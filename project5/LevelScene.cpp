#include "LevelScene.h"
#include <cstring>
#include <cstdio>
#include <cmath>

LevelScene::~LevelScene() {
    delete m_map;
}

void LevelScene::setup_camera(int map_pixel_w, int map_pixel_h) {
    m_camera.target   = m_player.position;
    m_camera.offset   = { GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f };
    m_camera.rotation = 0.0f;
    m_camera.zoom     = 1.0f;
}


void LevelScene::place_shield() {
    if (!m_data_ptr || m_data_ptr->shield_charges <= 0) return;
    for (int i = 0; i < MAX_SHIELDS; i++) {
        if (!m_shields[i].is_active) {
            m_shields[i].is_active = true;
            m_shields[i].position  = m_player.position;
            m_shields[i].timer     = SHIELD_DURATION;
            m_data_ptr->shield_charges--;
            return;
        }
    }
}

void LevelScene::update_shields(float dt) {
    for (int i = 0; i < MAX_SHIELDS; i++) {
        if (!m_shields[i].is_active) continue;
        m_shields[i].timer -= dt;
        if (m_shields[i].timer <= 0.0f) {
            m_shields[i].is_active = false;
        }
    }

    for (int e = 0; e < m_enemy_count; e++) {
        for (Entity* b : m_enemies[e].bullets) {
            if (!b->is_active) continue;
            for (int i = 0; i < MAX_SHIELDS; i++) {
                if (!m_shields[i].is_active) continue;
                if (CheckCollisionRecs(
                        { b->position.x - b->width * 0.5f,
                          b->position.y - b->height * 0.5f,
                          b->width, b->height },
                        m_shields[i].get_rect())) {
                    b->is_active = false;  
                }
            }
        }
    }

    for (int e = 0; e < m_enemy_count; e++) {
        if (!m_enemies[e].is_active) continue;
        for (int i = 0; i < MAX_SHIELDS; i++) {
            if (!m_shields[i].is_active) continue;
            if (CheckCollisionRecs(
                    m_enemies[e].get_rect(),
                    m_shields[i].get_rect())) {
                Vector2& ep = m_enemies[e].position;
                Vector2& sp = m_shields[i].position;
                float dx = ep.x - sp.x;
                float dy = ep.y - sp.y;
                float len = sqrtf(dx*dx + dy*dy);
                if (len > 0.001f) {
                    ep.x += (dx / len) * 4.0f;
                    ep.y += (dy / len) * 4.0f;
                }
            }
        }
    }
}

void LevelScene::render_shields() const {
    for (int i = 0; i < MAX_SHIELDS; i++) {
        if (!m_shields[i].is_active) continue;

        float t = m_shields[i].timer;
        bool blink = (t < 1.0f) && ((int)(t * 8.0f) % 2 == 0);
        if (blink) continue;

        unsigned char alpha = (unsigned char)(200.0f *
            (m_shields[i].timer / SHIELD_DURATION) + 55.0f);

        if (m_shield_tex.id != 0) {
            Rectangle src = { 0, 0,
                (float)m_shield_tex.width,
                (float)m_shield_tex.height };
            Rectangle dst = {
                m_shields[i].position.x - m_shields[i].width  * 0.5f,
                m_shields[i].position.y - m_shields[i].height * 0.5f,
                m_shields[i].width,
                m_shields[i].height };
            DrawTexturePro(m_shield_tex, src, dst, { 0, 0 }, 0.0f,
                        { 100, 200, 255, alpha });
        } else {
            DrawRectangle(
                (int)(m_shields[i].position.x - m_shields[i].width  * 0.5f),
                (int)(m_shields[i].position.y - m_shields[i].height * 0.5f),
                (int)m_shields[i].width,
                (int)m_shields[i].height,
                { 100, 200, 255, alpha });
        }

        float ratio = m_shields[i].timer / SHIELD_DURATION;
        int bar_w   = (int)(m_shields[i].width * ratio);
        DrawRectangle(
            (int)(m_shields[i].position.x - m_shields[i].width * 0.5f),
            (int)(m_shields[i].position.y + m_shields[i].height * 0.5f + 2),
            bar_w, 4, SKYBLUE);
    }
}
// process_input
void LevelScene::process_input() {
    m_player.movement = { 0, 0 };
    m_player.bullet_tex = m_bullet_tex;

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    m_player.movement.y -= 1.0f;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  m_player.movement.y += 1.0f;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  m_player.movement.x -= 1.0f;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) m_player.movement.x += 1.0f;

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse_world = GetScreenToWorld2D(GetMousePosition(), m_camera);
        float dx  = mouse_world.x - m_player.position.x;
        float dy  = mouse_world.y - m_player.position.y;
        float ang = atan2f(dy, dx) * (180.0f / 3.14159265f);
        m_player.rotation = ang + 90.0f;

        if (m_player.shoot_cooldown <= 0.0f) {
            m_player.shoot(ang);
            if (!m_player.bullets.empty()) {
                m_player.bullets.back()->texture = m_bullet_tex;
                m_player.bullets.back()->width   = 24.0f;
                m_player.bullets.back()->height  = 24.0f;
                PlaySound(m_sfx_shoot);
            }
        }
    }

    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        place_shield();
    }

    if (IsKeyPressed(KEY_ONE))   next_scene = SCENE_LEVEL1;
    if (IsKeyPressed(KEY_TWO))   next_scene = SCENE_LEVEL2;
    if (IsKeyPressed(KEY_THREE)) next_scene = SCENE_LEVEL3;
    if (IsKeyPressed(KEY_FOUR))  next_scene = SCENE_BOSS;
}

void LevelScene::clamp_player_to_map() {
    if (!m_map) return;
    float hw = m_player.width  * 0.5f;
    float hh = m_player.height * 0.5f;
    float mw = (float)m_map->get_pixel_width();
    float mh = (float)m_map->get_pixel_height();

    if (m_player.position.x < hw)      m_player.position.x = hw;
    if (m_player.position.x > mw - hw) m_player.position.x = mw - hw;
    if (m_player.position.y < hh)      m_player.position.y = hh;
    if (m_player.position.y > mh - hh) m_player.position.y = mh - hh;
}

void LevelScene::handle_enemy_player_collision(GameData& data) {
    if (m_invincible_timer > 0.0f) return;
    for (int i = 0; i < m_enemy_count; i++) {
        if (!m_enemies[i].is_active) continue;
        if (m_enemies[i].check_collision(m_player)) {
            m_enemies[i].take_damage(99);
            m_player.take_damage(1);
            data.lives = m_player.health;
            m_invincible_timer = 1.0f;
            PlaySound(m_sfx_hit);
        }
    }
}

// Update
void LevelScene::update(float dt, GameData& data) {
    m_data_ptr = &data;
    UpdateMusicStream(m_music);

    if (m_invincible_timer > 0.0f) {
        m_invincible_timer -= dt;
        m_player.is_invincible = true;
    } else {
        m_player.is_invincible = false;
    }

    if (m_level_done) {
        m_done_timer -= dt;
        if (m_done_timer <= 0.0f) next_scene = m_win_scene;
        return;
    }

    //  Player 
    Vector2 prev_player_pos = m_player.position;
    m_player.update(dt, nullptr, m_enemies, m_enemy_count, m_map);

    if (data.lives != m_player.health) {
        if (m_player.health < data.lives) PlaySound(m_sfx_hit);
        data.lives = m_player.health;
    }

    clamp_player_to_map();
    if (m_map->check_solid_collision(m_player.get_rect())) {
        m_player.position = prev_player_pos;
    }

    update_shields(dt);

    //  Enemies 
    for (int i = 0; i < m_enemy_count; i++) {
        if (m_enemies[i].just_died) {
            m_enemies[i].just_died = false;
            PlaySound(m_sfx_die);

            switch (m_enemies[i].entity_type) {
                case ENEMY_PATROL:  data.score += 100; break;
                case ENEMY_CHASER:  data.score += 150; break;
                case ENEMY_WAVE:    data.score += 150; break;
                case ENEMY_TURRET:  data.score += 300; break;
                default:            data.score += 100; break;
            }

            int roll = GetRandomValue(0, 99);
            if (roll < 20 && m_data_ptr->shield_charges < 9) {  
                m_data_ptr->shield_charges++;
            } else if (roll < 50 && m_powerup_count < MAX_POWERUPS) {
                m_powerups[m_powerup_count] = Entity(POWERUP, 80, 80, 0, 1, 1, 1);
                m_powerups[m_powerup_count].position  = m_enemies[i].position;
                m_powerups[m_powerup_count].is_active = true;
                m_powerups[m_powerup_count].texture   = m_powerup_tex;
                m_powerup_count++;
            }
        }

        if (!m_enemies[i].is_active) continue;

        Vector2 prev_pos = m_enemies[i].position;
        m_enemies[i].update(dt, &m_player, nullptr, 0, m_map);

        if (m_map->check_solid_collision(m_enemies[i].get_rect())) {
            m_enemies[i].position.x = prev_pos.x;
            if (m_map->check_solid_collision(m_enemies[i].get_rect())) {
                m_enemies[i].position.y = prev_pos.y;
            }
        }
    }

    //  Powerups 
    for (int i = 0; i < m_powerup_count; i++) {
        if (!m_powerups[i].is_active) continue;
        if (CheckCollisionRecs(m_powerups[i].get_rect(), m_player.get_rect())) {
            m_powerups[i].is_active = false;
            if (m_player.health < m_player.max_health) {
                m_player.health++;
                data.lives++;
            }
        }
    }

    handle_enemy_player_collision(data);

    //  Check player death 
    if (!m_player.is_active || data.lives <= 0) {
        data.lives = 0;
        next_scene = SCENE_LOSE;
        return;
    }

    //  Camera 
    m_camera.target = m_player.position;
    if (m_map) {
        float half_w = GetScreenWidth()  * 0.5f / m_camera.zoom;
        float half_h = GetScreenHeight() * 0.5f / m_camera.zoom;
        float mw     = (float)m_map->get_pixel_width();
        float mh     = (float)m_map->get_pixel_height();
        if (m_camera.target.x < half_w)      m_camera.target.x = half_w;
        if (m_camera.target.x > mw - half_w) m_camera.target.x = mw - half_w;
        if (m_camera.target.y < half_h)      m_camera.target.y = half_h;
        if (m_camera.target.y > mh - half_h) m_camera.target.y = mh - half_h;
    }

    //  Check win 
    int alive = 0;
    for (int i = 0; i < m_enemy_count; i++)
        if (m_enemies[i].is_active) alive++;
    if (alive == 0 && !m_level_done) {
        m_level_done = true;
        m_done_timer = 1.5f;
    }
}

// HUD
void LevelScene::draw_hud() const {
    if (!m_data_ptr) return;
    const GameData& data = *m_data_ptr;
    int sw = GetScreenWidth();
    int sh = GetScreenHeight();

    char buf[64];
    snprintf(buf, sizeof(buf), "LIVES: %d", data.lives);
    DrawText(buf, 16, 12, 22, WHITE);

    snprintf(buf, sizeof(buf), "SCORE: %d", data.score);
    int sw2 = MeasureText(buf, 22);
    DrawText(buf, sw - sw2 - 16, 12, 22, WHITE);

    int alive = 0;
    for (int i = 0; i < m_enemy_count; i++)
        if (m_enemies[i].is_active) alive++;
    snprintf(buf, sizeof(buf), "ENEMIES: %d", alive);
    int ew = MeasureText(buf, 22);
    DrawText(buf, (sw - ew) / 2, 12, 22, ORANGE);

    snprintf(buf, sizeof(buf), "SHIELD: %d", m_data_ptr->shield_charges);
    DrawText(buf, 16, 40, 20, SKYBLUE);
    DrawText("[RMB]", 16, 62, 16, DARKGRAY);

    if (m_level_done) {
        const char* msg = "SECTOR CLEARED!";
        int mw = MeasureText(msg, 42);
        DrawText(msg, (sw - mw) / 2, sh / 2 - 21, 42, GREEN);
    }
    if (m_invincible_timer > 0.0f) {
        const char* msg = "INVINCIBLE!";
        int mw = MeasureText(msg, 24);
        DrawText(msg, (sw - mw) / 2, sh / 2 + 40, 24, YELLOW);
    }
}

// Render
void LevelScene::render(Shader& shader) {
    BeginDrawing();
    ClearBackground({ 5, 5, 20, 255 });
    if (m_bg_tex.id != 0) {
        DrawTexturePro(m_bg_tex,
            { 0, 0, (float)m_bg_tex.width, (float)m_bg_tex.height },
            { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() },
            { 0, 0 }, 0.0f, { 255, 255, 255, 180 });
    }

    BeginMode2D(m_camera);
        BeginShaderMode(shader);
            if (m_map) m_map->render(m_camera);
        EndShaderMode();

        render_shields();   

        for (int i = 0; i < m_enemy_count; i++) m_enemies[i].render();
        m_player.render();

        for (int i = 0; i < m_powerup_count; i++)
            m_powerups[i].render();

    EndMode2D();

    draw_hud();
    EndDrawing();
}
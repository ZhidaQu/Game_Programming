#include "BossScene.h"
#include <cmath>
#include <cstdio>

static const int BOSS_W = 46;
static const int BOSS_H = 28;
static const int BOSS_DATA[BOSS_H][BOSS_W] = {
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
    {2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2},
    {2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2},
    {2,1,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,1,2},
    {2,1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,1,2},
    {2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2},
    {2,1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,1,2},
    {2,1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,1,2},
    {2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2},
    {2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2},
    {2,1,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,1,2},
    {2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2},
    {2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2},
    {2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2},
    {2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2},
    {2,1,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,1,2},
    {2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2},
    {2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2},
    {2,1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,1,2},
    {2,1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,1,2},
    {2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2},
    {2,1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,1,2},
    {2,1,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,1,2},
    {2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2},
    {2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2},
    {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
};

void BossScene::initialise(GameData& data) {
    m_data_ptr         = &data;
    next_scene         = SCENE_NONE;
    m_level_done       = false;
    m_done_timer       = 0.0f;
    m_phase            = BOSS_PHASE_1;
    m_boss_shoot_timer = 0.0f;
    m_spin_angle       = 0.0f;
    m_minion_timer     = 0.0f;
    m_minion_count     = 0;
    m_powerup_count    = 0;
    m_invincible_timer = 0.0f;
    m_phase_warning    = false;
    m_warning_timer    = 0.0f;
    for (int i = 0; i < MAX_BOSS_SHIELDS; i++) m_shields[i] = BossShield();

    Texture2D tileset = { 0 };
    m_map = new Map(BOSS_W, BOSS_H, &BOSS_DATA[0][0], tileset, 4);
    m_map->set_obstacle_tex(LoadTexture("assets/largeasteroid1.png"));

    m_player_tex      = LoadTexture("assets/spaceship_1.png");
    m_bullet_tex      = LoadTexture("assets/bullet1.png");
    m_boss_tex        = LoadTexture("assets/ufo_ship3.png");
    m_minion_tex      = LoadTexture("assets/ufo_ship2.png");
    m_powerup_tex     = LoadTexture("assets/coin.png");
    m_boss_bullet_tex = LoadTexture("assets/bullet2.png");
    m_shield_tex      = LoadTexture("assets/shield.png");
    m_font            = LoadFont("assets/font.ttf");

    m_music     = LoadMusicStream("assets/audio/boos_music.mp3");
    m_sfx_shoot = LoadSound("assets/audio/shoot.wav");
    m_sfx_hit   = LoadSound("assets/audio/hit.wav");
    m_sfx_die   = LoadSound("assets/audio/explode.wav");
    SetMusicVolume(m_music, 0.6f);
    PlayMusicStream(m_music);

    m_player = Entity(PLAYER, 32, 32, 160, 4, 1, 4);
    m_player.position     = { 4 * TILE_SIZE, 14 * TILE_SIZE };
    m_player.max_health   = 3;
    m_player.health       = (data.lives > 0 && data.lives <= 3) ? data.lives : 3;
    m_player.shoot_rate   = 0.20f;
    m_player.bullet_speed = 460.0f;
    m_player.anim_speed   = 0.08f;
    m_player.texture      = m_player_tex;
    m_player.bullet_tex   = m_bullet_tex;

    m_boss = Entity(ENEMY_TURRET, 64, 64, 0, 1, 1, 1);
    m_boss.position      = { 34 * TILE_SIZE, 14 * TILE_SIZE };
    m_boss.max_health    = m_boss_max_hp;
    m_boss.health        = m_boss_max_hp;
    m_boss.shoot_rate    = 1.5f;
    m_boss.bullet_speed  = 320.0f;
    m_boss.texture       = m_boss_tex;
    m_boss.bullet_tex    = m_boss_bullet_tex;
    m_boss.is_active     = true;
    m_boss.is_invincible = false;

    setup_camera();
}

void BossScene::process_input() {
    m_player.movement   = { 0, 0 };
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
}

void BossScene::place_shield() {
    if (!m_data_ptr || m_data_ptr->shield_charges <= 0) return;
    for (int i = 0; i < MAX_BOSS_SHIELDS; i++) {
        if (!m_shields[i].is_active) {
            m_shields[i].is_active = true;
            m_shields[i].position  = m_player.position;
            m_shields[i].timer     = SHIELD_DURATION;
            m_data_ptr->shield_charges--;
            return;
        }
    }
}

void BossScene::update_shields(float dt) {
    for (int i = 0; i < MAX_BOSS_SHIELDS; i++) {
        if (!m_shields[i].is_active) continue;
        m_shields[i].timer -= dt;
        if (m_shields[i].timer <= 0.0f)
            m_shields[i].is_active = false;
    }
    for (Entity* b : m_boss.bullets) {
        if (!b->is_active) continue;
        for (int i = 0; i < MAX_BOSS_SHIELDS; i++) {
            if (!m_shields[i].is_active) continue;
            Rectangle br = { b->position.x - b->width * 0.5f,
                             b->position.y - b->height * 0.5f,
                             b->width, b->height };
            if (CheckCollisionRecs(br, m_shields[i].get_rect()))
                b->is_active = false;
        }
    }
    for (int e = 0; e < m_minion_count; e++) {
        if (!m_minions[e].is_active) continue;
        for (int i = 0; i < MAX_BOSS_SHIELDS; i++) {
            if (!m_shields[i].is_active) continue;
            if (CheckCollisionRecs(m_minions[e].get_rect(), m_shields[i].get_rect())) {
                float dx = m_minions[e].position.x - m_shields[i].position.x;
                float dy = m_minions[e].position.y - m_shields[i].position.y;
                float len = sqrtf(dx*dx + dy*dy);
                if (len > 0.001f) {
                    m_minions[e].position.x += (dx / len) * 4.0f;
                    m_minions[e].position.y += (dy / len) * 4.0f;
                }
            }
        }
    }
}

void BossScene::render_shields() const {
    for (int i = 0; i < MAX_BOSS_SHIELDS; i++) {
        if (!m_shields[i].is_active) continue;
        float t = m_shields[i].timer;
        bool blink = (t < 1.0f) && ((int)(t * 8.0f) % 2 == 0);
        if (blink) continue;
        unsigned char alpha = (unsigned char)(200.0f * (t / SHIELD_DURATION) + 55.0f);
        if (m_shield_tex.id != 0) {
            Rectangle src = { 0, 0, (float)m_shield_tex.width, (float)m_shield_tex.height };
            Rectangle dst = { m_shields[i].position.x - m_shields[i].width  * 0.5f,
                              m_shields[i].position.y - m_shields[i].height * 0.5f,
                              m_shields[i].width, m_shields[i].height };
            DrawTexturePro(m_shield_tex, src, dst, { 0, 0 }, 0.0f, { 100, 200, 255, alpha });
        } else {
            DrawRectangle(
                (int)(m_shields[i].position.x - m_shields[i].width  * 0.5f),
                (int)(m_shields[i].position.y - m_shields[i].height * 0.5f),
                (int)m_shields[i].width, (int)m_shields[i].height,
                { 100, 200, 255, alpha });
        }
        int bar_w = (int)(m_shields[i].width * (t / SHIELD_DURATION));
        DrawRectangle(
            (int)(m_shields[i].position.x - m_shields[i].width * 0.5f),
            (int)(m_shields[i].position.y + m_shields[i].height * 0.5f + 2),
            bar_w, 4, SKYBLUE);
    }
}

void BossScene::shoot_ring(int count) {
    float step = 360.0f / count;
    for (int i = 0; i < count; i++) {
        float ang = m_spin_angle + step * i;
        float rad = ang * 3.14159265f / 180.0f;
        Entity* b      = new Entity();
        b->entity_type = BULLET;
        b->is_active   = true;
        b->width       = 40.0f;
        b->height      = 40.0f;
        b->texture     = m_boss_bullet_tex;
        b->position    = { m_boss.position.x + cosf(rad)*40.0f,
                           m_boss.position.y + sinf(rad)*40.0f };
        b->velocity        = { cosf(rad)*m_boss.bullet_speed, sinf(rad)*m_boss.bullet_speed };
        b->rotation        = ang + 90.0f;
        b->bullet_lifetime = 4.0f;
        m_boss.bullets.push_back(b);
    }
}

void BossScene::shoot_spread(int count, float base_angle) {
    float spread = 30.0f;
    float step   = (count > 1) ? spread / (count - 1) : 0.0f;
    float start  = base_angle - spread * 0.5f;
    for (int i = 0; i < count; i++) {
        float ang = start + step * i;
        float rad = ang * 3.14159265f / 180.0f;
        Entity* b      = new Entity();
        b->entity_type = BULLET;
        b->is_active   = true;
        b->width       = 40.0f;
        b->height      = 40.0f;
        b->texture     = m_boss_bullet_tex;
        b->position    = { m_boss.position.x + cosf(rad)*40.0f,
                           m_boss.position.y + sinf(rad)*40.0f };
        b->velocity        = { cosf(rad)*m_boss.bullet_speed, sinf(rad)*m_boss.bullet_speed };
        b->rotation        = ang + 90.0f;
        b->bullet_lifetime = 3.5f;
        if (m_phase == BOSS_PHASE_3) b->is_homing = true;
        m_boss.bullets.push_back(b);
    }
}

void BossScene::spawn_minions() {
    int alive = 0;
    for (int i = 0; i < m_minion_count; i++)
        if (m_minions[i].is_active) m_minions[alive++] = m_minions[i];
    m_minion_count = alive;
    int spawn = ((MAX_MINIONS - m_minion_count) >= 2) ? 2 : (MAX_MINIONS - m_minion_count);
    float offsets[4][2] = { {0,-6*TILE_SIZE},{0,6*TILE_SIZE},{-5*TILE_SIZE,0},{5*TILE_SIZE,0} };
    for (int i = 0; i < spawn; i++) {
        int slot = m_minion_count;
        if (slot >= MAX_MINIONS) break;
        m_minions[slot] = Entity(ENEMY_CHASER, 28, 28, 120, 4, 1, 4);
        m_minions[slot].position     = { m_boss.position.x + offsets[i%4][0],
                                         m_boss.position.y + offsets[i%4][1] };
        m_minions[slot].health       = (m_phase == BOSS_PHASE_3) ? 3 : 2;
        m_minions[slot].detect_range = 400.0f;
        m_minions[slot].ai_state     = CHASING;
        m_minions[slot].texture      = m_minion_tex;
        m_minions[slot].bullet_tex   = m_boss_bullet_tex;
        m_minions[slot].is_active    = true;
        m_minion_count++;
    }
}

void BossScene::update_boss(float dt, GameData& data) {
    if (!m_boss.is_active) return;
    if (m_boss.hit_flash_timer > 0.0f) m_boss.hit_flash_timer -= dt;

    float hp_ratio  = (float)m_boss.health / (float)m_boss_max_hp;
    BossPhase new_p = m_phase;
    if      (hp_ratio <= 0.33f) new_p = BOSS_PHASE_3;
    else if (hp_ratio <= 0.66f) new_p = BOSS_PHASE_2;
    if (new_p != m_phase) {
        m_phase = new_p; m_phase_warning = true;
        m_warning_timer = 2.0f; m_boss.is_invincible = true;
    }
    if (m_boss.is_invincible && m_warning_timer <= 0.0f) m_boss.is_invincible = false;

    float dx = m_player.position.x - m_boss.position.x;
    float dy = m_player.position.y - m_boss.position.y;
    m_boss.rotation = atan2f(dy, dx) * (180.0f / 3.14159265f) + 90.0f;
    m_spin_angle += ((m_phase == BOSS_PHASE_1) ? 60.0f :
                     (m_phase == BOSS_PHASE_2) ? 90.0f : 130.0f) * dt;
    m_boss_shoot_timer -= dt;
    float pa = atan2f(dy, dx) * (180.0f / 3.14159265f);

    if (m_phase == BOSS_PHASE_1) {
        if (m_boss_shoot_timer <= 0.0f) { shoot_ring(8);  m_boss_shoot_timer = 1.8f; }
    } else if (m_phase == BOSS_PHASE_2) {
        if (m_boss_shoot_timer <= 0.0f) { shoot_ring(12); shoot_spread(3,pa); m_boss_shoot_timer = 1.2f; }
        m_minion_timer -= dt;
        if (m_minion_timer <= 0.0f) { spawn_minions(); m_minion_timer = 8.0f; }
    } else {
        if (m_boss_shoot_timer <= 0.0f) { shoot_ring(16); shoot_spread(5,pa); m_boss_shoot_timer = 0.8f; }
        m_minion_timer -= dt;
        if (m_minion_timer <= 0.0f) { spawn_minions(); m_minion_timer = 5.0f; }
    }
    m_boss.update_bullets(dt, &m_player, 1, m_map);
}

void BossScene::handle_collisions(GameData& data) {
    for (Entity* b : m_player.bullets) {
        if (!b->is_active || !m_boss.is_active) continue;
        if (b->check_collision(m_boss)) {
            if (!m_boss.is_invincible) {
                m_boss.take_damage(1); PlaySound(m_sfx_hit);
                if (m_boss.health <= 0) { m_boss.is_active = false; data.score += 1000; PlaySound(m_sfx_die); }
            }
            b->is_active = false;
        }
    }
    for (Entity* b : m_player.bullets) {
        if (!b->is_active) continue;
        for (int i = 0; i < m_minion_count; i++) {
            if (!m_minions[i].is_active) continue;
            if (b->check_collision(m_minions[i])) {
                m_minions[i].take_damage(1); b->is_active = false;
                if (m_minions[i].just_died) {
                    m_minions[i].just_died = false; data.score += 200; PlaySound(m_sfx_die);
                    if (GetRandomValue(0,99) < 30 && m_powerup_count < MAX_POWERUPS) {
                        m_powerups[m_powerup_count] = Entity(POWERUP, 60, 60, 0, 1, 1, 1);
                        m_powerups[m_powerup_count].position  = m_minions[i].position;
                        m_powerups[m_powerup_count].is_active = true;
                        m_powerups[m_powerup_count].texture   = m_powerup_tex;
                        m_powerup_count++;
                    }
                }
                break;
            }
        }
    }
    if (m_invincible_timer <= 0.0f) {
        for (int i = 0; i < m_minion_count; i++) {
            if (!m_minions[i].is_active) continue;
            if (m_minions[i].check_collision(m_player)) {
                m_minions[i].take_damage(99); m_player.take_damage(1);
                data.lives = m_player.health; m_invincible_timer = 1.5f; PlaySound(m_sfx_hit);
            }
        }
        if (m_boss.is_active && m_boss.check_collision(m_player)) {
            m_player.take_damage(1); data.lives = m_player.health;
            m_invincible_timer = 1.5f; PlaySound(m_sfx_hit);
        }
    }
    for (int i = 0; i < m_powerup_count; i++) {
        if (!m_powerups[i].is_active) continue;
        if (CheckCollisionRecs(m_powerups[i].get_rect(), m_player.get_rect())) {
            m_powerups[i].is_active = false;
            if (m_player.health < m_player.max_health) { m_player.health++; data.lives++; }
        }
    }
}

void BossScene::update(float dt, GameData& data) {
    m_data_ptr = &data;
    UpdateMusicStream(m_music);

    if (m_phase_warning) { m_warning_timer -= dt; if (m_warning_timer <= 0.0f) m_phase_warning = false; }

    if (m_invincible_timer > 0.0f) { m_invincible_timer -= dt; m_player.is_invincible = true; }
    else m_player.is_invincible = false;

    if (m_level_done) {
        m_done_timer -= dt;
        if (m_done_timer <= 0.0f) next_scene = SCENE_WIN;
        return;
    }

    Vector2 prev_pos = m_player.position;
    m_player.update(dt, nullptr, nullptr, 0, m_map);

    if (data.lives != m_player.health) {
        if (m_player.health < data.lives) PlaySound(m_sfx_hit);
        data.lives = m_player.health;
    }

    {
        float hw = m_player.width * 0.5f, hh = m_player.height * 0.5f;
        float mw = (float)m_map->get_pixel_width(), mh = (float)m_map->get_pixel_height();
        if (m_player.position.x < hw)      m_player.position.x = hw;
        if (m_player.position.x > mw - hw) m_player.position.x = mw - hw;
        if (m_player.position.y < hh)      m_player.position.y = hh;
        if (m_player.position.y > mh - hh) m_player.position.y = mh - hh;
    }
    if (m_map->check_solid_collision(m_player.get_rect())) m_player.position = prev_pos;

    update_shields(dt);
    update_boss(dt, data);

    for (int i = 0; i < m_minion_count; i++) {
        if (!m_minions[i].is_active) continue;
        if (m_minions[i].hit_flash_timer > 0.0f) m_minions[i].hit_flash_timer -= dt;
        Vector2 pm = m_minions[i].position;
        m_minions[i].update(dt, &m_player, nullptr, 0, m_map);
        if (m_map->check_solid_collision(m_minions[i].get_rect())) {
            m_minions[i].position.x = pm.x;
            if (m_map->check_solid_collision(m_minions[i].get_rect())) m_minions[i].position.y = pm.y;
        }
    }

    handle_collisions(data);

    if (!m_player.is_active || data.lives <= 0) { data.lives = 0; next_scene = SCENE_BOSS_LOSE; return; }
    if (!m_boss.is_active && !m_level_done) { m_level_done = true; m_done_timer = 2.0f; }

    m_camera.target = m_player.position;
    {
        float hw = GetScreenWidth() * 0.5f / m_camera.zoom, hh = GetScreenHeight() * 0.5f / m_camera.zoom;
        float mw = (float)m_map->get_pixel_width(), mh = (float)m_map->get_pixel_height();
        if (m_camera.target.x < hw)      m_camera.target.x = hw;
        if (m_camera.target.x > mw - hw) m_camera.target.x = mw - hw;
        if (m_camera.target.y < hh)      m_camera.target.y = hh;
        if (m_camera.target.y > mh - hh) m_camera.target.y = mh - hh;
    }
}

void BossScene::draw_boss_healthbar() const {
    if (!m_boss.is_active) return;
    int sw = GetScreenWidth();
    int nw = MeasureText("FINAL BOSS", 20);
    DrawText("FINAL BOSS", (sw - nw) / 2, GetScreenHeight() - 52, 20, RED);
    int bar_w = sw/2, bar_h = 18, bar_x = (sw-bar_w)/2, bar_y = GetScreenHeight()-28;
    DrawRectangle(bar_x, bar_y, bar_w, bar_h, DARKGRAY);
    float ratio = (float)m_boss.health / (float)m_boss_max_hp;
    Color c = (ratio > 0.5f) ? GREEN : (ratio > 0.25f) ? YELLOW : RED;
    DrawRectangle(bar_x, bar_y, (int)(bar_w*ratio), bar_h, c);
    DrawRectangleLines(bar_x, bar_y, bar_w, bar_h, WHITE);
    DrawRectangle(bar_x + bar_w/3,     bar_y, 2, bar_h, WHITE);
    DrawRectangle(bar_x + bar_w*2/3,   bar_y, 2, bar_h, WHITE);
}

void BossScene::draw_hud() const {
    if (!m_data_ptr) return;
    const GameData& data = *m_data_ptr;
    int sw = GetScreenWidth();
    char buf[64];
    snprintf(buf, sizeof(buf), "LIVES: %d", data.lives);
    DrawText(buf, 16, 12, 22, WHITE);
    snprintf(buf, sizeof(buf), "SCORE: %d", data.score);
    DrawText(buf, sw - MeasureText(buf, 22) - 16, 12, 22, WHITE);
    snprintf(buf, sizeof(buf), "SHIELD: %d", data.shield_charges);
    DrawText(buf, 16, 40, 20, SKYBLUE);
    DrawText("[RMB]", 16, 62, 16, DARKGRAY);
    const char* ps = (m_phase==BOSS_PHASE_1)?"PHASE 1":(m_phase==BOSS_PHASE_2)?"PHASE 2":"PHASE 3";
    Color pc = (m_phase==BOSS_PHASE_1)?GREEN:(m_phase==BOSS_PHASE_2)?YELLOW:RED;
    DrawText(ps, (sw - MeasureText(ps,20))/2, 12, 20, pc);
    if (m_invincible_timer > 0.0f) {
        const char* msg = "INVINCIBLE!";
        DrawText(msg, (sw-MeasureText(msg,24))/2, GetScreenHeight()/2+40, 24, YELLOW);
    }
    if (m_phase_warning) {
        const char* msg = (m_phase==BOSS_PHASE_2)?"-- PHASE 2 --":"-- FINAL PHASE --";
        Color wc = (m_phase==BOSS_PHASE_2)?YELLOW:RED;
        DrawText(msg, (sw-MeasureText(msg,36))/2, GetScreenHeight()/2-18, 36, wc);
    }
    if (m_level_done) {
        const char* msg = "BOSS DEFEATED!";
        DrawText(msg, (sw-MeasureText(msg,48))/2, GetScreenHeight()/2-24, 48, GREEN);
    }
    draw_boss_healthbar();
}

void BossScene::setup_camera() {
    m_camera.target   = m_player.position;
    m_camera.offset   = { GetScreenWidth()*0.5f, GetScreenHeight()*0.5f };
    m_camera.rotation = 0.0f;
    m_camera.zoom     = 1.0f;
}

void BossScene::render(Shader& shader) {
    BeginDrawing();
    ClearBackground({ 5, 0, 20, 255 });
    BeginMode2D(m_camera);
        BeginShaderMode(shader);
            if (m_map) m_map->render(m_camera);
        EndShaderMode();
        render_shields();
        for (int i = 0; i < m_powerup_count; i++) m_powerups[i].render();
        for (int i = 0; i < m_minion_count;  i++) m_minions[i].render();
        if (m_boss.is_active) {
            Color tint = WHITE;
            if (m_boss.hit_flash_timer > 0.0f)
                tint = ((int)(m_boss.hit_flash_timer*10.0f)%2==0)?RED:WHITE;
            if (m_boss.texture.id != 0) {
                Rectangle src = {0,0,(float)m_boss.texture.width,(float)m_boss.texture.height};
                Rectangle dst = {m_boss.position.x,m_boss.position.y,m_boss.width,m_boss.height};
                DrawTexturePro(m_boss.texture,src,dst,{m_boss.width*0.5f,m_boss.height*0.5f},m_boss.rotation,tint);
            } else {
                DrawPoly({m_boss.position.x,m_boss.position.y},8,32,m_boss.rotation,RED);
            }
            for (const Entity* b : m_boss.bullets) {
                if (!b->is_active) continue;
                if (b->texture.id != 0) {
                    float dw=b->width*3.0f, dh=b->height*3.0f;
                    Rectangle src={0,0,(float)b->texture.width,(float)b->texture.height};
                    Rectangle dst={b->position.x,b->position.y,dw,dh};
                    DrawTexturePro(b->texture,src,dst,{dw*0.5f,dh*0.5f},b->rotation,ORANGE);
                } else {
                    DrawCircleV({b->position.x,b->position.y},8,ORANGE);
                }
            }
        }
        m_player.render();
    EndMode2D();
    draw_hud();
    DrawText("FINAL SECTOR - BOSS CORE", 16, GetScreenHeight()-52, 14, DARKGRAY);
    EndDrawing();
}
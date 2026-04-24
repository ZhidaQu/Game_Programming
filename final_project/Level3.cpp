#include "Level3.h"

static const int LEVEL3_W = 46;
static const int LEVEL3_H = 28;
static const int LEVEL3_DATA[LEVEL3_H][LEVEL3_W] = {
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 2},
    {2, 1, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
};

void Level3::initialise(GameData& data) {
    m_powerup_count = 0;
    m_data_ptr   = &data;
    next_scene   = SCENE_NONE;
    m_level_done = false;
    m_win_scene  = SCENE_BOSS;

    

    Texture2D tileset = { 0 };
    m_map = new Map(LEVEL3_W, LEVEL3_H, &LEVEL3_DATA[0][0], tileset, 4);

    Texture2D obstacle_tex = LoadTexture("assets/largeasteroid1.png");
    m_bg_tex = LoadTexture("assets/background.png");
    m_map->set_obstacle_tex(obstacle_tex);

    m_player_tex   = LoadTexture("assets/spaceship_1.png");
    m_bullet_tex   = LoadTexture("assets/bullet1.png");
    m_enemy_tex[0] = LoadTexture("assets/ufo_ship1.png");
    m_enemy_tex[1] = LoadTexture("assets/ufo_ship2.png");
    m_enemy_tex[2] = LoadTexture("assets/ufo_ship3.png");
    m_font         = LoadFont("assets/font.ttf");
    m_powerup_tex      = LoadTexture("assets/coin.png");
    m_enemy_bullet_tex = LoadTexture("assets/bullet2.png");
    m_shield_tex = LoadTexture("assets/shield.png");

    m_music     = LoadMusicStream("assets/audio/background.wav");
    m_sfx_shoot = LoadSound("assets/audio/shoot.wav");
    m_sfx_hit   = LoadSound("assets/audio/hit.wav");
    m_sfx_die   = LoadSound("assets/audio/explode.wav");
    SetMusicVolume(m_music, 0.55f);
    PlayMusicStream(m_music);

    m_player = Entity(PLAYER, 32, 32, 160, 4, 1, 4);
    m_player.position = { 3 * TILE_SIZE, 20 * TILE_SIZE }; 
    m_player.max_health   = 3;
    m_player.health       = (data.lives < 3) ? data.lives : 3;
    m_player.shoot_rate   = 0.22f;
    m_player.bullet_speed = 450.0f;
    m_player.anim_speed   = 0.08f;
    m_player.texture      = m_player_tex;

    m_enemy_count = 12;
    int idx = 0;

    // Patrol (4)
    for (int i = 0; i < 4; i++, idx++) {
        m_enemies[idx] = Entity(ENEMY_PATROL, 30, 30, 95, 2, 1, 2);
        m_enemies[idx].position     = { (float)((7 + i * 7) * TILE_SIZE),
                                        (float)((6 + i * 3) * TILE_SIZE) };
        m_enemies[idx].patrol_start = m_enemies[idx].position;
        m_enemies[idx].patrol_end   = { m_enemies[idx].position.x + 5 * TILE_SIZE,
                                        m_enemies[idx].position.y };
        m_enemies[idx].detect_range = 210.0f;
        m_enemies[idx].health       = 5;
        m_enemies[idx].shoot_rate   = 1.4f;
        m_enemies[idx].bullet_speed = 310.0f;
        m_enemies[idx].anim_speed   = 0.13f;
        m_enemies[idx].ai_state     = PATROLLING;
        m_enemies[idx].texture      = m_enemy_tex[0];
        m_enemies[idx].bullet_tex = m_enemy_bullet_tex;

        while (m_map->check_solid_collision(m_enemies[idx].get_rect())) {
            m_enemies[idx].position.x     += TILE_SIZE;
            m_enemies[idx].patrol_start.x += TILE_SIZE;
            m_enemies[idx].patrol_end.x   += TILE_SIZE;
        }
    }

    // Chasers (3)
    for (int i = 0; i < 3; i++, idx++) {
        m_enemies[idx] = Entity(ENEMY_CHASER, 28, 28, 145, 4, 1, 4);
        m_enemies[idx].position     = { (float)((20 + i * 4) * TILE_SIZE),
                                        (float)((10 + i * 4) * TILE_SIZE) };
        m_enemies[idx].detect_range = 260.0f;
        m_enemies[idx].health       = 3;
        m_enemies[idx].anim_speed   = 0.07f;
        m_enemies[idx].ai_state     = CHASING;
        m_enemies[idx].texture      = m_enemy_tex[1];
        m_enemies[idx].bullet_tex = m_enemy_bullet_tex;

        while (m_map->check_solid_collision(m_enemies[idx].get_rect())) {
            m_enemies[idx].position.x += TILE_SIZE;
        }
    }

    // Wave enemies (2)
    for (int i = 0; i < 2; i++, idx++) {
        m_enemies[idx] = Entity(ENEMY_WAVE, 28, 28, 120, 1, 1, 1);
        m_enemies[idx].position     = { (float)((12 + i * 6) * TILE_SIZE),
                                        (float)((14 + i * 3) * TILE_SIZE) };
        m_enemies[idx].detect_range = 280.0f;
        m_enemies[idx].health       = 4;
        m_enemies[idx].shoot_rate   = 2.0f;
        m_enemies[idx].bullet_speed = 280.0f;
        m_enemies[idx].ai_state     = CHASING;
        m_enemies[idx].texture      = m_enemy_tex[1];

        while (m_map->check_solid_collision(m_enemies[idx].get_rect())) {
            m_enemies[idx].position.x += TILE_SIZE;
        }
    }

    // Turrets (3)
    float turret_positions[3][2] = {
        { 18 * TILE_SIZE,  8 * TILE_SIZE },
        { 30 * TILE_SIZE, 13 * TILE_SIZE },
        { 18 * TILE_SIZE, 20 * TILE_SIZE },
    };
    for (int i = 0; i < 3; i++, idx++) {
        m_enemies[idx] = Entity(ENEMY_TURRET, 34, 34, 0, 1, 1, 1);
        m_enemies[idx].position       = { turret_positions[i][0], turret_positions[i][1] };
        m_enemies[idx].attack_range   = 280.0f;
        m_enemies[idx].health         = 8;
        m_enemies[idx].shoot_rate     = 3.0f;
        m_enemies[idx].shoot_cooldown = 2.0f;
        m_enemies[idx].bullet_speed   = 340.0f;
        m_enemies[idx].ai_state       = IDLE;
        m_enemies[idx].texture        = m_enemy_tex[2];
        m_enemies[idx].bullet_tex = m_enemy_bullet_tex;

        while (m_map->check_solid_collision(m_enemies[idx].get_rect())) {
            m_enemies[idx].position.x += TILE_SIZE;
        }
    }

    setup_camera(m_map->get_pixel_width(), m_map->get_pixel_height());
}

void Level3::render(Shader& shader) {
    BeginDrawing();
    ClearBackground({ 2, 3, 15, 255 });

    if (m_bg_tex.id != 0) {
        DrawTexturePro(m_bg_tex,
            { 0, 0, (float)m_bg_tex.width, (float)m_bg_tex.height },
            { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() },
            { 0, 0 }, 0.0f, { 255, 255, 255, 180 });
    }

    BeginMode2D(m_camera);
        BeginShaderMode(shader);
            m_map->render(m_camera);
        EndShaderMode();
        render_shields();
        for (int i = 0; i < m_powerup_count; i++) {
            m_powerups[i].render();
        }
        for (int i = 0; i < m_enemy_count; i++) m_enemies[i].render();
        m_player.render();
    EndMode2D();

    if (m_data_ptr) draw_hud();
    DrawText("SECTOR 3 - COMMAND CORE", 16, GetScreenHeight() - 28, 16, DARKGRAY);
    EndDrawing();
}
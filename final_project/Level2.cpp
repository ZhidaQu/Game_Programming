#include "Level2.h"

static const int LEVEL2_W = 44;
static const int LEVEL2_H = 26;
static const int LEVEL2_DATA[LEVEL2_H][LEVEL2_W] = {
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
};

void Level2::initialise(GameData& data) {
    m_powerup_count = 0;
    m_data_ptr   = &data;
    next_scene   = SCENE_NONE;
    m_level_done = false;
    m_win_scene  = SCENE_LEVEL3;

    

    Texture2D tileset = { 0 };
    m_map = new Map(LEVEL2_W, LEVEL2_H, &LEVEL2_DATA[0][0], tileset, 4);

    Texture2D obstacle_tex = LoadTexture("assets/largeasteroid1.png");
    m_bg_tex = LoadTexture("assets/background.png");
    m_map->set_obstacle_tex(obstacle_tex);

    m_player_tex   = LoadTexture("assets/spaceship_1.png");
    m_bullet_tex   = LoadTexture("assets/bullet1.png");
    m_enemy_tex[0] = LoadTexture("assets/ufo_ship1.png");
    m_enemy_tex[1] = LoadTexture("assets/ufo_ship2.png");
    m_font         = LoadFont("assets/font.ttf");
    m_powerup_tex      = LoadTexture("assets/coin.png");
    m_enemy_bullet_tex = LoadTexture("assets/bullet2.png");
    m_shield_tex = LoadTexture("assets/shield.png");

    m_music     = LoadMusicStream("assets/audio/background.wav");
    m_sfx_shoot = LoadSound("assets/audio/shoot.wav");
    m_sfx_hit   = LoadSound("assets/audio/hit.wav");
    m_sfx_die   = LoadSound("assets/audio/explode.wav");
    SetMusicVolume(m_music, 0.5f);
    PlayMusicStream(m_music);

    m_player = Entity(PLAYER, 32, 32, 160, 4, 1, 4);
    m_player.position     = { 3 * TILE_SIZE, 10 * TILE_SIZE };
    m_player.max_health   = 3;
    m_player.health       = data.lives;
    m_player.shoot_rate   = 0.25f;
    m_player.bullet_speed = 430.0f;
    m_player.anim_speed   = 0.09f;
    m_player.texture      = m_player_tex;

    m_enemy_count = 8;

    // Patrol (4)
    for (int i = 0; i < 4; i++) {
        m_enemies[i] = Entity(ENEMY_PATROL, 30, 30, 90, 2, 1, 2);
        m_enemies[i].position     = { (float)((9 + i * 6) * TILE_SIZE),
                                      (float)((5 + i * 3) * TILE_SIZE) };
        m_enemies[i].patrol_start = m_enemies[i].position;
        m_enemies[i].patrol_end   = { m_enemies[i].position.x + 6 * TILE_SIZE,
                                      m_enemies[i].position.y };
        m_enemies[i].detect_range = 200.0f;
        m_enemies[i].health       = 4;
        m_enemies[i].shoot_rate   = 1.6f;
        m_enemies[i].bullet_speed = 300.0f;
        m_enemies[i].anim_speed   = 0.14f;
        m_enemies[i].ai_state     = PATROLLING;
        m_enemies[i].texture      = m_enemy_tex[0];
        m_enemies[i].bullet_tex   = m_enemy_bullet_tex;

        while (m_map->check_solid_collision(m_enemies[i].get_rect())) {
            m_enemies[i].position.x     += TILE_SIZE;
            m_enemies[i].patrol_start.x += TILE_SIZE;
            m_enemies[i].patrol_end.x   += TILE_SIZE;
        }
    }

    // Chasers (2)
    for (int i = 4; i < 6; i++) {
        m_enemies[i] = Entity(ENEMY_CHASER, 28, 28, 130, 4, 1, 4);
        m_enemies[i].position     = { (float)((18 + (i-4) * 3) * TILE_SIZE),
                                      (float)((8  + (i-4) * 3) * TILE_SIZE) };
        m_enemies[i].detect_range = 240.0f;
        m_enemies[i].health       = 3;
        m_enemies[i].anim_speed   = 0.08f;
        m_enemies[i].ai_state     = CHASING;
        m_enemies[i].texture      = m_enemy_tex[1];
        m_enemies[i].texture = m_enemy_tex[0];

        while (m_map->check_solid_collision(m_enemies[i].get_rect())) {
            m_enemies[i].position.x += TILE_SIZE;
        }
    }

    // Wave enemies (2)
    for (int i = 6; i < 8; i++) {
        m_enemies[i] = Entity(ENEMY_WAVE, 28, 28, 110, 1, 1, 1);
        m_enemies[i].position     = { (float)((24 + (i-6) * 4) * TILE_SIZE),
                                      (float)((10 + (i-6) * 3) * TILE_SIZE) };
        m_enemies[i].detect_range = 260.0f;
        m_enemies[i].health       = 1;
        m_enemies[i].ai_state     = CHASING;
        m_enemies[i].texture      = m_enemy_tex[1];
        m_enemies[i].texture = m_enemy_tex[0];

        while (m_map->check_solid_collision(m_enemies[i].get_rect())) {
            m_enemies[i].position.x += TILE_SIZE;
        }
    }

    setup_camera(m_map->get_pixel_width(), m_map->get_pixel_height());
}

void Level2::render(Shader& shader) {
    BeginDrawing();
    ClearBackground({ 3, 5, 18, 255 });
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
    DrawText("SECTOR 2 - ASTEROID BELT", 16, GetScreenHeight() - 28, 16, DARKGRAY);
    EndDrawing();
}
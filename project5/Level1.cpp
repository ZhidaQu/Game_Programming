#include "Level1.h"

static const int LEVEL1_W = 40;
static const int LEVEL1_H = 25;
static const int LEVEL1_DATA[LEVEL1_H][LEVEL1_W] = {
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 2, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
    {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
};

void Level1::initialise(GameData& data) {
    m_powerup_count = 0;
    m_data_ptr   = &data;
    next_scene   = SCENE_NONE;
    m_level_done = false;
    m_win_scene  = SCENE_LEVEL2;

    

    Texture2D tileset = { 0 };
    m_map = new Map(LEVEL1_W, LEVEL1_H, &LEVEL1_DATA[0][0], tileset, 4);

    Texture2D obstacle_tex = LoadTexture("assets/largeasteroid1.png");
    m_bg_tex = LoadTexture("assets/background.png");
    m_map->set_obstacle_tex(obstacle_tex);

    m_player_tex   = LoadTexture("assets/spaceship_1.png");
    m_bullet_tex   = LoadTexture("assets/bullet1.png");
    m_enemy_tex[0] = LoadTexture("assets/ufo_ship1.png");
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
    m_player.position = { 5 * TILE_SIZE, 12 * TILE_SIZE };
    m_player.max_health   = 3;
    m_player.health     = (data.lives > 0 && data.lives <= 3) ? data.lives : 3;
    m_player.shoot_rate   = 0.28f;
    m_player.bullet_speed = 420.0f;
    m_player.anim_speed   = 0.10f;
    m_player.texture      = m_player_tex;

    m_enemy_count = 6;
    struct { float x1, y1, x2, y2; } patrol_paths[6] = {
        {  6*TILE_SIZE,  4*TILE_SIZE, 12*TILE_SIZE,  4*TILE_SIZE },
        { 15*TILE_SIZE,  4*TILE_SIZE, 22*TILE_SIZE,  4*TILE_SIZE },
        {  8*TILE_SIZE,  9*TILE_SIZE, 14*TILE_SIZE,  9*TILE_SIZE },
        { 15*TILE_SIZE,  9*TILE_SIZE, 22*TILE_SIZE,  9*TILE_SIZE },
        {  5*TILE_SIZE, 14*TILE_SIZE, 12*TILE_SIZE, 14*TILE_SIZE },
        { 15*TILE_SIZE, 14*TILE_SIZE, 22*TILE_SIZE, 14*TILE_SIZE },
    };

    for (int i = 0; i < m_enemy_count; i++) {
        m_enemies[i] = Entity(ENEMY_PATROL, 30, 30, 80, 2, 1, 2);
        m_enemies[i].position     = { patrol_paths[i].x1, patrol_paths[i].y1 };
        m_enemies[i].patrol_start = { patrol_paths[i].x1, patrol_paths[i].y1 };
        m_enemies[i].patrol_end   = { patrol_paths[i].x2, patrol_paths[i].y2 };
        m_enemies[i].detect_range = 180.0f;
        m_enemies[i].health       = 4;
        m_enemies[i].shoot_rate   = 1.8f;
        m_enemies[i].bullet_speed = 280.0f;
        m_enemies[i].anim_speed   = 0.15f;
        m_enemies[i].ai_state     = PATROLLING;
        m_enemies[i].texture      = m_enemy_tex[0];
        m_enemies[i].bullet_tex   = m_enemy_bullet_tex;

        while (m_map->check_solid_collision(m_enemies[i].get_rect())) {
            m_enemies[i].position.x     += TILE_SIZE;
            m_enemies[i].patrol_start.x += TILE_SIZE;
            m_enemies[i].patrol_end.x   += TILE_SIZE;
        }
    }

    setup_camera(m_map->get_pixel_width(), m_map->get_pixel_height());
}

void Level1::render(Shader& shader) {
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
    DrawText("SECTOR 1 - OUTER RIM", 16, GetScreenHeight() - 28, 16, DARKGRAY);
    EndDrawing();
}
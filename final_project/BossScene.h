#pragma once
#include "Scene.h"

enum BossPhase {
    BOSS_PHASE_1,
    BOSS_PHASE_2,
    BOSS_PHASE_3
};

struct BossShield {
    Vector2 position  = { 0, 0 };
    float   timer     = 0.0f;
    bool    is_active = false;
    float   width     = 160.0f;
    float   height    = 48.0f;

    Rectangle get_rect() const {
        return { position.x - width  * 0.5f,
                 position.y - height * 0.5f,
                 width, height };
    }
};

class BossScene : public Scene {
public:
    void initialise(GameData& data)       override;
    void process_input()                  override;
    void update(float dt, GameData& data) override;
    void render(Shader& shader)           override;

private:
    Map*    m_map = nullptr;
    Entity  m_player;
    Entity  m_boss;

    static constexpr int MAX_MINIONS  = 8;
    Entity  m_minions[MAX_MINIONS];
    int     m_minion_count = 0;

    static constexpr int MAX_POWERUPS = 6;
    Entity  m_powerups[MAX_POWERUPS];
    int     m_powerup_count = 0;

    static constexpr int   MAX_BOSS_SHIELDS = 5;
    static constexpr float SHIELD_DURATION  = 4.0f;
    BossShield  m_shields[MAX_BOSS_SHIELDS];
    Texture2D   m_shield_tex = { 0 };
    Texture2D m_bg_tex = { 0 };

    Texture2D m_player_tex      = { 0 };
    Texture2D m_bullet_tex      = { 0 };
    Texture2D m_boss_tex        = { 0 };
    Texture2D m_minion_tex      = { 0 };
    Texture2D m_powerup_tex     = { 0 };
    Texture2D m_boss_bullet_tex = { 0 };
    Font      m_font            = { 0 };
    Music     m_music           = { 0 };
    Sound     m_sfx_shoot       = { 0 };
    Sound     m_sfx_hit         = { 0 };
    Sound     m_sfx_die         = { 0 };

    BossPhase m_phase            = BOSS_PHASE_1;
    int       m_boss_max_hp      = 60;
    float     m_boss_shoot_timer = 0.0f;
    float     m_spin_angle       = 0.0f;
    float     m_minion_timer     = 0.0f;
    float     m_warning_timer    = 0.0f;
    bool      m_phase_warning    = false;

    float m_invincible_timer = 0.0f;
    bool  m_level_done       = false;
    float m_done_timer       = 0.0f;

    GameData* m_data_ptr = nullptr;

    void setup_camera();
    void place_shield();
    void update_shields(float dt);
    void render_shields() const;
    void shoot_ring(int count);
    void shoot_spread(int count, float base_angle);
    void spawn_minions();
    void update_boss(float dt, GameData& data);
    void handle_collisions(GameData& data);
    void draw_hud() const;
    void draw_boss_healthbar() const;
};
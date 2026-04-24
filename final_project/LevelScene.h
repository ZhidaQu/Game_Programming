#pragma once
#include "Scene.h"
#include <vector>
#include <string>

struct Shield {
    Vector2   position  = { 0, 0 };
    float     timer     = 0.0f;    
    bool      is_active = false;
    float     width     = 160.0f;
    float     height    = 48.0f;

    Rectangle get_rect() const {
        return { position.x - width * 0.5f,
                 position.y - height * 0.5f,
                 width, height };
    }
};

// LevelScene
class LevelScene : public Scene {
public:
    ~LevelScene() override;

    void process_input()                   override;
    void update(float dt, GameData& data)  override;
    void render(Shader& shader)            override;

protected:
    void setup_camera(int map_pixel_w, int map_pixel_h);

    Map*   m_map      = nullptr;
    Entity m_player;

    static constexpr int MAX_ENEMIES = 20;
    Entity m_enemies[MAX_ENEMIES];
    int    m_enemy_count = 0;

    static constexpr int MAX_POWERUPS = 20;
    Entity m_powerups[MAX_POWERUPS];
    int    m_powerup_count = 0;

    static constexpr int MAX_SHIELDS  = 5;
    static constexpr float SHIELD_DURATION = 4.0f;  
    Shield    m_shields[MAX_SHIELDS];
    int       m_shield_count    = 0;  
    Texture2D m_shield_tex      = { 0 };

    //  Textures / Audio 
    Texture2D m_player_tex  = { 0 };
    Texture2D m_bullet_tex  = { 0 };
    Texture2D m_powerup_tex = { 0 };
    Texture2D m_enemy_bullet_tex = { 0 };
    Texture2D m_enemy_tex[3]= {};
    Font      m_font        = { 0 };
    Music     m_music       = { 0 };
    Sound     m_sfx_shoot   = { 0 };
    Sound     m_sfx_hit     = { 0 };
    Sound     m_sfx_die     = { 0 };

    //  Win / Lose tracking 
    SceneID   m_win_scene   = SCENE_WIN;
    bool      m_level_done  = false;
    float     m_done_timer  = 0.0f;

    //  HUD 
    void draw_hud() const;
    float m_invincible_timer = 0.0f;

    GameData* m_data_ptr = nullptr;
protected:
    void render_shields() const;
    Texture2D m_bg_tex = { 0 };
private:
    void clamp_player_to_map();
    void handle_enemy_player_collision(GameData& data);
    void place_shield();          
    void update_shields(float dt);
};
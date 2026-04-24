#pragma once
#include "raylib.h"
#include "Map.h"  
#include <vector>
#include <string>

//AI State
enum AIState { IDLE, PATROLLING, CHASING, SHOOTING, DEAD };

enum EntityType { PLAYER, ENEMY_PATROL, ENEMY_CHASER, ENEMY_TURRET, ENEMY_WAVE, BULLET, POWERUP };

class Entity {
public:
    Vector2 position   = { 0.0f, 0.0f };
    Vector2 velocity   = { 0.0f, 0.0f };
    Vector2 movement   = { 0.0f, 0.0f };  
    float   speed      = 150.0f;
    float   rotation   = 0.0f;            
    bool just_died = false;

    float   width      = 32.0f;
    float   height     = 32.0f;
    Texture2D texture  = { 0 };
    Texture2D bullet_tex = { 0 };
    int   frame_cols   = 1;
    int   frame_rows   = 1;
    int   frame_index  = 0;               
    int   frame_count  = 1;              
    float anim_timer   = 0.0f;
    float anim_speed   = 0.12f;          

    EntityType entity_type = PLAYER;
    AIState    ai_state    = IDLE;
    bool       is_active   = true;
    int        health      = 3;
    int        max_health  = 3;
    float hit_flash_timer = 0.0f; 

    float shoot_cooldown     = 0.0f;
    float shoot_rate         = 0.35f;
    float bullet_speed       = 400.0f;
    float bullet_lifetime = 0.0f;
    bool is_homing = false;
    bool drop_checked = false;
    bool is_invincible = false;
    std::vector<Entity*> bullets;          

    Vector2 patrol_start = { 0, 0 };
    Vector2 patrol_end   = { 0, 0 };
    float   patrol_dir   = 1.0f;         
    float   ai_timer     = 0.0f;
    float   detect_range = 200.0f;        
    float   attack_range = 250.0f;

    Entity() = default;
    Entity(Texture2D tex, EntityType type, float w, float h,
           float spd, int cols, int rows, int frames);

    Entity(EntityType type, float w, float h,
       float spd, int cols, int rows, int frames);
    ~Entity();

    void update(float dt, Entity* player, Entity* enemies, int enemy_count, Map* map = nullptr);
    void render() const;

    void        shoot(float angle_deg);   
    void update_bullets(float dt, Entity* targets, int target_count, Map* map = nullptr);
    void        animate(float dt);
    void        face_direction(Vector2 dir); 
    bool        check_collision(const Entity& other) const;
    Rectangle   get_rect() const;
    void        take_damage(int dmg = 1);

    void ai_patrol(float dt);
    void ai_chase(Entity* player, float dt);
    void ai_turret(Entity* player, float dt);
    void ai_wave(Entity* player, float dt);

private:
    float angle_to(Vector2 target) const;
    float dist_to(Vector2 target)  const;
    static float vec2_length(Vector2 v);
    static Vector2 vec2_normalize(Vector2 v);
};

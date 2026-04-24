#include "Entity.h"
#include "Map.h"
#include <cmath>
#include <algorithm>

Entity::Entity(Texture2D tex, EntityType type, float w, float h,
               float spd, int cols, int rows, int frames)
    : speed(spd), width(w), height(h),
      texture(tex), frame_cols(cols), frame_rows(rows), frame_count(frames),
      entity_type(type) {}

Entity::Entity(EntityType type, float w, float h,
               float spd, int cols, int rows, int frames)
    : speed(spd), width(w), height(h),
      frame_cols(cols), frame_rows(rows), frame_count(frames),
      entity_type(type) {}

Entity::~Entity() {
    for (Entity* b : bullets) delete b;
    bullets.clear();
}

Rectangle Entity::get_rect() const {
    return { position.x - width * 0.5f, position.y - height * 0.5f, width, height };
}

bool Entity::check_collision(const Entity& other) const {
    if (!is_active || !other.is_active) return false;
    return CheckCollisionRecs(get_rect(), other.get_rect());
}

void Entity::take_damage(int dmg) {
    health -= dmg;
    if (health <= 0) {
        health    = 0;
        is_active = false;
        ai_state  = DEAD;
        just_died = true;
    }
    hit_flash_timer = 0.5f;
}

float Entity::vec2_length(Vector2 v) {
    return sqrtf(v.x * v.x + v.y * v.y);
}
Vector2 Entity::vec2_normalize(Vector2 v) {
    float len = vec2_length(v);
    if (len < 0.0001f) return { 0, 0 };
    return { v.x / len, v.y / len };
}
float Entity::angle_to(Vector2 target) const {
    float dx = target.x - position.x;
    float dy = target.y - position.y;
    return atan2f(dy, dx) * (180.0f / 3.14159265f);
}
float Entity::dist_to(Vector2 target) const {
    float dx = target.x - position.x;
    float dy = target.y - position.y;
    return sqrtf(dx * dx + dy * dy);
}

void Entity::face_direction(Vector2 dir) {
    if (vec2_length(dir) < 0.001f) return;
    rotation = atan2f(dir.y, dir.x) * (180.0f / 3.14159265f) + 90.0f;
}

void Entity::animate(float dt) {
    if (frame_count <= 1) return;
    anim_timer += dt;
    if (anim_timer >= anim_speed) {
        anim_timer  = 0.0f;
        frame_index = (frame_index + 1) % frame_count;
    }
}

void Entity::shoot(float angle_deg) {
    if (shoot_cooldown > 0.0f) return;
    shoot_cooldown = shoot_rate;

    Entity* b      = new Entity();
    b->entity_type = BULLET;
    b->is_active   = true;
    b->width       = 24.0f;   
    b->height      = 24.0f;
    b->texture     = bullet_tex;

    float rad    = angle_deg * 3.14159265f / 180.0f;
    float offset = width * 0.5f + 10.0f;
    b->position  = {
        position.x + cosf(rad) * offset,
        position.y + sinf(rad) * offset
    };

    b->velocity = { cosf(rad) * bullet_speed, sinf(rad) * bullet_speed };
    b->rotation = angle_deg + 90.0f;
    bullets.push_back(b);
}

void Entity::update_bullets(float dt, Entity* targets, int target_count, Map* map) {
    for (Entity* b : bullets) {
        if (!b->is_active) continue;

        if (b->bullet_lifetime > 0.0f) {
            b->bullet_lifetime -= dt;
            if (b->bullet_lifetime <= 0.0f) {
                b->is_active = false;
                continue;
            }
        }

        if (b->is_homing && targets != nullptr && target_count > 0) {
            if (targets[0].is_active) {
                float dx  = targets[0].position.x - b->position.x;
                float dy  = targets[0].position.y - b->position.y;
                float len = sqrtf(dx * dx + dy * dy);
                if (len > 0.01f) {
                    float spd  = sqrtf(b->velocity.x * b->velocity.x +
                                       b->velocity.y * b->velocity.y);
                    float turn = 0.08f;
                    b->velocity.x = b->velocity.x * (1.0f - turn) + (dx / len) * spd * turn;
                    b->velocity.y = b->velocity.y * (1.0f - turn) + (dy / len) * spd * turn;
                }
            }
        }

        float move_x     = b->velocity.x * dt;
        float move_y     = b->velocity.y * dt;
        float total_dist = sqrtf(move_x * move_x + move_y * move_y);
        int   steps      = (int)(total_dist / 4.0f) + 1;
        float step_x     = move_x / steps;
        float step_y     = move_y / steps;

        bool hit_wall = false;
        for (int s = 0; s < steps; s++) {
            b->position.x += step_x;
            b->position.y += step_y;

            if (map != nullptr) {
                Rectangle point = { b->position.x - 2, b->position.y - 2, 4, 4 };
                if (map->check_solid_collision(point)) {
                    b->is_active = false;
                    hit_wall     = true;
                    break;
                }
            }
        }
        if (hit_wall) continue;

        if (b->position.x < -100 || b->position.x > 5000 ||
            b->position.y < -100 || b->position.y > 5000) {
            b->is_active = false;
            continue;
        }

        if (targets == nullptr) continue;
        for (int i = 0; i < target_count; i++) {
            if (!targets[i].is_active) continue;
            if (b->check_collision(targets[i])) {
                if (!targets[i].is_invincible) {
                    targets[i].take_damage(1);
                    b->is_active = false;
                }
                break;
            }
        }
    }

    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
            [](Entity* b) {
                bool dead = !b->is_active;
                if (dead) delete b;
                return dead;
            }),
        bullets.end());
}

void Entity::ai_patrol(float dt) {
    ai_state = PATROLLING;
    Vector2 target = (patrol_dir > 0) ? patrol_end : patrol_start;
    Vector2 dir    = { target.x - position.x, target.y - position.y };
    float   dist   = vec2_length(dir);
    if (dist < 8.0f) { patrol_dir *= -1.0f; return; }
    dir = vec2_normalize(dir);
    face_direction(dir);
    position.x += dir.x * speed * dt;
    position.y += dir.y * speed * dt;
}

void Entity::ai_chase(Entity* player, float dt) {
    if (!player || !player->is_active) return;
    ai_state = CHASING;
    Vector2 dir = { player->position.x - position.x,
                    player->position.y - position.y };
    dir = vec2_normalize(dir);
    face_direction(dir);
    position.x += dir.x * speed * dt;
    position.y += dir.y * speed * dt;
}

void Entity::ai_turret(Entity* player, float dt) {
    if (!player || !player->is_active) return;
    ai_state = SHOOTING;
    rotation = angle_to(player->position) + 90.0f;
    shoot_cooldown -= dt;
    if (shoot_cooldown <= 0.0f) {
        float ang = angle_to(player->position);
        shoot(ang);
        if (!bullets.empty()) {
            bullets.back()->is_homing       = true;
            bullets.back()->bullet_lifetime = 3.0f;
        }
        shoot_cooldown = shoot_rate;
    }
}

void Entity::ai_wave(Entity* player, float dt) {
    if (!player || !player->is_active) return;
    ai_state = CHASING;

    Vector2 dir = { player->position.x - position.x,
                    player->position.y - position.y };
    dir = vec2_normalize(dir);

    Vector2 perp = { -dir.y, dir.x };

    ai_timer += dt;
    float wave = sinf(ai_timer * 4.0f) * 60.0f;

    position.x += (dir.x * speed + perp.x * wave) * dt;
    position.y += (dir.y * speed + perp.y * wave) * dt;

    face_direction(dir);
}

void Entity::update(float dt, Entity* player, Entity* enemies, int enemy_count, Map* map) {
    if (!is_active) return;

    animate(dt);
    if (hit_flash_timer > 0.0f) hit_flash_timer -= dt;

    if (shoot_cooldown > 0.0f && entity_type != ENEMY_TURRET)
        shoot_cooldown -= dt;

    switch (entity_type) {

        case PLAYER: {
            if (vec2_length(movement) > 0.001f) {
                movement = vec2_normalize(movement);
                face_direction(movement);
            }
            position.x += movement.x * speed * dt;
            position.y += movement.y * speed * dt;
            movement = { 0, 0 };
            update_bullets(dt, enemies, enemy_count, map);
            break;
        }

        case ENEMY_PATROL: {
            float d = dist_to(player ? player->position : position);
            if (player && d < detect_range) {
                ai_chase(player, dt);
            } else {
                ai_patrol(dt);
            }
            update_bullets(dt, player, 1, map);
            break;
        }

        case ENEMY_CHASER: {
            ai_chase(player, dt);
            break;
        }

        case ENEMY_TURRET: {
            ai_timer += dt;
            if (player) ai_turret(player, dt);
            update_bullets(dt, player, 1, map);
            break;
        }

        case ENEMY_WAVE: {
            ai_wave(player, dt);
            update_bullets(dt, player, 1, map);
            break;
        }

        case BULLET:
            break;
        case POWERUP:
            break;
    }
}

void Entity::render() const {
    if (!is_active) return;

    if (entity_type != BULLET && texture.id != 0) {
        Rectangle src    = { 0, 0, (float)texture.width, (float)texture.height };
        Rectangle dst    = { position.x, position.y, width, height };
        Vector2   origin = { width * 0.5f, height * 0.5f };
        Color tint = WHITE;
        if (hit_flash_timer > 0.0f) {
            tint = ((int)(hit_flash_timer * 10.0f) % 2 == 0) ? RED : WHITE;
        }
        DrawTexturePro(texture, src, dst, origin, rotation, tint);
    } else {
        switch (entity_type) {
            case PLAYER: {
                Color tint = WHITE;
                if (hit_flash_timer > 0.0f) {
                    tint = ((int)(hit_flash_timer * 10.0f) % 2 == 0) ? RED : WHITE;
                }
                DrawPoly({position.x, position.y}, 3, 16, rotation, tint);
                break;
            }
            case ENEMY_PATROL:
                DrawRectanglePro({position.x, position.y, width, height},
                                 {width*0.5f, height*0.5f}, rotation, RED);
                break;
            case ENEMY_CHASER:
                DrawPoly({position.x, position.y}, 4, 14, rotation, ORANGE);
                break;
            case ENEMY_TURRET:
                DrawPoly({position.x, position.y}, 6, 16, rotation, PURPLE);
                break;
            case ENEMY_WAVE:
                DrawPoly({position.x, position.y}, 5, 14, rotation, YELLOW);
                break;
            case POWERUP:
                if (texture.id != 0) {
                    Rectangle src    = { 0, 0, (float)texture.width, (float)texture.height };
                    Rectangle dst    = { position.x, position.y, width, height };
                    Vector2   origin = { width * 0.5f, height * 0.5f };
                    DrawTexturePro(texture, src, dst, origin, rotation, WHITE);
                } else {
                    DrawCircleV({position.x, position.y}, 10, GREEN);
                    DrawCircleLines((int)position.x, (int)position.y, 13, LIME);
                }
                break;
            default:
                break;
        }
    }

    for (const Entity* b : bullets) {
        if (!b->is_active) continue;
        if (b->texture.id != 0) {
            float draw_w = b->width * 4.0f;
            float draw_h = b->height * 4.0f;
            Rectangle src    = { 0, 0, (float)b->texture.width, (float)b->texture.height };
            Rectangle dst    = { b->position.x, b->position.y, draw_w, draw_h };
            Vector2   origin = { draw_w * 0.5f, draw_h * 0.5f };
            DrawTexturePro(b->texture, src, dst, origin, b->rotation, WHITE);
        } else {
            DrawCircleV({b->position.x, b->position.y}, 8, YELLOW);
        }
    }
}
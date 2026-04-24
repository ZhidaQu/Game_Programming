#pragma once
#include "raylib.h"
#include "Entity.h"
#include "Map.h"

enum SceneID { SCENE_NONE = -1, SCENE_MENU, SCENE_LEVEL1, SCENE_LEVEL2, SCENE_LEVEL3,
               SCENE_BOSS, SCENE_BOSS_LOSE, SCENE_WIN, SCENE_LOSE };

struct GameData {
    int lives          = 3;
    int score          = 0;
    int shield_charges = 0;
};

class Scene {
public:
    virtual ~Scene() = default;

    virtual void initialise(GameData& data)      = 0;
    virtual void process_input()                 = 0;
    virtual void update(float dt, GameData& data)= 0;
    virtual void render(Shader& shader)          = 0;

    SceneID next_scene = SCENE_NONE;

protected:
    Camera2D m_camera = { 0 };
};
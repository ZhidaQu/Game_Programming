#pragma once
#include "raylib.h"

class Scene;

enum SceneID {
    SCENE_MENU,
    SCENE_LEVEL1,
    SCENE_LEVEL2,
    SCENE_LEVEL3,
    SCENE_WIN,
    SCENE_LOSE
};

class Game {
public:
    static const int SCREEN_W = 1280;
    static const int SCREEN_H = 720;

    int    lives;
    int    currentLevel;

    Scene* currentScene;
    Scene* nextScene;

    Game();
    ~Game();
    void SwitchScene(SceneID id);
    void ApplySceneSwitch();
};
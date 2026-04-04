#include "Game.h"
#include "Scene.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"

Game::Game()
    : lives(3), currentLevel(1),
      currentScene(nullptr), nextScene(nullptr)
{}

Game::~Game() {
    if (currentScene) { currentScene->Shutdown(); delete currentScene; }
    if (nextScene)    { nextScene->Shutdown();    delete nextScene;    }
}

void Game::SwitchScene(SceneID id) {
    Scene* s = nullptr;
    switch (id) {
        case SCENE_MENU:   s = new MenuScene(this);     break;
        case SCENE_LEVEL1: s = new Level1(this, lives); break;
        case SCENE_LEVEL2: s = new Level2(this, lives); break;
        case SCENE_LEVEL3: s = new Level3(this, lives); break;
        case SCENE_WIN:    s = new YouWinScene(this);   break;
        case SCENE_LOSE:   s = new YouLoseScene(this);  break;
    }
    nextScene = s;
}

void Game::ApplySceneSwitch() {
    if (!nextScene) return;
    if (currentScene) {
        currentScene->Shutdown();
        delete currentScene;
    }
    currentScene = nextScene;
    nextScene    = nullptr;
    currentScene->Initialize();
}
/**
* Author: Zhida Qu
* Assignment: Rise of the AI
* Date due: 2026-4-4, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/


#include "raylib.h"
#include "Game.h"
#include "Scene.h"

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(Game::SCREEN_W, Game::SCREEN_H, "Dungeon Quest");
    SetAudioStreamBufferSizeDefault(4096);
    InitAudioDevice();
    SetTargetFPS(144);

    Game game;
    game.SwitchScene(SCENE_MENU);
    game.ApplySceneSwitch();

    while (!WindowShouldClose()) {

        game.ApplySceneSwitch();

        game.currentScene->ProcessInput();

        float dt = GetFrameTime();
        if (dt > 0.05f) dt = 0.05f;
        game.currentScene->Update(dt);

        BeginDrawing();
            ClearBackground(BLACK);
            game.currentScene->Render();
        EndDrawing();
    }

    if (game.currentScene) {
        game.currentScene->Shutdown();
        delete game.currentScene;
        game.currentScene = nullptr;
    }
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
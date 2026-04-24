/**
* Author: Zhida Qu
* Assignment: Star Defender
* Date due: 2026/5/1, 2:00pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "raylib.h"
#include "raymath.h"
#include "Scene.h"
#include "MenuScene.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "BossScene.h"
#include "WinScene.h"

constexpr int   SCREEN_W      = 1280;
constexpr int   SCREEN_H      = 720;
constexpr int   TARGET_FPS    = 60;

constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;

Scene* make_scene(SceneID id);

int main() {
    InitWindow(SCREEN_W, SCREEN_H, "Star Defender");
    InitAudioDevice();
    SetTargetFPS(TARGET_FPS);
    Shader shader = LoadShader("shaders/vertex.glsl", "shaders/fragment.glsl");
    int loc_health = GetShaderLocation(shader, "u_health");
    int loc_time   = GetShaderLocation(shader, "u_time");

    GameData game_data;
    game_data.lives = 3;
    game_data.score = 0;
    Scene* current_scene = make_scene(SCENE_MENU);
    current_scene->initialise(game_data);

    float accumulator  = 0.0f;
    float elapsed_time = 0.0f;

    while (!WindowShouldClose()) {

        float frame_dt = GetFrameTime();
        elapsed_time  += frame_dt;

        current_scene->process_input();

        float health_ratio = (game_data.lives > 0)
                             ? (float)game_data.lives / 3.0f
                             : 0.0f;
        SetShaderValue(shader, loc_health, &health_ratio, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, loc_time,   &elapsed_time,  SHADER_UNIFORM_FLOAT);

        accumulator += frame_dt;
        while (accumulator >= FIXED_TIMESTEP) {
            current_scene->update(FIXED_TIMESTEP, game_data);
            accumulator -= FIXED_TIMESTEP;
        }

        current_scene->render(shader);

        if (current_scene->next_scene != SCENE_NONE) {
            SceneID next_id = current_scene->next_scene;
            delete current_scene;

            if (next_id == SCENE_MENU) {
                game_data.lives = 3;
                game_data.score = 0;
            }

            current_scene = make_scene(next_id);
            current_scene->initialise(game_data);
        }
    }

    delete current_scene;
    UnloadShader(shader);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}

Scene* make_scene(SceneID id) {
    switch (id) {
        case SCENE_MENU:   return new MenuScene();
        case SCENE_LEVEL1: return new Level1();
        case SCENE_LEVEL2: return new Level2();
        case SCENE_LEVEL3: return new Level3();
        case SCENE_BOSS:   return new BossScene();
        case SCENE_BOSS_LOSE: return new BossLoseScene();
        case SCENE_WIN:    return new WinScene();
        case SCENE_LOSE:   return new LoseScene();
        default:           return new MenuScene();
    }
}
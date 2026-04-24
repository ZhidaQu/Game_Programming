#include "MenuScene.h"

void MenuScene::initialise(GameData& data) {
    next_scene = SCENE_NONE;
    m_bg = LoadTexture("assets/background.png");
    m_music = LoadMusicStream("assets/audio/menu_music.mp3");
    SetMusicVolume(m_music, 0.5f);
    PlayMusicStream(m_music);
}

void MenuScene::process_input() {
    if (IsKeyPressed(KEY_ENTER)) next_scene = SCENE_LEVEL1;
    if (IsKeyPressed(KEY_Q))     CloseWindow();
}

void MenuScene::update(float dt, GameData& data) {
    UpdateMusicStream(m_music);
    m_blink += dt;
}

void MenuScene::render(Shader& shader) {
    BeginDrawing();
    ClearBackground(BLACK);
    if (m_bg.id != 0) {
        DrawTexturePro(m_bg,
            { 0, 0, (float)m_bg.width, (float)m_bg.height },
            { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() },
            { 0, 0 }, 0.0f, WHITE);
    }
    int sw = GetScreenWidth(), sh = GetScreenHeight();

    DrawText("STAR DEFENDER",      (sw - MeasureText("STAR DEFENDER", 52)) / 2,
             sh*0.25f, 52, SKYBLUE);
    DrawText("WASD: Move",         (sw - MeasureText("WASD: Move", 20)) / 2,
             sh*0.50f, 20, LIGHTGRAY);
    DrawText("LMB: Shoot  RMB: Shield",       (sw - MeasureText("LMB: Shoot  RMB: Shield", 20)) / 2,
             sh*0.55f, 20, LIGHTGRAY);
    DrawText("Destroy all enemies to advance", 
             (sw - MeasureText("Destroy all enemies to advance", 18)) / 2,
             sh*0.62f, 18, GRAY);
    if ((int)(m_blink * 2.0f) % 2 == 0)
        DrawText("Press ENTER to Start",
                 (sw - MeasureText("Press ENTER to Start", 24)) / 2,
                 sh*0.75f, 24, YELLOW);
    EndDrawing();
}
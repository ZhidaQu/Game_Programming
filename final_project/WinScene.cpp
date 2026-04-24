#include "WinScene.h"
#include <cstdio>
void WinScene::initialise(GameData& data) {
    next_scene = SCENE_NONE;
    m_timer    = 0.0f;
    m_score    = data.score;
    m_font     = LoadFont("assets/font.ttf");
    m_music    = LoadMusicStream("assets/audio/win_music.wav");
    m_bg = LoadTexture("assets/background.png");
    SetMusicVolume(m_music, 0.6f);
    PlayMusicStream(m_music);
}
void WinScene::process_input() {
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
        next_scene = SCENE_MENU;
    if (IsKeyPressed(KEY_Q)) CloseWindow();
}
void WinScene::update(float dt, GameData& data) {
    UpdateMusicStream(m_music);
    m_timer += dt;
}
void WinScene::render(Shader& /*shader*/) {
    BeginDrawing();
    ClearBackground({ 2, 10, 30, 255 });

    int sw = GetScreenWidth();
    int sh = GetScreenHeight();

    // Pulsing star field effect 
    for (int i = 0; i < 120; i++) {
        float x = (float)((i * 137 + 73)  % sw);
        float y = (float)((i * 251 + 113) % sh);
        float br = 100 + (int)(m_timer * 60 + i * 17) % 155;
        DrawPixel((int)x, (int)y, { (unsigned char)br, (unsigned char)br, 255, 255 });
    }

    const char* title = "MISSION COMPLETE";
    int tw = MeasureText(title, 54);
    DrawText(title, (sw - tw) / 2, sh / 2 - 90, 54, GREEN);

    char score_buf[64];
    snprintf(score_buf, sizeof(score_buf), "Final Score: %d", m_score);
    int scw = MeasureText(score_buf, 28);
    DrawText(score_buf, (sw - scw) / 2, sh / 2 - 20, 28, WHITE);

    const char* sub = "You defended the galaxy!";
    int subw = MeasureText(sub, 22);
    DrawText(sub, (sw - subw) / 2, sh / 2 + 20, 22, LIGHTGRAY);

    if ((int)(m_timer * 2) % 2 == 0) {
        const char* prompt = "Press ENTER to return to menu";
        int pw = MeasureText(prompt, 20);
        DrawText(prompt, (sw - pw) / 2, sh / 2 + 80, 20, YELLOW);
    }
    EndDrawing();
}

//  LoseScene.cpp
void LoseScene::initialise(GameData& data) {
    next_scene = SCENE_NONE;
    m_timer    = 0.0f;
    m_font     = LoadFont("assets/font.ttf");
    m_music    = LoadMusicStream("assets/audio/lose_music.wav");
    SetMusicVolume(m_music, 0.5f);
    PlayMusicStream(m_music);
}
void LoseScene::process_input() {
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
        next_scene = SCENE_MENU;
    if (IsKeyPressed(KEY_Q)) CloseWindow();
}
void LoseScene::update(float dt, GameData& data) {
    UpdateMusicStream(m_music);
    m_timer += dt;
}


void LoseScene::render(Shader& /*shader*/) {
    BeginDrawing();
    ClearBackground({ 20, 2, 2, 255 });

    if (m_bg.id != 0) {
        DrawTexturePro(m_bg,
            { 0, 0, (float)m_bg.width, (float)m_bg.height },
            { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() },
            { 0, 0 }, 0.0f, { 255, 255, 255, 150 });
    }
    int sw = GetScreenWidth();
    int sh = GetScreenHeight();

    const char* title = "SHIP DESTROYED";
    int tw = MeasureText(title, 54);
    DrawText(title, (sw - tw) / 2, sh / 2 - 80, 54, RED);

    const char* sub = "The galaxy has fallen...";
    int subw = MeasureText(sub, 22);
    DrawText(sub, (sw - subw) / 2, sh / 2 - 10, 22, LIGHTGRAY);

    if ((int)(m_timer * 2) % 2 == 0) {
        const char* prompt = "Press ENTER to return to menu";
        int pw = MeasureText(prompt, 20);
        DrawText(prompt, (sw - pw) / 2, sh / 2 + 60, 20, YELLOW);
    }
    EndDrawing();
}

// BossLoseScene
void BossLoseScene::initialise(GameData& data) {
    next_scene = SCENE_NONE;
    m_timer    = 0.0f;
    m_select   = 0;
    m_score    = data.score;
}

void BossLoseScene::process_input() {
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
        m_select = 0;
    if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))
        m_select = 1;

    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
        if (m_select == 0)
            next_scene = SCENE_BOSS;   
        else
            next_scene = SCENE_MENU;   
    }
    if (IsKeyPressed(KEY_Q)) CloseWindow();
}

void BossLoseScene::update(float dt, GameData& data) {
    m_timer += dt;
    if (next_scene == SCENE_BOSS) {
        data.lives = 3;
    }
}

void BossLoseScene::render(Shader& /*shader*/) {
    BeginDrawing();
    ClearBackground({ 15, 2, 2, 255 });

    int sw = GetScreenWidth();
    int sh = GetScreenHeight();

    const char* title = "DEFEATED BY BOSS";
    int tw = MeasureText(title, 48);
    DrawText(title, (sw - tw) / 2, sh * 0.2f, 48, RED);

    char buf[64];
    snprintf(buf, sizeof(buf), "Score: %d", m_score);
    int bw = MeasureText(buf, 24);
    DrawText(buf, (sw - bw) / 2, sh * 0.38f, 24, WHITE);

    const char* hint = "W/S to select    ENTER to confirm";
    int hw = MeasureText(hint, 18);
    DrawText(hint, (sw - hw) / 2, sh * 0.48f, 18, DARKGRAY);

    Color c0 = (m_select == 0) ? YELLOW : LIGHTGRAY;
    Color c1 = (m_select == 1) ? YELLOW : LIGHTGRAY;

    const char* opt0 = (m_select == 0) ? "> RETRY BOSS <" : "  RETRY BOSS  ";
    int ow0 = MeasureText(opt0, 32);
    DrawText(opt0, (sw - ow0) / 2, sh * 0.58f, 32, c0);

    const char* opt1 = (m_select == 1) ? "> GIVE UP - RETURN TO MENU <" 
                                        : "  GIVE UP - RETURN TO MENU  ";
    int ow1 = MeasureText(opt1, 32);
    DrawText(opt1, (sw - ow1) / 2, sh * 0.70f, 32, c1);

    EndDrawing();
}
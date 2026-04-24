//  WinScene.h
#pragma once
#include "Scene.h"

class WinScene : public Scene {
public:
    ~WinScene() override {
        UnloadMusicStream(m_music);
        UnloadFont(m_font);
    }
    void initialise(GameData& data)       override;
    void process_input()                  override;
    void update(float dt, GameData& data) override;
    void render(Shader& shader)           override;
private:
    Texture2D m_bg = { 0 };
    Font  m_font  = { 0 };
    Music m_music = { 0 };
    float m_timer = 0.0f;
    int   m_score = 0;
};

//  LoseScene.h
class LoseScene : public Scene {
public:
    ~LoseScene() override {
        UnloadMusicStream(m_music);
        UnloadFont(m_font);
    }
    void initialise(GameData& data)       override;
    void process_input()                  override;
    void update(float dt, GameData& data) override;
    void render(Shader& shader)           override;
private:
    Texture2D m_bg = { 0 };
    Font  m_font  = { 0 };
    Music m_music = { 0 };
    float m_timer = 0.0f;
};

class BossLoseScene : public Scene {
public:
    void initialise(GameData& data)       override;
    void process_input()                  override;
    void update(float dt, GameData& data) override;
    void render(Shader& shader)           override;
private:
    float m_timer    = 0.0f;
    int   m_select   = 0;     
    int   m_score    = 0;
};

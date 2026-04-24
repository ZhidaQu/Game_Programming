#pragma once
#include "Scene.h"

class MenuScene : public Scene {
public:
    void initialise(GameData& data)       override;
    void process_input()                  override;
    void update(float dt, GameData& data) override;
    void render(Shader& shader)           override;

private:
    Texture2D m_bg     = { 0 };
    Texture2D m_logo   = { 0 };
    Font      m_font   = { 0 };
    float     m_blink  = 0.0f;   
    Music     m_music  = { 0 };
};

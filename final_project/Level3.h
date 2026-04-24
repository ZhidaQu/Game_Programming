#pragma once
#include "LevelScene.h"

class Level3 : public LevelScene {
public:
    void initialise(GameData& data) override;
    void render(Shader& shader)     override;
};

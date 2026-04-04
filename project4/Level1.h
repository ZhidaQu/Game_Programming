#pragma once
#include "Scene.h"

class Level1 : public GameScene {
public:
    Level1(Game* g, int& livesRef);
    void BuildLevel() override;
};

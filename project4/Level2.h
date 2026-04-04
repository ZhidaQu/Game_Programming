#pragma once
#include "Scene.h"
class Level2 : public GameScene {
public:
    Level2(Game* g, int& livesRef);

    void BuildLevel() override;
};

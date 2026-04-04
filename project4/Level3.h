#pragma once
#include "Scene.h"
class Level3 : public GameScene {
public:
    Level3(Game* g, int& livesRef);

    void BuildLevel() override;
};

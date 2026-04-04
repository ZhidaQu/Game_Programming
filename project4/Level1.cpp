#include "Level1.h"

Level1::Level1(Game* g, int& livesRef) : GameScene(g, 1, livesRef) {}


void Level1::BuildLevel() {
    levelWidth = 2560.0f;
    enemies.clear();
    platforms.clear();
    enemies.reserve(10);
    platforms.reserve(10);

    platforms.push_back({{0,     640, 2560, 80}, DARKGREEN}); // ground
    platforms.push_back({{0,     520,  220, 25}, DARKGREEN}); // platform1
    platforms.push_back({{400,   460,  200, 25}, DARKGREEN}); // platform2
    platforms.push_back({{800,   400,  200, 25}, DARKGREEN}); // platform3
    platforms.push_back({{1200,  460,  200, 25}, DARKGREEN}); // platform4
    platforms.push_back({{1600,  380,  200, 25}, DARKGREEN}); // platform5
    platforms.push_back({{2000,  440,  200, 25}, DARKGREEN}); // platform6
    platforms.push_back({{2350,  300,  200, 25}, {0,180,80,255}}); // EXIT

    std::map<Direction, std::vector<int>> slimeAtlas = {
        { RIGHT, {0,1,2,3}               },
        { LEFT,  {8,9,10,11,12,13,14,15} },
        { DOWN,  {0,1,2,3}               },
        { UP,    {0,1,2,3}               }
    };
    std::map<Direction, std::vector<int>> skelAtlas = {
        { LEFT,  {6,7,8,9,10,11}     },
        { RIGHT, {12,13,14,15,16,17} },
        { DOWN,  {0,1,2,3,4,5}       },
        { UP,    {18,19,20,21,22,23} }
    };

    // Walker slime A
    {
        Entity e({200.0f, 610.0f}, {48.0f, 48.0f}, "",
                 ATLAS, {8.0f, 3.0f}, slimeAtlas, NPC);
        e.setTexture(slimeTex);
        e.setColliderDimensions({30.0f, 28.0f});
        e.setSpeed(65);
        e.setFrameSpeed(6);
        e.setAIType(WANDERER);
        e.setPatrol(0.0f, 600.0f);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(RIGHT);
        enemies.push_back(e);
    }

    // Follower skeleton
    {
        Entity e({1800.0f, 600.0f}, {44.0f, 60.0f}, "",
                 ATLAS, {6.0f, 10.0f}, skelAtlas, NPC);
        e.setTexture(skeletonTex);
        e.setColliderDimensions({18.0f, 38.0f});
        e.setSpeed(75);
        e.setFrameSpeed(7);
        e.setAIType(FOLLOWER);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(LEFT);
        enemies.push_back(e);
    }

    // Walker slime
    {
        Entity e({880.0f, 372.0f}, {48.0f, 48.0f}, "",
                 ATLAS, {8.0f, 3.0f}, slimeAtlas, NPC);
        e.setTexture(slimeTex);
        e.setColliderDimensions({30.0f, 28.0f});
        e.setSpeed(55);
        e.setFrameSpeed(5);
        e.setAIType(WANDERER);
        e.setPatrol(800.0f, 1000.0f);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(RIGHT);
        enemies.push_back(e);
    }
}
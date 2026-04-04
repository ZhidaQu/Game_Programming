#include "Level3.h"

Level3::Level3(Game* g, int& livesRef) : GameScene(g, 3, livesRef) {}

void Level3::BuildLevel() {
    levelWidth = 3840.0f;
    enemies.clear();
    platforms.clear();
    enemies.reserve(24);
    platforms.reserve(16);

    // Platforms
    platforms.push_back({{0,     640, 3840, 80}, DARKGREEN});
    platforms.push_back({{0,     560,  150, 25}, DARKGREEN});
    platforms.push_back({{300,   500,  100, 25}, DARKGREEN});
    platforms.push_back({{580,   440,  100, 25}, DARKGREEN});
    platforms.push_back({{860,   380,  100, 25}, DARKGREEN});
    platforms.push_back({{1140,  440,  130, 25}, DARKGREEN});
    platforms.push_back({{1450,  360,  130, 25}, DARKGREEN});
    platforms.push_back({{1750,  300,  130, 25}, DARKGREEN});
    platforms.push_back({{2050,  360,  130, 25}, DARKGREEN});
    platforms.push_back({{2350,  280,  130, 25}, DARKGREEN});
    platforms.push_back({{2650,  360,  130, 25}, DARKGREEN});
    platforms.push_back({{2950,  300,  130, 25}, DARKGREEN});
    platforms.push_back({{3250,  380,  130, 25}, DARKGREEN});
    platforms.push_back({{3550,  300,  150, 25}, {0,180,80,255}}); // EXIT

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

    // Skeleton (ground)
    {
        Entity e({700.0f, 600.0f}, {44.0f, 60.0f}, "",
                 ATLAS, {6.0f, 10.0f}, skelAtlas, NPC);
        e.setTexture(skeletonTex);
        e.setColliderDimensions({18.0f, 38.0f});
        e.setSpeed(110); e.setFrameSpeed(9);
        e.setAIType(FOLLOWER);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(LEFT);
        enemies.push_back(e);
    }
    {
        Entity e({1300.0f, 600.0f}, {44.0f, 60.0f}, "",
                 ATLAS, {6.0f, 10.0f}, skelAtlas, NPC);
        e.setTexture(skeletonTex);
        e.setColliderDimensions({18.0f, 38.0f});
        e.setSpeed(115); e.setFrameSpeed(9);
        e.setAIType(FOLLOWER);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(LEFT);
        enemies.push_back(e);
    }
    {
        Entity e({1900.0f, 600.0f}, {44.0f, 60.0f}, "",
                 ATLAS, {6.0f, 10.0f}, skelAtlas, NPC);
        e.setTexture(skeletonTex);
        e.setColliderDimensions({18.0f, 38.0f});
        e.setSpeed(118); e.setFrameSpeed(9);
        e.setAIType(FOLLOWER);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(LEFT);
        enemies.push_back(e);
    }
    {
        Entity e({2500.0f, 600.0f}, {44.0f, 60.0f}, "",
                 ATLAS, {6.0f, 10.0f}, skelAtlas, NPC);
        e.setTexture(skeletonTex);
        e.setColliderDimensions({18.0f, 38.0f});
        e.setSpeed(120); e.setFrameSpeed(10);
        e.setAIType(FOLLOWER);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(LEFT);
        enemies.push_back(e);
    }
    {
        Entity e({3000.0f, 600.0f}, {44.0f, 60.0f}, "",
                 ATLAS, {6.0f, 10.0f}, skelAtlas, NPC);
        e.setTexture(skeletonTex);
        e.setColliderDimensions({18.0f, 38.0f});
        e.setSpeed(125); e.setFrameSpeed(10);
        e.setAIType(FOLLOWER);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(LEFT);
        enemies.push_back(e);
    }
    {
        Entity e({3500.0f, 600.0f}, {44.0f, 60.0f}, "",
                 ATLAS, {6.0f, 10.0f}, skelAtlas, NPC);
        e.setTexture(skeletonTex);
        e.setColliderDimensions({18.0f, 38.0f});
        e.setSpeed(130); e.setFrameSpeed(10);
        e.setAIType(FOLLOWER);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(LEFT);
        enemies.push_back(e);
    }

    // Skeleton (platform)
    {
        Entity e({350.0f, 462.0f}, {44.0f, 60.0f}, "",
                 ATLAS, {6.0f, 10.0f}, skelAtlas, NPC);
        e.setTexture(skeletonTex);
        e.setColliderDimensions({18.0f, 38.0f});
        e.setSpeed(100); e.setFrameSpeed(8);
        e.setAIType(WANDERER);
        e.setPatrol(300.0f, 400.0f);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(LEFT);
        enemies.push_back(e);
    }
    {
        Entity e({910.0f, 342.0f}, {44.0f, 60.0f}, "",
                 ATLAS, {6.0f, 10.0f}, skelAtlas, NPC);
        e.setTexture(skeletonTex);
        e.setColliderDimensions({18.0f, 38.0f});
        e.setSpeed(105); e.setFrameSpeed(9);
        e.setAIType(WANDERER);
        e.setPatrol(860.0f, 960.0f);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(LEFT);
        enemies.push_back(e);
    }
    {
        Entity e({1515.0f, 322.0f}, {44.0f, 60.0f}, "",
                 ATLAS, {6.0f, 10.0f}, skelAtlas, NPC);
        e.setTexture(skeletonTex);
        e.setColliderDimensions({18.0f, 38.0f});
        e.setSpeed(108); e.setFrameSpeed(9);
        e.setAIType(WANDERER);
        e.setPatrol(1450.0f, 1580.0f);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(LEFT);
        enemies.push_back(e);
    }
    {
        Entity e({2115.0f, 322.0f}, {44.0f, 60.0f}, "",
                 ATLAS, {6.0f, 10.0f}, skelAtlas, NPC);
        e.setTexture(skeletonTex);
        e.setColliderDimensions({18.0f, 38.0f});
        e.setSpeed(110); e.setFrameSpeed(9);
        e.setAIType(WANDERER);
        e.setPatrol(2050.0f, 2180.0f);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(LEFT);
        enemies.push_back(e);
    }
    {
        Entity e({2715.0f, 322.0f}, {44.0f, 60.0f}, "",
                 ATLAS, {6.0f, 10.0f}, skelAtlas, NPC);
        e.setTexture(skeletonTex);
        e.setColliderDimensions({18.0f, 38.0f});
        e.setSpeed(112); e.setFrameSpeed(9);
        e.setAIType(WANDERER);
        e.setPatrol(2650.0f, 2780.0f);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(LEFT);
        enemies.push_back(e);
    }
    {
        Entity e({3315.0f, 342.0f}, {44.0f, 60.0f}, "",
                 ATLAS, {6.0f, 10.0f}, skelAtlas, NPC);
        e.setTexture(skeletonTex);
        e.setColliderDimensions({18.0f, 38.0f});
        e.setSpeed(115); e.setFrameSpeed(9);
        e.setAIType(WANDERER);
        e.setPatrol(3250.0f, 3380.0f);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(LEFT);
        enemies.push_back(e);
    }

    // Slime (platform)
    {
        Entity e({60.0f, 532.0f}, {48.0f, 48.0f}, "",
                 ATLAS, {8.0f, 3.0f}, slimeAtlas, NPC);
        e.setTexture(slimeTex);
        e.setColliderDimensions({30.0f, 28.0f});
        e.setSpeed(95); e.setFrameSpeed(8);
        e.setAIType(WANDERER);
        e.setPatrol(0.0f, 150.0f);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(RIGHT);
        enemies.push_back(e);
    }
    {
        Entity e({630.0f, 412.0f}, {48.0f, 48.0f}, "",
                 ATLAS, {8.0f, 3.0f}, slimeAtlas, NPC);
        e.setTexture(slimeTex);
        e.setColliderDimensions({30.0f, 28.0f});
        e.setSpeed(100); e.setFrameSpeed(8);
        e.setAIType(WANDERER);
        e.setPatrol(580.0f, 680.0f);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(RIGHT);
        enemies.push_back(e);
    }
    {
        Entity e({1205.0f, 412.0f}, {48.0f, 48.0f}, "",
                 ATLAS, {8.0f, 3.0f}, slimeAtlas, NPC);
        e.setTexture(slimeTex);
        e.setColliderDimensions({30.0f, 28.0f});
        e.setSpeed(105); e.setFrameSpeed(8);
        e.setAIType(WANDERER);
        e.setPatrol(1140.0f, 1270.0f);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(RIGHT);
        enemies.push_back(e);
    }
    {
        Entity e({1815.0f, 272.0f}, {48.0f, 48.0f}, "",
                 ATLAS, {8.0f, 3.0f}, slimeAtlas, NPC);
        e.setTexture(slimeTex);
        e.setColliderDimensions({30.0f, 28.0f});
        e.setSpeed(108); e.setFrameSpeed(8);
        e.setAIType(WANDERER);
        e.setPatrol(1750.0f, 1880.0f);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(RIGHT);
        enemies.push_back(e);
    }
    {
        Entity e({2415.0f, 252.0f}, {48.0f, 48.0f}, "",
                 ATLAS, {8.0f, 3.0f}, slimeAtlas, NPC);
        e.setTexture(slimeTex);
        e.setColliderDimensions({30.0f, 28.0f});
        e.setSpeed(110); e.setFrameSpeed(9);
        e.setAIType(WANDERER);
        e.setPatrol(2350.0f, 2480.0f);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(RIGHT);
        enemies.push_back(e);
    }
    {
        Entity e({3015.0f, 272.0f}, {48.0f, 48.0f}, "",
                 ATLAS, {8.0f, 3.0f}, slimeAtlas, NPC);
        e.setTexture(slimeTex);
        e.setColliderDimensions({30.0f, 28.0f});
        e.setSpeed(112); e.setFrameSpeed(9);
        e.setAIType(WANDERER);
        e.setPatrol(2950.0f, 3080.0f);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(RIGHT);
        enemies.push_back(e);
    }

    // Flyer
    {
        Entity e({1000.0f, 200.0f}, {48.0f, 48.0f}, "",
                 ATLAS, {8.0f, 3.0f}, slimeAtlas, NPC);
        e.setTexture(slimeTex);
        e.setColliderDimensions({30.0f, 28.0f});
        e.setSpeed(110); e.setFrameSpeed(8);
        e.setAIType(FLYER_AI);
        e.setFlyOffset(0.0f);
        e.setAcceleration({0.0f, 0.0f});
        e.setDirection(RIGHT);
        enemies.push_back(e);
    }
    {
        Entity e({2800.0f, 200.0f}, {48.0f, 48.0f}, "",
                 ATLAS, {8.0f, 3.0f}, slimeAtlas, NPC);
        e.setTexture(slimeTex);
        e.setColliderDimensions({30.0f, 28.0f});
        e.setSpeed(120); e.setFrameSpeed(8);
        e.setAIType(FLYER_AI);
        e.setFlyOffset(1.5f);
        e.setAcceleration({0.0f, 0.0f});
        e.setDirection(RIGHT);
        enemies.push_back(e);
    }
}
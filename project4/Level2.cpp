#include "Level2.h"

Level2::Level2(Game* g, int& livesRef) : GameScene(g, 2, livesRef) {}

void Level2::BuildLevel() {
    levelWidth = 3200.0f;
    enemies.clear();
    platforms.clear();
    enemies.reserve(16);
    platforms.reserve(12);

    platforms.push_back({{0,     640, 3200, 80}, DARKGREEN}); // ground
    platforms.push_back({{0,     530,  200, 25}, DARKGREEN}); // platform1
    platforms.push_back({{350,   470,  160, 25}, DARKGREEN}); // platform2
    platforms.push_back({{700,   400,  140, 25}, DARKGREEN}); // platform3
    platforms.push_back({{1050,  470,  160, 25}, DARKGREEN}); // platform4
    platforms.push_back({{1400,  400,  160, 25}, DARKGREEN}); // platform5
    platforms.push_back({{1750,  330,  160, 25}, DARKGREEN}); // platform6
    platforms.push_back({{2100,  400,  140, 25}, DARKGREEN}); // platform7
    platforms.push_back({{2450,  330,  160, 25}, DARKGREEN}); // platform8
    platforms.push_back({{2800,  400,  160, 25}, DARKGREEN}); // platform9
    platforms.push_back({{3000,  300,  160, 25}, {0,180,80,255}}); // EXIT

    std::map<Direction, std::vector<int>> slimeAtlas = {
        { RIGHT, {0,1,2,3}               },
        { LEFT,  {8,9,10,11,12,13,14,15} },
        { DOWN,  {0,1,2,3}               },
        { UP,    {0,1,2,3}               }
    };

    // Walker slime 
    {
        Entity e({1100.0f, 610.0f}, {48.0f, 48.0f}, "",
                 ATLAS, {8.0f, 3.0f}, slimeAtlas, NPC);
        e.setTexture(slimeTex);
        e.setColliderDimensions({30.0f, 28.0f});
        e.setSpeed(90);
        e.setFrameSpeed(7);
        e.setAIType(WANDERER);
        e.setPatrol(800.0f, 1500.0f);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(RIGHT);
        enemies.push_back(e);
    }

    // Walker slime 
    {
        Entity e({2300.0f, 610.0f}, {48.0f, 48.0f}, "",
                 ATLAS, {8.0f, 3.0f}, slimeAtlas, NPC);
        e.setTexture(slimeTex);
        e.setColliderDimensions({30.0f, 28.0f});
        e.setSpeed(95);
        e.setFrameSpeed(7);
        e.setAIType(WANDERER);
        e.setPatrol(2000.0f, 2900.0f);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(LEFT);
        enemies.push_back(e);
    }
    {
        Entity e({80.0f, 502.0f}, {48.0f, 48.0f}, "",
                 ATLAS, {8.0f, 3.0f}, slimeAtlas, NPC);
        e.setTexture(slimeTex);
        e.setColliderDimensions({30.0f, 28.0f});
        e.setSpeed(70);
        e.setFrameSpeed(6);
        e.setAIType(WANDERER);
        e.setPatrol(0.0f, 200.0f);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(RIGHT);
        enemies.push_back(e);
    }
    {
        Entity e({430.0f, 442.0f}, {48.0f, 48.0f}, "",
                 ATLAS, {8.0f, 3.0f}, slimeAtlas, NPC);
        e.setTexture(slimeTex);
        e.setColliderDimensions({30.0f, 28.0f});
        e.setSpeed(72);
        e.setFrameSpeed(6);
        e.setAIType(WANDERER);
        e.setPatrol(350.0f, 510.0f);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(RIGHT);
        enemies.push_back(e);
    }

    {
        Entity e({760.0f, 372.0f}, {48.0f, 48.0f}, "",
                 ATLAS, {8.0f, 3.0f}, slimeAtlas, NPC);
        e.setTexture(slimeTex);
        e.setColliderDimensions({30.0f, 28.0f});
        e.setSpeed(75);
        e.setFrameSpeed(6);
        e.setAIType(WANDERER);
        e.setPatrol(700.0f, 840.0f);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(RIGHT);
        enemies.push_back(e);
    }
    {
        Entity e({1130.0f, 442.0f}, {48.0f, 48.0f}, "",
                 ATLAS, {8.0f, 3.0f}, slimeAtlas, NPC);
        e.setTexture(slimeTex);
        e.setColliderDimensions({30.0f, 28.0f});
        e.setSpeed(78);
        e.setFrameSpeed(6);
        e.setAIType(WANDERER);
        e.setPatrol(1050.0f, 1210.0f);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(LEFT);
        enemies.push_back(e);
    }
    {
        Entity e({1480.0f, 372.0f}, {48.0f, 48.0f}, "",
                 ATLAS, {8.0f, 3.0f}, slimeAtlas, NPC);
        e.setTexture(slimeTex);
        e.setColliderDimensions({30.0f, 28.0f});
        e.setSpeed(80);
        e.setFrameSpeed(7);
        e.setAIType(WANDERER);
        e.setPatrol(1400.0f, 1560.0f);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(LEFT);
        enemies.push_back(e);
    }

    {
        Entity e({1830.0f, 302.0f}, {48.0f, 48.0f}, "",
                 ATLAS, {8.0f, 3.0f}, slimeAtlas, NPC);
        e.setTexture(slimeTex);
        e.setColliderDimensions({30.0f, 28.0f});
        e.setSpeed(82);
        e.setFrameSpeed(7);
        e.setAIType(WANDERER);
        e.setPatrol(1750.0f, 1910.0f);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(RIGHT);
        enemies.push_back(e);
    }

    {
        Entity e({2170.0f, 372.0f}, {48.0f, 48.0f}, "",
                 ATLAS, {8.0f, 3.0f}, slimeAtlas, NPC);
        e.setTexture(slimeTex);
        e.setColliderDimensions({30.0f, 28.0f});
        e.setSpeed(85);
        e.setFrameSpeed(7);
        e.setAIType(WANDERER);
        e.setPatrol(2100.0f, 2240.0f);
        e.setAcceleration({0.0f, 980.0f});
        e.setDirection(LEFT);
        enemies.push_back(e);
    }

    // Flyer Follower A
    {
        Entity e({500.0f, 200.0f}, {48.0f, 48.0f}, "",
                 ATLAS, {8.0f, 3.0f}, slimeAtlas, NPC);
        e.setTexture(slimeTex);
        e.setColliderDimensions({30.0f, 28.0f});
        e.setSpeed(85);
        e.setFrameSpeed(7);
        e.setAIType(FLYER_AI);
        e.setFlyOffset(0.0f);
        e.setAcceleration({0.0f, 0.0f});
        e.setDirection(RIGHT);
        enemies.push_back(e);
    }

    // Flyer Follower B
    {
        Entity e({1100.0f, 180.0f}, {48.0f, 48.0f}, "",
                 ATLAS, {8.0f, 3.0f}, slimeAtlas, NPC);
        e.setTexture(slimeTex);
        e.setColliderDimensions({30.0f, 28.0f});
        e.setSpeed(88);
        e.setFrameSpeed(7);
        e.setAIType(FLYER_AI);
        e.setFlyOffset(0.8f);
        e.setAcceleration({0.0f, 0.0f});
        e.setDirection(LEFT);
        enemies.push_back(e);
    }

    // Flyer Follower C
    {
        Entity e({1900.0f, 200.0f}, {48.0f, 48.0f}, "",
                 ATLAS, {8.0f, 3.0f}, slimeAtlas, NPC);
        e.setTexture(slimeTex);
        e.setColliderDimensions({30.0f, 28.0f});
        e.setSpeed(90);
        e.setFrameSpeed(7);
        e.setAIType(FLYER_AI);
        e.setFlyOffset(1.6f);
        e.setAcceleration({0.0f, 0.0f});
        e.setDirection(RIGHT);
        enemies.push_back(e);
    }

    // Flyer Follower D
    {
        Entity e({2700.0f, 180.0f}, {48.0f, 48.0f}, "",
                 ATLAS, {8.0f, 3.0f}, slimeAtlas, NPC);
        e.setTexture(slimeTex);
        e.setColliderDimensions({30.0f, 28.0f});
        e.setSpeed(92);
        e.setFrameSpeed(7);
        e.setAIType(FLYER_AI);
        e.setFlyOffset(2.4f);
        e.setAcceleration({0.0f, 0.0f});
        e.setDirection(LEFT);
        enemies.push_back(e);
    }
}
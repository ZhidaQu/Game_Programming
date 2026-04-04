#pragma once
#include "raylib.h"
#include "Entity.h"
#include "Map.h"
#include <vector>

class Game;

struct Platform {
    Rectangle rect;
    Color     color;
};

// Base Scene
class Scene {
public:
    Game* game;
    explicit Scene(Game* g) : game(g) {}
    virtual ~Scene() {}
    virtual void Initialize()            = 0;
    virtual void ProcessInput()          = 0;  
    virtual void Update(float deltaTime) = 0;
    virtual void Render()                = 0;
    virtual void Shutdown()              = 0;
};

// MenuScene
class MenuScene : public Scene {
public:
    float titlePulse, starTimer;
    float stars[50][2];

    Music menuMusic   = {0};
    bool  musicLoaded = false;

    explicit MenuScene(Game* g);
    void Initialize()    override;
    void ProcessInput()  override;
    void Update(float dt) override;
    void Render()        override;
    void Shutdown()      override;
};

// GameScene
class GameScene : public Scene {
public:
    int   level;
    int&  livesRef_;

    Entity              player;
    std::vector<Entity> enemies;
    std::vector<Platform> platforms;

    Texture2D playerTex;
    Texture2D skeletonTex;
    Texture2D slimeTex;
    Texture2D tilesetTex;

    Music bgMusic;
    Sound jumpSound, hitSound, deathSound;
    bool  musicLoaded, soundLoaded;

    float hurtFlash;
    bool  levelComplete;
    float completeTimer;
    bool  onGround;

    Camera2D camera;
    float    levelWidth;
    float mPrevTicks = 0.0f;
    float mTimeAccum  = 0.0f;
    static constexpr float FIXED_TS = 1.0f / 60.0f;

    bool inputLeft  = false;
    bool inputRight = false;
    bool inputJump  = false;

    GameScene(Game* g, int lvl, int& livesRef);

    virtual void BuildLevel() = 0;

    void Initialize()    override;
    void ProcessInput()  override;
    void Update(float dt) override;
    void Render()        override;
    void Shutdown()      override;

    void ResetPlayer();
    void DrawHUD();
    void DrawPlatforms();
};

// YouWinScene
class YouWinScene : public Scene {
public:
    float timer;
    explicit YouWinScene(Game* g);
    void Initialize()    override;
    void ProcessInput()  override;
    void Update(float dt) override;
    void Render()        override;
    void Shutdown()      override;
};

// YouLoseScene
class YouLoseScene : public Scene {
public:
    float timer;
    explicit YouLoseScene(Game* g);
    void Initialize()    override;
    void ProcessInput()  override;
    void Update(float dt) override;
    void Render()        override;
    void Shutdown()      override;
};
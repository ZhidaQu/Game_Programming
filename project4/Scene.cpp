#include "Scene.h"
#include "Game.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>

// MenuScene
MenuScene::MenuScene(Game* g) : Scene(g), titlePulse(0), starTimer(0) {
    for (int i = 0; i < 50; i++) {
        stars[i][0] = (float)(rand() % Game::SCREEN_W);
        stars[i][1] = (float)(rand() % Game::SCREEN_H);
    }
}

void MenuScene::Initialize() {
    game->lives        = 3;
    game->currentLevel = 1;
    titlePulse         = 0;

    if (FileExists("assets/audio/menu.ogg")) {
        menuMusic = LoadMusicStream("assets/audio/menu.ogg");
        SetMusicVolume(menuMusic, 0.4f);
        PlayMusicStream(menuMusic);
        musicLoaded = true;
    }
}

void MenuScene::ProcessInput() {
    if (IsKeyPressed(KEY_ENTER)) game->SwitchScene(SCENE_LEVEL1);
    if (IsKeyPressed(KEY_ONE))   game->SwitchScene(SCENE_LEVEL1);
    if (IsKeyPressed(KEY_TWO))   game->SwitchScene(SCENE_LEVEL2);
    if (IsKeyPressed(KEY_THREE)) game->SwitchScene(SCENE_LEVEL3);
}

void MenuScene::Update(float dt) {
    titlePulse += dt * 2;
    starTimer  += dt;
    if (musicLoaded) UpdateMusicStream(menuMusic);
}

void MenuScene::Render() {
    DrawRectangleGradientV(0, 0, Game::SCREEN_W, Game::SCREEN_H,
                           {10,10,40,255}, {20,25,70,255});
    // Stars
    for (int i = 0; i < 50; i++) {
        float t = (sinf(starTimer * 3 + i) + 1) * 0.5f;
        unsigned char b = (unsigned char)(120 + t * 135);
        DrawPixel((int)stars[i][0], (int)stars[i][1], {b,b,b,255});
    }
    // Title
    float sc  = 1 + 0.05f * sinf(titlePulse);
    int   fs  = (int)(56 * sc);
    const char* title = "DUNGEON QUEST";
    int tw = MeasureText(title, fs);
    DrawText(title, Game::SCREEN_W/2 - tw/2 + 3, 133, fs, {50,0,80,200});
    DrawText(title, Game::SCREEN_W/2 - tw/2,     130, fs, {220,180,255,255});
    // Subtitle
    const char* sub = "A Raylib Adventure";
    int sw = MeasureText(sub, 22);
    DrawText(sub, Game::SCREEN_W/2 - sw/2, 200, 22, {160,120,220,255});
    // Prompt
    float al = (sinf(titlePulse * 1.5f) + 1) * 0.5f;
    const char* p = "Press ENTER to Start";
    int pw = MeasureText(p, 28);
    DrawText(p, Game::SCREEN_W/2 - pw/2, 320, 28,
             {255,255,255,(unsigned char)(150 + al * 105)});
    // Controls hint
    DrawText("WASD Keys to Move",
             10, Game::SCREEN_H - 60, 16, {150,150,200,200});
    DrawRectangleLinesEx({20,20,(float)Game::SCREEN_W-40,
                          (float)Game::SCREEN_H-40}, 2, {100,60,160,180});
}

void MenuScene::Shutdown() {
    if (musicLoaded) {
        StopMusicStream(menuMusic);
        UnloadMusicStream(menuMusic);
        musicLoaded = false;
    }
}

// GameScene
GameScene::GameScene(Game* g, int lvl, int& livesRef)
    : Scene(g), level(lvl), livesRef_(livesRef),
      musicLoaded(false), soundLoaded(false),
      hurtFlash(0), levelComplete(false), completeTimer(0),
      onGround(false), levelWidth(2560.0f)
{
    playerTex = {0}; skeletonTex = {0}; slimeTex = {0}; tilesetTex = {0};
    bgMusic = {0}; jumpSound = {0}; hitSound = {0}; deathSound = {0};
    camera  = {0};
}

void GameScene::ResetPlayer() {
    player.setPosition({128.0f, 560.0f});
    player.setVelocity({0, 0});
    player.activate();
}

void GameScene::Initialize() {
    // Load textures
    playerTex   = LoadTexture("assets/images/player.png");
    skeletonTex = LoadTexture("assets/images/skeleton.png");
    slimeTex    = LoadTexture("assets/images/slime_green.png");
    tilesetTex  = LoadTexture("assets/images/tileset.png");

    // Load audio
    if (FileExists("assets/audio/jump.wav")) {
        jumpSound   = LoadSound("assets/audio/jump.wav");
        hitSound    = LoadSound("assets/audio/hit.wav");
        deathSound  = LoadSound("assets/audio/death.wav");
        soundLoaded = true;
    }
    if (FileExists("assets/audio/bg.mp3")) {
        bgMusic = LoadMusicStream("assets/audio/bg.mp3");
        PlayMusicStream(bgMusic);
        musicLoaded = true;
    } else if (FileExists("assets/audio/bg.ogg")) {
        bgMusic = LoadMusicStream("assets/audio/bg.ogg");
        PlayMusicStream(bgMusic);
        musicLoaded = true;
    }

    // Player setup
    std::map<Direction, std::vector<int>> playerAtlas = {
        { DOWN,  {0,  1,  2,  3,  4,  5 } },
        { RIGHT, {24, 25, 26, 27, 28, 29} },
        { LEFT,  {24, 25, 26, 27, 28, 29} },
        { UP,    {0,  1,  2,  3,  4,  5 } }
    };

    player = Entity({128.0f, 560.0f}, {72.0f, 90.0f}, "",
                    ATLAS, {6.0f, 10.0f}, playerAtlas, PLAYER);
    player.setTexture(playerTex);
    player.setColliderDimensions({30.0f, 45.0f});
    player.setSpeed(220);
    player.setFrameSpeed(8);
    player.setJumpingPower(600.0f);
    player.setAcceleration({0.0f, 980.0f});
    player.setDirection(DOWN);

    BuildLevel();

    camera.target   = player.getPosition();
    camera.offset   = {Game::SCREEN_W / 2.0f, Game::SCREEN_H / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom     = 1.0f;

    hurtFlash     = 0;
    levelComplete = false;
    completeTimer = 0;
    inputLeft = inputRight = inputJump = false;
    mPrevTicks = (float)GetTime();
    mTimeAccum = 0.0f;
}

void GameScene::ProcessInput() {
    inputLeft  = IsKeyDown(KEY_A);
    inputRight = IsKeyDown(KEY_D);

    if (IsKeyPressed(KEY_W))
        inputJump = true;

    // level skip
    if (IsKeyPressed(KEY_ONE)) game->SwitchScene(SCENE_LEVEL1);
    if (IsKeyPressed(KEY_TWO)) game->SwitchScene(SCENE_LEVEL2);
    if (IsKeyPressed(KEY_THREE)) game->SwitchScene(SCENE_LEVEL3);
}

void GameScene::Update(float dt) {
    if (musicLoaded) UpdateMusicStream(bgMusic);

    // Level complete transition (outside fixed loop)
    if (levelComplete) {
        completeTimer += dt;
        if (completeTimer > 2.0f) {
            if (level < 3) {
                game->currentLevel = level + 1;
                game->SwitchScene(level == 1 ? SCENE_LEVEL2 : SCENE_LEVEL3);
            } else {
                game->SwitchScene(SCENE_WIN);
            }
        }
        return;
    }

    if (hurtFlash > 0) hurtFlash -= dt;

    // Fixed timestep
    float ticks = (float)GetTime();
    float delta = ticks - mPrevTicks;
    mPrevTicks  = ticks;
    if (delta > 0.05f) delta = 0.05f;
    delta += mTimeAccum;

    if (delta < FIXED_TS) { mTimeAccum = delta; return; }

    while (delta >= FIXED_TS) {

        // Physics & logic use FIXED_TS, not dt
        player.resetMovement();
        if (inputLeft)  { player.moveLeft();  player.setDirection(LEFT);  }
        if (inputRight) { player.moveRight(); player.setDirection(RIGHT); }

        if (inputJump && onGround) {
            player.jump();
            onGround  = false;
            inputJump = false;
            if (soundLoaded) PlaySound(jumpSound);
        }

        if (!onGround) player.setDirection(UP);
        else if (!inputLeft && !inputRight) player.setDirection(DOWN);

        player.update(FIXED_TS, nullptr, nullptr, nullptr, 0);

        // Platform collision
        onGround = false;
        for (auto& plat : platforms) {
            Rectangle pr = plat.rect;
            Rectangle cr = player.getColliderRect();
            if (!CheckCollisionRecs(cr, pr)) continue;

            float ovX = fabsf(pr.x+pr.width - cr.x) < fabsf(cr.x+cr.width - pr.x)
                        ? (pr.x+pr.width - cr.x) : -(cr.x+cr.width - pr.x);
            float ovY = fabsf(pr.y+pr.height - cr.y) < fabsf(cr.y+cr.height - pr.y)
                        ? (pr.y+pr.height - cr.y) : -(cr.y+cr.height - pr.y);

            Vector2 pos = player.getPosition();
            Vector2 vel = player.getVelocity();
            if (fabsf(ovX) < fabsf(ovY)) {
                pos.x += ovX; vel.x = 0;
            } else {
                pos.y += ovY;
                if (ovY < 0) { vel.y = 0; onGround = true; }
                else          { vel.y = 0; }
            }
            player.setPosition(pos);
            player.setVelocity(vel);
        }

        // Player bounds
        {
            Vector2 pos = player.getPosition();
            float hw = player.getColliderDimensions().x * 0.5f;
            if (pos.x - hw < 0)          pos.x = hw;
            if (pos.x + hw > levelWidth) pos.x = levelWidth - hw;
            player.setPosition(pos);
        }

        // Camera follow
        {
            camera.target = player.getPosition();
            float hw = Game::SCREEN_W / 2.0f, hh = Game::SCREEN_H / 2.0f;
            if (camera.target.x < hw)              camera.target.x = hw;
            if (camera.target.x > levelWidth - hw) camera.target.x = levelWidth - hw;
            if (camera.target.y < hh)              camera.target.y = hh;
            if (camera.target.y > Game::SCREEN_H - hh)
                camera.target.y = Game::SCREEN_H - hh;
        }

        // Fall off screen
        if (player.getPosition().y > Game::SCREEN_H + 100) {
            livesRef_--;
            if (soundLoaded) PlaySound(hitSound);
            if (livesRef_ <= 0) { game->SwitchScene(SCENE_LOSE); return; }
            ResetPlayer();
            hurtFlash = 1.0f;
        }

        // Enemy update
        for (auto& e : enemies) {
            if (!e.isActive()) continue;
            e.update(FIXED_TS, &player, nullptr, nullptr, 0);

            if (e.getAIType() != FLYER_AI) {
                for (auto& plat : platforms) {
                    Rectangle pr = plat.rect;
                    Rectangle cr = e.getColliderRect();
                    if (!CheckCollisionRecs(cr, pr)) continue;
                    float ovX = fabsf(pr.x+pr.width-cr.x) < fabsf(cr.x+cr.width-pr.x)
                                ? (pr.x+pr.width-cr.x) : -(cr.x+cr.width-pr.x);
                    float ovY = fabsf(pr.y+pr.height-cr.y) < fabsf(cr.y+cr.height-pr.y)
                                ? (pr.y+pr.height-cr.y) : -(cr.y+cr.height-pr.y);
                    Vector2 pos = e.getPosition(), vel = e.getVelocity();
                    if (fabsf(ovX) < fabsf(ovY)) { pos.x += ovX; vel.x = 0; }
                    else                         { pos.y += ovY; vel.y = 0; }
                    e.setPosition(pos); e.setVelocity(vel);
                }
            }

            Vector2 ep  = e.getPosition();
            float   ehw = e.getColliderDimensions().x * 0.5f;
            if (ep.x - ehw < 0)          ep.x = ehw;
            if (ep.x + ehw > levelWidth) ep.x = levelWidth - ehw;
            if (e.getAIType() == FLYER_AI) {
                if (ep.y < 60)                ep.y = 60;
                if (ep.y > Game::SCREEN_H-60) ep.y = Game::SCREEN_H - 60;
            }
            e.setPosition(ep);
        }

        // Player-enemy collision
        for (auto& e : enemies) {
            if (!e.isActive() || e.isDead()) continue;
            Rectangle pc = player.getColliderRect();
            Rectangle ec = e.getColliderRect();
            if (!CheckCollisionRecs(pc, ec)) continue;

            Vector2 pv    = player.getVelocity();
            bool    stomp = pv.y > 0 &&
                            pc.y + pc.height < ec.y + ec.height * 0.5f + 15;
            if (stomp) {
                e.kill();
                player.setVelocity({pv.x, -300.0f});
                if (soundLoaded) PlaySound(deathSound);
            } else {
                livesRef_--;
                if (soundLoaded) PlaySound(hitSound);
                hurtFlash = 1.5f;
                if (livesRef_ <= 0) { game->SwitchScene(SCENE_LOSE); return; }
                ResetPlayer();
            }
        }

        // Exit detection
        if (!levelComplete) {
            Platform& goal = platforms.back();
            Rectangle pc   = player.getColliderRect();
            if (onGround &&
                pc.x + pc.width  > goal.rect.x &&
                pc.x              < goal.rect.x + goal.rect.width &&
                pc.y + pc.height >= goal.rect.y &&
                pc.y + pc.height <= goal.rect.y + goal.rect.height + 5) {
                levelComplete = true;
                completeTimer = 0;
            }
        }

        delta -= FIXED_TS;
    }

    mTimeAccum = delta;
}

void GameScene::DrawHUD() {
    char buf[64];
    sprintf(buf, "Level %d", level);
    DrawText(buf, 10, 10, 24, WHITE);
    for (int i = 0; i < livesRef_; i++) DrawText("<3", 10+i*32, 40, 20, RED);
    for (int i = livesRef_; i < 3;  i++) DrawText("<3", 10+i*32, 40, 20, DARKGRAY);
    int alive = 0;
    for (auto& e : enemies) if (e.isActive()) alive++;
    sprintf(buf, "Enemies: %d", alive);
    DrawText(buf, Game::SCREEN_W - 130, 10, 20, ORANGE);
}

void GameScene::DrawPlatforms() {
    for (size_t i = 0; i < platforms.size(); i++) {
        Platform& p      = platforms[i];
        bool      isExit = (i == platforms.size() - 1);

        if (!isExit) {
            if (tilesetTex.id != 0) {
                float ts = p.rect.height;
                int   tw = (int)(p.rect.width / ts) + 1;
                for (int tx = 0; tx < tw; tx++) {
                    Rectangle src = {0, 0, 128, 128};
                    Rectangle dst = {p.rect.x + tx*ts, p.rect.y, ts, p.rect.height};
                    if (dst.x + dst.width > p.rect.x + p.rect.width)
                        dst.width = p.rect.x + p.rect.width - dst.x;
                    DrawTexturePro(tilesetTex, src, dst, {0,0}, 0, WHITE);
                }
            } else {
                DrawRectangleRec(p.rect, p.color);
                DrawRectangleLinesEx(p.rect, 1,
                    {0,(unsigned char)(p.color.g+40),0,255});
            }
        } else {
            // Exit platform
            float pulse = (sinf(GetTime()*4)+1)*0.5f;
            DrawRectangleRec(p.rect, {0,255,150,(unsigned char)(100+pulse*155)});
            DrawText("EXIT",
                (int)(p.rect.x + p.rect.width/2 - 20),
                (int)(p.rect.y - 20), 16, YELLOW);
        }
    }
}

void GameScene::Render() {
    // Background
    DrawRectangleGradientV(0, 0, Game::SCREEN_W, Game::SCREEN_H,
                           {20,15,40,255}, {8,6,20,255});
    BeginMode2D(camera);
        DrawPlatforms();
        for (auto& e : enemies) e.render();
        // Hurt flash
        if (hurtFlash > 0 && sinf(hurtFlash * 20) > 0) {
            Rectangle cr = player.getColliderRect();
            DrawRectangle((int)(cr.x-2),(int)(cr.y-2),
                          (int)(cr.width+4),(int)(cr.height+4),{255,0,0,120});
        }
        player.render();
    EndMode2D();

    DrawHUD();

    // Level complete overlay
    if (levelComplete) {
        DrawRectangle(0, 0, Game::SCREEN_W, Game::SCREEN_H, {0,0,0,100});
        const char* msg = (level < 3) ? "Level Complete!" : "You Cleared All Levels!";
        int mw = MeasureText(msg, 40);
        DrawText(msg, Game::SCREEN_W/2-mw/2, Game::SCREEN_H/2-20, 40, YELLOW);
    }
}

void GameScene::Shutdown() {
    if (playerTex.id)   UnloadTexture(playerTex);
    if (skeletonTex.id) UnloadTexture(skeletonTex);
    if (slimeTex.id)    UnloadTexture(slimeTex);
    if (tilesetTex.id)  UnloadTexture(tilesetTex);
    if (musicLoaded) {
        StopMusicStream(bgMusic);
        UnloadMusicStream(bgMusic);
        musicLoaded = false;
    }
    if (soundLoaded) {
        UnloadSound(jumpSound);
        UnloadSound(hitSound);
        UnloadSound(deathSound);
        soundLoaded = false;
    }
}

// YouWinScene
YouWinScene::YouWinScene(Game* g) : Scene(g), timer(0) {}
void YouWinScene::Initialize()      { timer = 0; }
void YouWinScene::Shutdown()        {}
void YouWinScene::ProcessInput() {
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
        game->SwitchScene(SCENE_MENU);
}
void YouWinScene::Update(float dt)  { timer += dt; }
void YouWinScene::Render() {
    DrawRectangleGradientV(0, 0, Game::SCREEN_W, Game::SCREEN_H,
                           {40,30,5,255}, {60,45,8,255});
    // Particles
    for (int i = 0; i < 80; i++) {
        float a = GetTime()*2 + i*0.3f;
        float r = 150 + sinf(GetTime()+i)*100;
        int   sx = (int)(Game::SCREEN_W/2 + cosf(a)*r);
        int   sy = (int)(Game::SCREEN_H/2 + sinf(a)*r*0.6f);
        float b  = (sinf(GetTime()*3+i)+1)*0.5f;
        DrawCircle(sx, sy, 2,
            {255,(unsigned char)(200+b*55),0,(unsigned char)(b*255)});
    }
    float pulse = 1 + 0.06f*sinf(timer*3);
    int   fs    = (int)(64*pulse);
    const char* win = "YOU WIN!";
    int ww = MeasureText(win, fs);
    DrawText(win, Game::SCREEN_W/2-ww/2+3, 193, fs, {120,80,0,200});
    DrawText(win, Game::SCREEN_W/2-ww/2,   190, fs, {255,220,50,255});
    const char* sub = "You conquered all 3 levels!";
    int sw = MeasureText(sub, 24);
    DrawText(sub, Game::SCREEN_W/2-sw/2, 280, 24, {255,200,100,255});
    float al = (sinf(timer*2)+1)*0.5f;
    const char* bk = "Press ENTER to return to Menu";
    int bw = MeasureText(bk, 22);
    DrawText(bk, Game::SCREEN_W/2-bw/2, 370, 22,
             {255,255,255,(unsigned char)(150+al*105)});
}

// YouLoseScene
YouLoseScene::YouLoseScene(Game* g) : Scene(g), timer(0) {}
void YouLoseScene::Initialize()     { timer = 0; }
void YouLoseScene::Shutdown()       {}
void YouLoseScene::ProcessInput() {
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
        game->lives        = 3;
        game->currentLevel = 1;
        game->SwitchScene(SCENE_MENU);
    }
}
void YouLoseScene::Update(float dt) { timer += dt; }
void YouLoseScene::Render() {
    DrawRectangleGradientV(0, 0, Game::SCREEN_W, Game::SCREEN_H,
                           {50,5,5,255}, {65,8,8,255});
    // Falling particles
    for (int i = 0; i < 40; i++) {
        float py = fmodf(GetTime()*(20+i*3)+i*37, (float)Game::SCREEN_H);
        float px = (float)((i*173) % Game::SCREEN_W);
        DrawRectangle((int)px, (int)py, 2, 8, {200,0,0,180});
    }
    float pulse = 1 + 0.07f*sinf(timer*2.5f);
    int   fs    = (int)(64*pulse);
    const char* lose = "YOU LOSE";
    int lw = MeasureText(lose, fs);
    DrawText(lose, Game::SCREEN_W/2-lw/2+3, 193, fs, {80,0,0,220});
    DrawText(lose, Game::SCREEN_W/2-lw/2,   190, fs, {255,60,60,255});
    const char* sub = "You ran out of lives...";
    int sw = MeasureText(sub, 24);
    DrawText(sub, Game::SCREEN_W/2-sw/2, 280, 24, {200,100,100,255});
    float al = (sinf(timer*2)+1)*0.5f;
    const char* bk = "Press ENTER to return to Menu";
    int bw = MeasureText(bk, 22);
    DrawText(bk, Game::SCREEN_W/2-bw/2, 370, 22,
             {255,200,200,(unsigned char)(150+al*105)});
}
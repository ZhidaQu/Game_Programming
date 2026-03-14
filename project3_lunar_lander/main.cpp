/**
 * Author: Zhida Qu
 * Assignment: Lunar Lander
 * Date due: 2025/03/14
 * I pledge that I have completed this assignment without
 * collaborating with anyone else, in conformance with the
 * NYU School of Engineering Policies and Procedures on
 * Academic Misconduct.
 **/

#include "CS3113/cs3113.h"
#include "CS3113/Entity.h"
constexpr int SCREEN_WIDTH = 960,
              SCREEN_HEIGHT = 600,
              FPS = 60;

constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;
constexpr char WINDOW_TITLE[] = "Lunar Lander";
constexpr float GRAVITY = 80.0f;
constexpr float THRUST = 240.0f;
constexpr float DRAG = 0.985f;
constexpr float MAX_FUEL = 300.0f;
constexpr float FUEL_RATE = 12.0f;

constexpr int NUMBER_OF_PLATFORMS = 4;

enum GameStatus { PLAYING, MISSION_ACCOMPLISHED, MISSION_FAILED };

AppStatus gAppStatus = RUNNING;
GameStatus gGameStatus = PLAYING;

float gPreviousTicks = 0.0f;
float gTimeAccumulator = 0.0f;
float gFuel = MAX_FUEL;

Entity *gLander = nullptr;
Entity *gPlatforms = nullptr;

const float PLAT_SPEED[NUMBER_OF_PLATFORMS] = { 0.0f, 0.0f, 90.0f, 60.0f };
const float PLAT_MIN_X[NUMBER_OF_PLATFORMS] = { 0.0f, 0.0f, 30.0f, 460.0f };
const float PLAT_MAX_X[NUMBER_OF_PLATFORMS] = { 0.0f, 0.0f, 500.0f, 900.0f };
const bool PLAT_WIN[NUMBER_OF_PLATFORMS] = { false, true, false, true };

int gPlatformDir[NUMBER_OF_PLATFORMS] = { 1, 1, 1, 1 };


void initialise();
void resetGame();
void processInput();
void update();
void render();
void shutdown();
void updatePhysics(float deltaTime);
void drawLander();
void drawPlatforms();
void drawHUD();
void drawEndScreen();

bool checkCollisionAABB(Vector2 posA, Vector2 scaleA, Vector2 posB, Vector2 scaleB)
{
    float xDist = fabs(posA.x - posB.x) - (scaleA.x + scaleB.x) / 2.0f;
    float yDist = fabs(posA.y - posB.y) - (scaleA.y + scaleB.y) / 2.0f;
    return xDist < 0.0f && yDist < 0.0f;
}

void resetGame()
{
    delete gLander;
    delete[] gPlatforms;

    gLander = new Entity();
    gLander->setPosition({ SCREEN_WIDTH / 2.0f, 60.0f });
    gLander->setScale({ 48.0f, 48.0f });
    gLander->setColliderDimensions({ 48.0f, 48.0f });
    gLander->setVelocity({ 0.0f, 0.0f });
    gLander->setAcceleration({ 0.0f, 0.0f });
    gPlatforms = new Entity[NUMBER_OF_PLATFORMS];

    gPlatforms[0].setPosition({ 150.0f, 490.0f });
    gPlatforms[0].setScale({ 110.0f, 18.0f });
    gPlatforms[0].setColliderDimensions({ 110.0f, 18.0f });

    gPlatforms[1].setPosition({ 750.0f, 390.0f });
    gPlatforms[1].setScale({ 130.0f, 18.0f });
    gPlatforms[1].setColliderDimensions({ 130.0f, 18.0f });

    gPlatforms[2].setPosition({ 200.0f, 310.0f });
    gPlatforms[2].setScale({ 100.0f, 18.0f });
    gPlatforms[2].setColliderDimensions({ 100.0f, 18.0f });

    gPlatforms[3].setPosition({ 520.0f, 530.0f });
    gPlatforms[3].setScale({ 110.0f, 18.0f });
    gPlatforms[3].setColliderDimensions({ 110.0f, 18.0f });

    for (int i = 0; i < NUMBER_OF_PLATFORMS; i++) gPlatformDir[i] = 1;

    gFuel = MAX_FUEL;
    gGameStatus = PLAYING;
    gPreviousTicks = (float) GetTime();
    gTimeAccumulator = 0.0f;
}

void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(FPS);
    resetGame();
}

void processInput()
{
    if (IsKeyPressed(KEY_Q) || WindowShouldClose()) gAppStatus = TERMINATED;
    if (IsKeyPressed(KEY_R) && gGameStatus != PLAYING) resetGame();
}

void updatePhysics(float deltaTime)
{
    bool thrustLeft = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
    bool thrustRight = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);
    bool thrustUp = IsKeyDown(KEY_UP) || IsKeyDown(KEY_W);

    Vector2 vel = gLander->getVelocity();
    Vector2 pos = gLander->getPosition();

    Vector2 accel = { 0.0f, GRAVITY };

    if (gFuel > 0.0f)
    {
        if (thrustLeft)  { accel.x -= THRUST; gFuel -= FUEL_RATE * deltaTime; }
        if (thrustRight) { accel.x += THRUST; gFuel -= FUEL_RATE * deltaTime; }
        if (thrustUp)    { accel.y -= THRUST; gFuel -= FUEL_RATE * deltaTime; }
    }

    if (gFuel < 0.0f) gFuel = 0.0f;

    gLander->setAcceleration(accel);

    vel.x += accel.x * deltaTime;
    vel.y += accel.y * deltaTime;
    vel.x *= DRAG;
    pos.x += vel.x * deltaTime;
    pos.y += vel.y * deltaTime;

    gLander->setVelocity(vel);
    gLander->setPosition(pos);
    Vector2 scale = gLander->getScale();
    if (pos.x - scale.x / 2.0f <= 0.0f ||
        pos.x + scale.x / 2.0f >= SCREEN_WIDTH ||
        pos.y - scale.y / 2.0f <= 0.0f ||
        pos.y + scale.y / 2.0f >= SCREEN_HEIGHT)
    {
        gGameStatus = MISSION_FAILED;
        return;
    }

    for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
    {
        if (checkCollisionAABB(pos, scale, gPlatforms[i].getPosition(), gPlatforms[i].getScale()))
        {
            gGameStatus = PLAT_WIN[i] ? MISSION_ACCOMPLISHED : MISSION_FAILED;
            return;
        }
    }

    for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
    {
        if (PLAT_SPEED[i] == 0.0f) continue;
        Vector2 platPos = gPlatforms[i].getPosition();
        float halfW = gPlatforms[i].getScale().x / 2.0f;
        platPos.x += PLAT_SPEED[i] * gPlatformDir[i] * deltaTime;

        if (platPos.x - halfW <= PLAT_MIN_X[i] || platPos.x + halfW >= PLAT_MAX_X[i])
            gPlatformDir[i] *= -1;
        gPlatforms[i].setPosition(platPos);
    }
}

void update()
{
    float ticks = (float) GetTime();
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks = ticks;

    if (gGameStatus != PLAYING) return;

    deltaTime += gTimeAccumulator;
    if (deltaTime < FIXED_TIMESTEP) { gTimeAccumulator = deltaTime; return; }

    while (deltaTime >= FIXED_TIMESTEP)
    {
        updatePhysics(FIXED_TIMESTEP);
        if (gGameStatus != PLAYING) break;
        deltaTime -= FIXED_TIMESTEP;
    }

    gTimeAccumulator = deltaTime;
}

void drawLander()
{
    Vector2 pos = gLander->getPosition();
    Vector2 sc = gLander->getScale();
    float hw = sc.x / 2.0f;
    float hh = sc.y / 2.0f;

    DrawTriangle({ pos.x, pos.y - hh }, { pos.x - hw, pos.y }, { pos.x + hw, pos.y }, LIGHTGRAY);
    DrawRectangle((int)(pos.x - hw), (int) pos.y, (int)(hw * 2.0f), (int)(hh * 0.8f), LIGHTGRAY);
    DrawLine((int)(pos.x - hw), (int)(pos.y + hh * 0.6f), (int)(pos.x - hw - 8), (int)(pos.y + hh), GRAY);
    DrawLine((int)(pos.x + hw), (int)(pos.y + hh * 0.6f), (int)(pos.x + hw + 8), (int)(pos.y + hh), GRAY);

    bool up    = (IsKeyDown(KEY_UP)    || IsKeyDown(KEY_W)) && gFuel > 0.0f;
    bool left  = (IsKeyDown(KEY_LEFT)  || IsKeyDown(KEY_A)) && gFuel > 0.0f;
    bool right = (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && gFuel > 0.0f;

    if (up)
    {
        DrawTriangle({ pos.x - 7, pos.y + hh * 0.7f }, { pos.x + 7, pos.y + hh * 0.7f }, { pos.x, pos.y + hh + 20 }, ORANGE);
        DrawTriangle({ pos.x - 4, pos.y + hh * 0.7f }, { pos.x + 4, pos.y + hh * 0.7f }, { pos.x, pos.y + hh + 10 }, YELLOW);
    }
    if (left)
        DrawTriangle({ pos.x + hw + 2, pos.y - 4 }, { pos.x + hw + 2, pos.y + 4 }, { pos.x + hw + 14, pos.y }, ORANGE);
    if (right)
        DrawTriangle({ pos.x - hw - 2, pos.y - 4 }, { pos.x - hw - 2, pos.y + 4 }, { pos.x - hw - 14, pos.y }, ORANGE);
}

void drawPlatforms()
{
    for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
    {
        Vector2 pos = gPlatforms[i].getPosition();
        Vector2 scale = gPlatforms[i].getScale();
        bool moves = PLAT_SPEED[i] > 0.0f;

        Color col = PLAT_WIN[i] ? GREEN : RED;
        if (moves) col = PLAT_WIN[i] ? (Color){ 80, 255, 120, 255 } : (Color){ 255, 80, 60, 255 };

        DrawRectangle(
            (int)(pos.x - scale.x / 2.0f),
            (int)(pos.y - scale.y / 2.0f),
            (int) scale.x,
            (int) scale.y,
            col
        );
        DrawRectangle((int)(pos.x - scale.x / 2.0f), (int)(pos.y - scale.y / 2.0f), (int) scale.x, 3, WHITE);
    }
}

void drawHUD()
{
    float fuelPct = gFuel / MAX_FUEL;
    DrawRectangle(20, 20, 202, 16, DARKGRAY);
    DrawRectangle(21, 21, (int)(200.0f * fuelPct), 14, fuelPct > 0.3f ? GREEN : RED);
    DrawRectangleLines(20, 20, 202, 16, RAYWHITE);
    DrawText("FUEL", 228, 20, 14, LIGHTGRAY);
}

void drawEndScreen()
{
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, { 0, 0, 0, 160 });

    if (gGameStatus == MISSION_ACCOMPLISHED)
    {
        const char *msg = "MISSION ACCOMPLISHED!";
        DrawText(msg, SCREEN_WIDTH / 2 - MeasureText(msg, 44) / 2, SCREEN_HEIGHT / 2 - 24, 44, GREEN);
    }
    else
    {
        const char *msg = "MISSION FAILED";
        DrawText(msg, SCREEN_WIDTH / 2 - MeasureText(msg, 48) / 2, SCREEN_HEIGHT / 2 - 24, 48, RED);
    }
}

void render()
{
    BeginDrawing();
    ClearBackground(BLACK);
    drawPlatforms();
    if (gGameStatus == PLAYING) drawLander();
    drawHUD();
    if (gGameStatus != PLAYING) drawEndScreen();
    EndDrawing();
}

void shutdown()
{
    delete gLander;
    delete[] gPlatforms;
    gLander = nullptr;
    gPlatforms = nullptr;
}

int main(void)
{
    initialise();
    while (gAppStatus == RUNNING)
    {
        processInput();
        update();
        render();
    }
    shutdown();
    CloseWindow();
    return 0;
}

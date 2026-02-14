/**
* Author: Zhida Qu
* Assignment: Simple 2D Scene
* Date due: 2/14/2026
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "raylib.h"
#include <cmath>

enum AppStatus { TERMINATED, RUNNING };

// Global constants
constexpr int SCREEN_WIDTH  = 900;
constexpr int SCREEN_HEIGHT = 600;
constexpr int FPS = 60;

// Texture file paths (match image names)
constexpr char TEX_SUN_FP[] = "asset/sun.png";
constexpr char TEX_EARTH_FP[] = "asset/earth.png";
constexpr char TEX_ROCKET_FP[] = "asset/rocket.png";

AppStatus gAppStatus = RUNNING;

// Textures
Texture2D gSunTex;
Texture2D gEarthTex;
Texture2D gRocketTex;

// Some Global variables
float gPrevTime = 0.0f;
float gTime = 0.0f;

Vector2 gSunPos = { 
    SCREEN_WIDTH * 0.5f, 
    SCREEN_HEIGHT * 0.5f };

Vector2 gEarthPos = { 0, 0 };

Vector2 gRocketPos = { 
    SCREEN_WIDTH * 0.5f, 
    SCREEN_HEIGHT * 0.5f };

float gSunRot = 0.0f;
float gEarthRot = 0.0f;
float gRocketRot = 0.0f;
float gRocketScalePulse = 1.0f;

// Function declarations
void initialise();
void processInput();
void update();
void render();
void shutdown();
static Color AnimatedBackground(float t);
static void DrawTexturedObject(Texture2D tex, Vector2 pos, Vector2 size, float rotation, Color tint);

void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "A Simple 2D Scene");
    SetTargetFPS(FPS);
    gSunTex = LoadTexture(TEX_SUN_FP);
    gEarthTex = LoadTexture(TEX_EARTH_FP);
    gRocketTex = LoadTexture(TEX_ROCKET_FP);
    gPrevTime = (float)GetTime();
}

void processInput()
{
    if (WindowShouldClose()) gAppStatus = TERMINATED;
}

// Generates a animated background color based on time
static Color AnimatedBackground(float t)
{
    auto toByte = [](float x) -> unsigned char {
        int v = (int)(x * 255.0f);
        if (v < 0) v = 0;
        if (v > 255) v = 255;
        return (unsigned char)v;
    };
    float r = 0.35f + 0.35f * sinf(t * 0.7f);
    float g = 0.35f + 0.35f * sinf(t * 0.9f + 1.3f);
    float b = 0.35f + 0.35f * sinf(t * 1.1f + 2.1f);
    return (Color){toByte(r), toByte(g), toByte(b), 255};
}

void update()
{
    float now = (float)GetTime();
    float dt = now - gPrevTime;
    gPrevTime = now;
    gTime += dt;
    Vector2 center = {SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f};

    // Sun movement 
    float ax = 220.0f;
    float ay = 140.0f;
    float fx = 1.2f;
    float fy = 1.8f;
    float phase = 0.8f;
    gSunPos.x = center.x + ax * sinf(gTime * fx + phase);
    gSunPos.y = center.y + ay * sinf(gTime * fy);

    // Earth orbits sun 
    float orbitR = 110.0f + 15.0f * sinf(gTime * 1.3f);
    float orbitAng = gTime * 2.2f;
    gEarthPos.x = gSunPos.x + orbitR * cosf(orbitAng);
    gEarthPos.y = gSunPos.y + orbitR * sinf(orbitAng);

    // Rocket movement
    float eightA = 260.0f;
    float eightB = 120.0f;
    gRocketPos.x = center.x + eightA * sinf(gTime * 0.95f);
    gRocketPos.y = center.y + eightB * sinf(gTime * 1.90f) * cosf(gTime * 0.95f);
    gRocketRot += 90.0f * dt;
    gRocketScalePulse = 1.0f + 0.20f * sinf(gTime * 3.0f);
    gEarthRot = 25.0f * sinf(gTime * 2.0f);
}

static void DrawTexturedObject(Texture2D tex, Vector2 pos, Vector2 size, float rotation, Color tint)
{
    Rectangle src = {
        0.0f, 0.0f, 
        static_cast<float>(tex.width), 
        static_cast<float>(tex.height)
        };
    Rectangle dst = {
        pos.x, 
        pos.y, 
        size.x, 
        size.y
    };
    Vector2 origin = {
        size.x * 0.5f, 
        size.y * 0.5f};
    DrawTexturePro(tex, src, dst, origin, rotation, tint);
}

void render()
{
    BeginDrawing();
    ClearBackground(AnimatedBackground(gTime));
    DrawTexturedObject(gSunTex, gSunPos, {140.0f, 140.0f}, gSunRot, WHITE);
    DrawTexturedObject(gEarthTex, gEarthPos, {80.0f, 80.0f}, gEarthRot, WHITE);
    Vector2 rocketSize = {110.0f * gRocketScalePulse, 110.0f * gRocketScalePulse};
    DrawTexturedObject(gRocketTex, gRocketPos, rocketSize, gRocketRot, WHITE);
    EndDrawing();
}

void shutdown()
{
    UnloadTexture(gSunTex);
    UnloadTexture(gEarthTex);
    UnloadTexture(gRocketTex);
    CloseWindow();
}

int main()
{
    initialise();
    while (gAppStatus == RUNNING)
    {
        processInput();
        update();
        render();
    }
    shutdown();
    return 0;
}
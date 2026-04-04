#pragma once
#include "raylib.h"
#include <cmath>

enum TextureType { SINGLE, ATLAS };

static inline void Normalise(Vector2* v) {
    float len = sqrtf(v->x * v->x + v->y * v->y);
    if (len > 0.0f) { v->x /= len; v->y /= len; }
}

static inline float GetLength(Vector2 v) {
    return sqrtf(v.x * v.x + v.y * v.y);
}


class Map {
public:
    static const int MAX_COLS = 50;
    static const int MAX_ROWS = 38;

    Map();
    ~Map() {}
    void Load(const int* mapData, int cols, int rows,
              float tileSize, const char* texturePath = "");

    void Render() const;

    bool isSolidTileAt(Vector2 probe, float* xOverlap, float* yOverlap) const;

    float getTileSize() const { return mTileSize; }
    int   getCols()     const { return mCols; }
    int   getRows()     const { return mRows; }

private:
    int   mData[MAX_ROWS][MAX_COLS];
    int   mCols;
    int   mRows;
    float mTileSize;

    Texture2D mTexture;
    bool      mHasTexture;
};

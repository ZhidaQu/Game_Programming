#include "Map.h"
#include <cstring>
#include <cstdio>

Map::Map()
    : mCols(0), mRows(0), mTileSize(32.0f),
      mHasTexture(false)
{
    memset(mData, 0, sizeof(mData));
    mTexture = {0};
}

void Map::Load(const int* mapData, int cols, int rows,
               float tileSize, const char* texturePath)
{
    mCols     = (cols < MAX_COLS) ? cols : MAX_COLS;
    mRows     = (rows < MAX_ROWS) ? rows : MAX_ROWS;
    mTileSize = tileSize;

    for (int r = 0; r < mRows; r++)
        for (int c = 0; c < mCols; c++)
            mData[r][c] = mapData[r * cols + c];

    mHasTexture = false;
    if (texturePath && texturePath[0] != '\0' && FileExists(texturePath)) {
        mTexture    = LoadTexture(texturePath);
        mHasTexture = true;
    }
}

void Map::Render() const {
    for (int r = 0; r < mRows; r++) {
        for (int c = 0; c < mCols; c++) {
            if (mData[r][c] == 0) continue;

            float x = c * mTileSize;
            float y = r * mTileSize;

            if (mHasTexture && mTexture.id != 0) {
                Rectangle src = {0, 0,
                    (float)mTexture.width,
                    (float)mTexture.height};
                Rectangle dst = {x, y, mTileSize, mTileSize};
                DrawTexturePro(mTexture, src, dst, {0,0}, 0.0f, WHITE);
            } else {
                DrawRectangle((int)x, (int)y,
                              (int)mTileSize, (int)mTileSize, DARKGREEN);
                DrawRectangleLinesEx({x, y, mTileSize, mTileSize}, 1.0f, {0, 150, 60, 200});
            }
        }
    }
}

bool Map::isSolidTileAt(Vector2 probe, float* xOverlap, float* yOverlap) const {
    // Convert world position to tile indices
    int col = (int)(probe.x / mTileSize);
    int row = (int)(probe.y / mTileSize);

    if (col < 0 || col >= mCols || row < 0 || row >= mRows) {
        *xOverlap = 0.0f;
        *yOverlap = 0.0f;
        return false;
    }

    if (mData[row][col] == 0) {
        *xOverlap = 0.0f;
        *yOverlap = 0.0f;
        return false;
    }

    // Calculate how far inside the tile the probe point is
    float tileLeft   = col * mTileSize;
    float tileTop    = row * mTileSize;
    float tileRight  = tileLeft + mTileSize;
    float tileBottom = tileTop  + mTileSize;

    *xOverlap = (probe.x < tileLeft + mTileSize * 0.5f)
                ? (tileRight  - probe.x)
                : (probe.x    - tileLeft);

    *yOverlap = (probe.y < tileTop + mTileSize * 0.5f)
                ? (tileBottom - probe.y)
                : (probe.y    - tileTop);

    return true;
}

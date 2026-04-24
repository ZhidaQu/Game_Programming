#include "Map.h"
#include <cmath>

Map::Map(int w, int h, const int* level_data, Texture2D tileset, int tileset_cols)
    : width(w), height(h), m_tileset(tileset), m_tileset_cols(tileset_cols)
{
    m_data.assign(level_data, level_data + w * h);
}

int Map::tile_at(int col, int row) const {
    if (col < 0 || col >= width || row < 0 || row >= height) return 1; 
    return m_data[row * width + col];
}

void Map::render(Camera2D camera) const {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int id = tile_at(col, row);
            if (id == 0) continue;

            if (id == 1) {
                DrawRectangle(col * TILE_SIZE, row * TILE_SIZE,
                              TILE_SIZE, TILE_SIZE, {10, 10, 40, 255});
            } else if (id == 2) {
                if (m_obstacle_tex.id != 0) {
                    Rectangle src = { 0, 0, (float)m_obstacle_tex.width,
                                            (float)m_obstacle_tex.height };
                    Rectangle dst = { (float)(col * TILE_SIZE),
                                      (float)(row * TILE_SIZE),
                                      (float)TILE_SIZE, (float)TILE_SIZE };
                    DrawTexturePro(m_obstacle_tex, src, dst, {0,0}, 0.0f, WHITE);
                } else {
                    DrawRectangle(col * TILE_SIZE, row * TILE_SIZE,
                                  TILE_SIZE, TILE_SIZE, {80, 80, 90, 255});
                }
            } else {
                DrawRectangle(col * TILE_SIZE, row * TILE_SIZE,
                              TILE_SIZE, TILE_SIZE, {30, 30, 60, 255});
            }
        }
    }
}

bool Map::check_solid_collision(Rectangle rect) const {
    // Check all tiles the rectangle overlaps
    int left   = (int)(rect.x              / TILE_SIZE);
    int right  = (int)((rect.x + rect.width - 1)  / TILE_SIZE);
    int top    = (int)(rect.y              / TILE_SIZE);
    int bottom = (int)((rect.y + rect.height - 1) / TILE_SIZE);

    for (int row = top; row <= bottom; row++) {
        for (int col = left; col <= right; col++) {
            if (is_solid(tile_at(col, row))) return true;
        }
    }
    return false;
}

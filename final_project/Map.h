#pragma once
#include "raylib.h"
#include <vector>

constexpr int TILE_SIZE = 32;

class Map {
public:
    int width  = 0;   
    int height = 0;   
    Texture2D m_obstacle_tex = { 0 };

    Map(int w, int h, const int* level_data, Texture2D tileset, int tileset_cols);
    ~Map() = default;

    void render(Camera2D camera) const;
    void set_obstacle_tex(Texture2D tex) { m_obstacle_tex = tex; }

    bool check_solid_collision(Rectangle rect) const;

    int   get_pixel_width()  const { return width  * TILE_SIZE; }
    int   get_pixel_height() const { return height * TILE_SIZE; }

private:
    std::vector<int> m_data;
    Texture2D        m_tileset = { 0 };
    int              m_tileset_cols = 1;

    int  tile_at(int col, int row) const;
    bool is_solid(int tile_id) const { return tile_id == 2; }
};

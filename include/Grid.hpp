#include <vector>
#include <cstdint>
#include <limits>
#include <cmath>
#include <ncurses.h>
#include <algorithm>
#include <iostream>

class Grid
{
public:
    Grid(/* args */) = default;
    ~Grid() = default;
    uint8_t maxGridSize = std::numeric_limits<uint8_t>::max();
    std::vector<uint8_t> Tiles = std::vector<uint8_t>(maxGridSize+1);
    std::vector<uint8_t> bufferTiles = std::vector<uint8_t>(maxGridSize+1);
    const int width = sqrt(Tiles.size());
    const uint8_t bitAmount = std::log2(width);
    void DrawGrid() {
        for (size_t i = 0; i < Tiles.size()-1; i++)
        {
            int y = floor(i/width);
            int x = i-(y*width);

            constexpr uint8_t charspaces = 4;

            if (Tiles[i] == 0)
            {
                mvaddstr(y, x*charspaces, " ");
            }else{
                mvaddstr(y, x*charspaces, "▀");
            }
        }
    }

    uint8_t GetIndexFromCoords(uint8_t x, uint8_t y) {
        return (y << 4) | x;
    }

    uint8_t CountNeighbors(uint8_t i){
        uint8_t count = 0;

        uint8_t x = i & 0x0F;
        uint8_t y = i >> 4;

        for (int dx = -1; dx <= 1; dx++)
        {
            for (int dy = -1; dy <= 1; dy++)
            {
                if (dx == 0 && dy == 0)
                    continue;
                if (Tiles[GetIndexFromCoords(x+dx,y+dy)] == 1)
                    count++;
            }
        }
        
        return count;
    }
    void UpdateTiles() {
        for (size_t i = 0; i < Tiles.size(); i++)
        {
            uint8_t nCount = CountNeighbors(i);
            if (Tiles[i] == 1) {
                if (nCount < 2 || nCount > 3)
                {
                    bufferTiles[i] = 0;
                    continue;
                }
            }else if(nCount != 3){
                continue;
            }
            bufferTiles[i] = 1;
        }

        std::swap(Tiles, bufferTiles);
        std::fill(bufferTiles.begin(), bufferTiles.end(), 0);
    }

};
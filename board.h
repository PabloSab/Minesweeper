//
// Created by Pablo Sabogal on 4/22/2024.
//
#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H
#include "tile.h"
#include "TextureManager.h"
#include <vector>
using namespace std;

class Board{
private:
    int mineCount = 0;
    int flagCount = 0;
    vector<Tile> board;
    int width;
    int length;
    int mine;
    bool debug = false;
    bool end = false;
    bool victory = false;
public:
    Board(int width1, int length1, int mine1);
    void Initialize();
    void Debug();
    void GameOver();
    void RevealTile(Tile* tile);
    void AddFlag(Tile* tile);
    Tile& GetTile(int tile);
    int TileCount();
    int GetMineCount();
    void SetNumber();
    void SetNeighbor();
    bool GetVictory();
    void SetMineCount(int mineCount1);
    void Clear();
    bool GetEnd();
    void SetTile();
    void UnsetTile();
};


#endif //MINESWEEPER_BOARD_H

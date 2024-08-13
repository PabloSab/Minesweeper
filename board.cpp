//
// Created by Pablo Sabogal on 4/22/2024.
//
#include "board.h"
#include <cstdlib>
#include <ctime>
using namespace std;
Board::Board(int width1, int length1,int mine1){
    width = width1;
    length = length1;
    mine = mine1;
}
void Board::Initialize(){
    srand(time(0));
    vector<int> MinePositions;
    while(MinePositions.size()<mine){
        int temp = (rand() % 401);
        bool check = false;
        for(int i =0;i<MinePositions.size();i++){
            if(temp == MinePositions[i]){
                check = true;
                break;
            }
        }
        if(check==false){
            MinePositions.push_back(temp);
        }
    }
    end = false;
    victory = false;
    mineCount = 0;
    flagCount = 0;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            sf::Vector2f position = sf::Vector2f((float)(j) * 32, (float)(i) * 32);
            Tile::SecretState sec_state = Tile::SecretState::empty;
            Tile temp = Tile(position, "tile_hidden", sec_state);
            board.push_back(temp);
        }
    }
    for(int i = 0; i<MinePositions.size();i++){
        board[MinePositions[i]].SetSecretState(Tile::SecretState::mine);
        mineCount++;
    }
    SetNeighbor();
    SetNumber();
}

void Board::Clear(){
    for(int i =0; i<board.size();i++){
        board[i].SetSecretState(Tile::SecretState::empty);
        board[i].SetState(Tile::State::hidden);
        board[i].SetSprite("tile_hidden");
        board[i].SetClickable(true);
        board[i].SetRightClickable(true);
    }
}

void Board::SetTile(){
    for(int i =0; i<board.size();i++){
        board[i].SetSprite("tile_revealed");
        board[i].SetClickable(false);
        board[i].SetRightClickable(false);
    }
}
void Board::SetNeighbor(){
    for (int i = 0; i < board.size(); ++i) {
        int row = i/width;
        int col = i%width;
        int rowStart = max(row - 1, 0);
        int rowEnd = min(row + 1, length - 1);
        int colStart = max(col - 1, 0);
        int colEnd = min(col + 1, width - 1);
        for (int r = rowStart; r <= rowEnd; ++r) {
            for (int c = colStart; c <= colEnd; ++c) {
                if (r == row && c == col) continue;
                int neighborIndex = r * width + c;
                board[i].AddInRadius(&board[neighborIndex]);
            }
        }
    }
}

void Board::SetNumber(){
    for (int i = 0; i < board.size(); i++) {
        if (!(board[i].GetSecretState() == Tile::SecretState::mine)) {
            int count = 0;
            for (int j = 0; j < board[i].GetCount(); j++) {
                Tile *tile = board[i].GetRadius(j);
                if (tile->GetSecretState() == Tile::SecretState::mine) {
                    count++;
                }
            }
            if (count == 1) {
                board[i].SetSecretState(Tile::SecretState::one);
            } else if (count == 2) {
                board[i].SetSecretState(Tile::SecretState::two);
            } else if (count == 3) {
                board[i].SetSecretState(Tile::SecretState::three);
            } else if (count == 4){
                board[i].SetSecretState(Tile::SecretState::four);
            } else if (count == 5){
                board[i].SetSecretState(Tile::SecretState::five);
            }
            else if (count == 6){
                board[i].SetSecretState(Tile::SecretState::six);
            }
            else if (count == 7){
                board[i].SetSecretState(Tile::SecretState::seven);
            }
            else if (count == 8){
                board[i].SetSecretState(Tile::SecretState::eight);
            }
            else if (board[i].GetSecretState() != Tile::SecretState::mine){
                board[i].SetSecretState(Tile::SecretState::empty);
            }
        }
    }
}
void Board::Debug(){
    debug = !debug;
    if (!end && !victory) {
        for (int i = 0; i < TileCount(); i++) {
            if (board[i].GetSecretState() == Tile::SecretState::mine) {
                board[i].SetSprite("mine");
            }
        }
    }
    if (!debug) {
        for (int i = 0; i < TileCount(); i++) {
            if (board[i].GetSecretState() == Tile::SecretState::mine) {
                board[i].SetSprite("tile_hidden");
            }
        }
    }
}
void Board::GameOver(){
    end = true;
    for(int i = 0; i < board.size(); i++) {
        board[i].SetClickable(false);
        board[i].SetRightClickable(false);
        if (board[i].GetSecretState() == Tile::SecretState::mine) {
            board[i].SetSprite("mine");
        }
    }

}
void Board::RevealTile(Tile* tile){
    bool end = tile->Reveal();
    if(end){
        GameOver();
    }
}
void Board::AddFlag(Tile* tile){
    tile->ToggleFlag(debug);
}
Tile& Board::GetTile(int tile){
    return board[tile];
}
int Board::TileCount(){
    return width * length;
}
int Board::GetMineCount(){
    return mineCount;
}
void Board::SetMineCount(int mineCount1){
    mineCount = mineCount1;
}
bool Board::GetVictory(){
    int count = 0;
    for (unsigned int i = 0; i < TileCount(); i++) {
        if (board[i].GetState() == Tile::State::revealed)
            count++;
    }
    if (TileCount() - count - mineCount == 0) {
        for(int i = 0; i < board.size(); i++) {
            board[i].SetClickable(false);
            board[i].SetRightClickable(false);
            if (board[i].GetSecretState() == Tile::SecretState::mine) {
                board[i].SetSprite("flag");
            }
        }
        victory = true;
    }
    return victory;
}
bool Board::GetEnd(){
    return end;
}
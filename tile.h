//
// Created by Pablo Sabogal on 4/20/2024.
#ifndef MINESWEEPER_TILE_H
#define MINESWEEPER_TILE_H
#include <fstream>
#include "TextureManager.h"
#include <vector>
using namespace std;

class Tile{
private:
    sf::Vector2f position;
    vector<Tile*> radius;
    sf::Sprite sprite;
    bool clickable;
    bool right_clickable;
public:
    enum class State { hidden, revealed, flag };
    State state;
    State GetState();
    void SetState(State change);
    enum class SecretState { empty, mine, one, two, three, four, five, six, seven, eight, flag };
    SecretState secret_state;
    SecretState GetSecretState();
    void SetSecretState(SecretState change);
    Tile(sf::Vector2f position1, const char* texture, SecretState sec_state);
    sf::Sprite& GetSprite();
    Tile* GetRadius(int radius1);
    void SetClickable(bool change);
    void SetRightClickable(bool change);
    void SetSprite(const char* texture);
    bool Reveal();
    void ToggleFlag(bool debug);
    void AddInRadius(Tile* addradius);
    int GetCount();
    bool GetClickable();
    bool GetRightClickable();
};
#endif //MINESWEEPER_TILE_H

//
// Created by Pablo Sabogal on 4/20/2024.
//
#ifndef MINESWEEPER_TEXTURE_H
#define MINESWEEPER_TEXTURE_H
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <map>
using namespace std;
class TextureManager{
    static map<string, sf::Texture> textures;
    static void LoadTexture(const char* fileName);
public:
    static sf::Texture& GetTexture(const char* texture);
    static void Clear();
};


#endif //MINESWEEPER_TEXTURE_H

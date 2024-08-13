//
// Created by Pablo Sabogal on 4/21/2024.
//
#include "TextureManager.h"

map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(const char* fileName){
    string filePath = "files/images/";
    filePath += fileName;
    filePath += ".png";

    textures[fileName].loadFromFile(filePath);
}
void TextureManager::Clear(){
    textures.clear();
}
sf::Texture& TextureManager::GetTexture(const char* texture){
    if(textures.find(texture) == textures.end()){
        LoadTexture(texture);
    }
    return textures[texture];
}
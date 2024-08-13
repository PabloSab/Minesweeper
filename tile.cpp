//
// Created by Pablo Sabogal on 4/21/2024.
//
#include "tile.h"
#include <vector>
using namespace std;
Tile::Tile(sf::Vector2f position1, const char* texture, SecretState sec_state){
    sprite = sf::Sprite(TextureManager::GetTexture(texture));
    sprite.setPosition(position1.x, position1.y);
    position = position1;
    state = State::hidden;
    secret_state = sec_state;
    clickable = true;
    right_clickable = true;
}
Tile::State Tile::GetState(){
 return state;
}
void Tile::SetState(State change){
    state = change;
}
Tile::SecretState Tile::GetSecretState(){
    return secret_state;
}
void Tile::SetSecretState(SecretState change){
    secret_state = change;
}
sf::Sprite& Tile::GetSprite(){
    return sprite;
}
Tile* Tile::GetRadius(int radius1){
    return radius[radius1];
}
void Tile::SetClickable(bool change){
    clickable = change;
}
void Tile::SetRightClickable(bool change){
    right_clickable = change;
}
bool Tile::GetClickable(){
    return clickable;
}
bool Tile::GetRightClickable(){
    return right_clickable;
}
void Tile::SetSprite(const char* texture){
    sprite.setTexture(TextureManager::GetTexture(texture));
    sprite.setPosition(position);
}
bool Tile::Reveal(){
    if(clickable){
        if(state == State::hidden){
            state = State::revealed;
            if (secret_state == SecretState::mine) {
                SetSprite("mine");
                return true;
            }
            else if (secret_state == SecretState::one) {
                SetSprite("number_1");
                return false;
            }
            else if (secret_state == SecretState::two) {
                SetSprite("number_2");
                return false;
            }
            else if (secret_state == SecretState::three) {
                SetSprite("number_3");
                return false;
            }
            else if (secret_state == SecretState::four) {
                SetSprite("number_4");
                return false;
            }
            else if (secret_state == SecretState::five) {
                SetSprite("number_5");
                return false;
            }
            else if (secret_state == SecretState::six) {
                SetSprite("number_6");
                return false;
            }
            else if (secret_state == SecretState::seven) {
                SetSprite("number_7");
                return false;
            }
            else if (secret_state == SecretState::eight) {
                SetSprite("number_8");
                return false;
            }
            else {
                SetSprite("tile_revealed");
                for (unsigned int i = 0; i < GetCount(); i++)
                    GetRadius(i)->Reveal();
                return false;
            }
        }
    }
    return false;
}
void Tile::ToggleFlag(bool debug){
    if(right_clickable){
        if (state == State::hidden) {
            clickable = false;
            state = State::flag;
            SetSprite("flag");
        }
        else if (state == State::flag && debug && secret_state == SecretState::mine) {
            clickable = true;
            state = State::hidden;
            SetSprite("mine");
        }
        else if (state == State::flag) {
            clickable = true;
            state = State::hidden;
            SetSprite("tile_hidden");
        }
    }
}
void Tile::AddInRadius(Tile* addradius){
     radius.push_back(addradius);
}
int Tile::GetCount(){
    return radius.size();
}
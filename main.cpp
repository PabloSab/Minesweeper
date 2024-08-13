#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include "board.h"
#include "tile.h"
#include "TextureManager.h"
#include <chrono>
using namespace std;
sf::Text setText(std::string string1,bool bold, bool italic, std::string color, int size, int x, int y, sf::Font& font){
    sf::Text text;
    text.setFont(font);
    text.setString(string1);
    text.setCharacterSize(size);
    if(bold== true && italic ==true) {
        text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    }
    else if(bold == true){
        text.setStyle(sf::Text::Bold);
    }
    else if(italic == true){
        text.setStyle(sf::Text::Underlined);
    }
    if(color == "white"){
        text.setFillColor(sf::Color::White);
    }
    else if(color == "yellow"){
        text.setFillColor(sf::Color::Yellow);
    }
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,textRect.top + textRect.height/2.0f);
    text.setPosition(x,y);
    return text;
}

map<int, sf::Sprite> parseDigit(sf::Sprite digits){
    map<int, sf::Sprite> digitmap;
    for(int i =0;i<11;i++){
        sf::IntRect rect(i*21,0,21,32);
        digits.setTextureRect(rect);
        sf::Sprite sprite = digits;
        digitmap.emplace(i,sprite);
    }
    return digitmap;
}

int main() {
    std::ifstream file("files/config.cfg");
    std::string width, length, mineCount;
    std::getline(file, width);
    std::getline(file, length);
    std::getline(file, mineCount);
    int width1 = std::stoi(width) * 32;
    int cols = std::stoi(width);
    int rows = std::stoi(length);
    int length1 = (std::stoi(length) *32) +100;
    int tileCount = width1 *length1;
    bool change = false;
    sf::RenderWindow welcomewindow(sf::VideoMode(width1, length1), "Minsweeper");
    sf::Font font1;
    font1.loadFromFile("files/font.ttf");
    sf::Text welcomeText = setText("WELCOME TO MINESWEEPER!", true, true, "white", 24, width1/2, length1/2-150, font1);
    sf::Text nameText = setText("Enter your name:", true, false, "white", 20, width1/2, length1/2-75, font1);
    std::string name = "";
    std::string place ="|";
    sf::Text inputstring = setText(name+place, true, false, "yellow", 18, width1/2, length1/2-45, font1);
    while(welcomewindow.isOpen()) {
        sf::Event event;
        while(welcomewindow.pollEvent(event)) {
            if(event.type == sf::Event::Closed){
                welcomewindow.close();
            }
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::BackSpace){
                    if(name.size() != 0){
                        name.erase(name.end()-1);
                        inputstring.setString(name+place);
                    }
            }
                if(event.key.code == sf::Keyboard::Return){
                    if(name.size() ==0){}
                    else{
                        welcomewindow.close();
                        change = true;
                    }
                }
        }
            if(event.type == sf::Event::TextEntered){
                if(name.size() == 10){}
                else if ((event.text.unicode >= 65 && event.text.unicode<=90) || (event.text.unicode >= 97 && event.text.unicode<=122)){
                    name += static_cast<char>(event.text.unicode);
                    inputstring.setString(name+place);
                }
                if(!name.empty()){
                    name[0] = std::toupper(name[0]);
                    for(std::size_t i = 1 ; i < name.length() ; ++i){
                        name[i] = std::tolower(name[i]);
                    }
                    inputstring.setString(name+place);
                }
            }
        }
        welcomewindow.clear(sf::Color::Blue);
        welcomewindow.draw(welcomeText);
        welcomewindow.draw(nameText);
        welcomewindow.draw(inputstring);
        welcomewindow.display();
    }
    if(change) {
        sf::RenderWindow gamewindow(sf::VideoMode(width1, length1), "Game Window");
        auto start_time = chrono::high_resolution_clock::now();
        auto pauseTime = chrono::high_resolution_clock::now();
        auto elaspedPauseTime = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now()-pauseTime).count();
        bool pauseCheck = false;
        sf::Texture& digitText = TextureManager::GetTexture("digits");
        sf::Sprite digits;
        digits.setTexture(digitText);
        map<int,sf::Sprite> digitMap = parseDigit(digits);
        Board board = Board(cols,rows, stoi(mineCount));
        board.Initialize();
        Board boardclear = board;
        boardclear.SetTile();
        bool Check = true;
        TextureManager texture;
        sf::Sprite happyface;
        happyface.setTexture(texture.GetTexture("face_happy"));
        happyface.setPosition((cols/2 *32)-32,32*(rows+.5));
        sf::Sprite lose;
        lose.setTexture(texture.GetTexture("face_lose"));
        lose.setPosition((cols/2 *32)-32,32*(rows+.5));
        sf::Sprite win;
        win.setTexture(texture.GetTexture("face_win"));
        win.setPosition((cols/2 *32)-32,32*(rows+.5));
        sf::Sprite debug;
        debug.setTexture(texture.GetTexture("debug"));
        debug.setPosition((cols * 32)-304,32*(rows+.5));
        sf::Sprite pause;
        pause.setTexture(texture.GetTexture("pause"));
        pause.setPosition((cols * 32)-240,32*(rows+.5));
        sf::Sprite play;
        play.setTexture(texture.GetTexture("play"));
        play.setPosition((cols * 32)-240,32*(rows+.5));
        sf::Sprite leaderboard;
        leaderboard.setTexture(texture.GetTexture("leaderboard"));
        leaderboard.setPosition((cols * 32)-176,32*(rows+.5));
        while (gamewindow.isOpen()) {
            sf::Event event;
            while(gamewindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    gamewindow.close();
                }
                else if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                    auto pos = sf::Mouse::getPosition(gamewindow);
                    if(debug.getGlobalBounds().contains(pos.x,pos.y)){
                        board.Debug();
                    }
                    else if(pause.getGlobalBounds().contains(pos.x,pos.y)){
                        pauseCheck = !pauseCheck;
                    }
                    else if(pos.y<512){
                        Tile* currentSpot = &board.GetTile(25 * (pos.y / 32) + (pos.x / 32));
                        board.RevealTile(currentSpot);
                    }
                    else if(happyface.getGlobalBounds().contains(pos.x,pos.y)){
                        board.Clear();
                        board.Initialize();
                    }
                    else if(leaderboard.getGlobalBounds().contains(pos.x,pos.y)){
                        sf::RenderWindow leaderboardWindow(sf::VideoMode(width1, length1), "Leaderboard Window");
                        leaderboardWindow.clear(sf::Color::Blue);
                        sf::Text leader = setText("LEADERBOARD",true,true,"white",20,width1/2,length1/2-120,font1);
                        leaderboardWindow.draw(leader);
                        sf::Event event;
                        leaderboardWindow.display();
                    }
                    else if(lose.getGlobalBounds().contains(pos.x,pos.y)){
                        board.Clear();
                        board.Initialize();
                    }
                    if(pauseCheck){
                        Check = false;
                       pauseTime = chrono::high_resolution_clock::now();
                    }
                    else{
                        Check = true;
                        auto unpauseTime = chrono::high_resolution_clock::now();
                        elaspedPauseTime += chrono::duration_cast<chrono::seconds>(unpauseTime - pauseTime).count();
                    }
                }
                else if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right){
                    auto pos = sf::Mouse::getPosition(gamewindow);
                    if(pos.y<512){
                        Tile* currentSpot = &board.GetTile(cols* (pos.y / 32) + (pos.x / 32));
                        board.AddFlag(currentSpot);
                        if(currentSpot->GetClickable()){
                            board.SetMineCount(board.GetMineCount()+1);
                        }
                        else{
                            board.SetMineCount(board.GetMineCount()-1);
                        }
                    }
                }

            }
            auto gameDuration = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - start_time);
            int totalTime = gameDuration.count();
            int minutes;
            int seconds;
            if(!pauseCheck){
                totalTime = totalTime - elaspedPauseTime;
                minutes = totalTime/60;
                seconds = totalTime%60;
            }
            int minutes0 = minutes/10 %10;
            int minutes1 = minutes%10;
            int seconds0 = seconds/10 %10;
            int seconds1 = seconds%10-1;
            int mines0 = board.GetMineCount()/10%10;
            int mines1 = board.GetMineCount()%10;
            int mines2 = 0;
            if(board.GetMineCount()<0){
                mines2 = 10;
            }
            gamewindow.clear(sf::Color::White);
            if(!Check){
                for (unsigned int i = 0; i < boardclear.TileCount(); i++) {
                    gamewindow.draw(boardclear.GetTile(i).GetSprite());
                }
            }
            else {
                for (unsigned int i = 0; i < board.TileCount(); i++) {
                    gamewindow.draw(board.GetTile(i).GetSprite());
                }
            }
            digitMap[minutes0].setPosition((cols*32)-97,32*(rows+.5)+16);
            digitMap[minutes1].setPosition((cols*32)-76,32*(rows+.5)+16);
            digitMap[seconds0].setPosition((cols*32)-54,32*(rows+.5)+16);
            digitMap[seconds1].setPosition((cols*32)-33,32*(rows+.5)+16);
            digitMap[mines0].setPosition(33,32*(rows+.5)+16);
            digitMap[mines1].setPosition(54,32*(rows+.5)+16);
            digitMap[mines2].setPosition(12,32*(rows+.5)+16);
            gamewindow.draw(happyface);
            gamewindow.draw(debug);
            gamewindow.draw(leaderboard);
            gamewindow.draw(digitMap[minutes0]);
            gamewindow.draw(digitMap[minutes1]);
            gamewindow.draw(digitMap[seconds0]);
            gamewindow.draw(digitMap[seconds1]);
            gamewindow.draw(digitMap[mines0]);
            gamewindow.draw(digitMap[mines1]);
            gamewindow.draw(digitMap[mines2]);
            gamewindow.draw(pause);
            if(pauseCheck){
                gamewindow.draw(play);
            }
            else if(board.GetVictory() == true){
                gamewindow.draw(win);
            }
            else if(board.GetEnd() == true){
                gamewindow.draw(lose);
            }
            gamewindow.display();
        }
    }
        return 0;
}
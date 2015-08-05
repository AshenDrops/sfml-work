#include <SFML/Graphics.hpp>
#include <iostream>

#include "titlemenu.h"

#define winWidth 600
#define winHeight 600

#define fieldXOffset 75
#define fieldYOffset 75

#define fieldWidth 450
#define fieldHeight 450

#define gridWidth 3
#define gridHeight 3

sf::Vector2i coordToGrid(sf::Vector2i coords);

class GameState{
  public:
    GameState(){
      // Populate board
      for(int i=0;i<gridHeight;i++){
        for(int j=0;j<gridWidth;j++){
          this->board[i][j] = ' ';
        }
      }
      this->turn = 'x';
      this->turnNum = 0;
    }

    void choose(int x, int y){
      if(this->board[y][x] == ' '){
        this->board[y][x] = this->turn;
        this->turnNum++;
        if(this->turn == 'x'){this->turn='y';}else{this->turn='x';}
        if(this->turnNum == 9){
          //this->endGame();
          std::cout << "It's over dog" << std::endl;
        }
      }else{
        std::cout << "That tile has already been played in." << std::endl;
      }

      // Only necessary until I implement graphics
      this->draw();
    }

    void draw(){
      for(int i=0;i<gridHeight;i++){
        for(int j=0;j<gridWidth;j++){
          std::cout << this->board[i][j];
        }
        std::cout << std::endl;
      }
    }

  private:
    char board[gridHeight][gridWidth];
    char turn;
    int turnNum;
};

int main(){
  // Create window -- 200x200 for each "tile"
  sf::Window window(sf::VideoMode(winWidth, winHeight), "Tic-tac-toe", sf::Style::Close);

  // VSync
  window.setVerticalSyncEnabled(true);

  GameState game;
  bool mouseUp = true;

  sf::Texture logo;
  if(!logo.loadFromMemory(titlemenu_png, titlemenu_png_len, sf::IntRect(0, 272, 479, 100))){
    std::cout << "Error with loading titlemenu.png from memory" << std::endl;
  }

  // Main loop
  while(window.isOpen()){

    // Go through all of the events
    sf::Event event;
    while(window.pollEvent(event)){

      // If close event, close
      if(event.type == sf::Event::Closed){
        window.close();
      }


    }

    // Should work on game clock, not framerate

    bool pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    if(mouseUp && pressed){
      sf::Vector2i rawPosition = sf::Mouse::getPosition(window);
      sf::Vector2i position = coordToGrid(rawPosition);
      std::cout << "x:" << rawPosition.x << " y:" << rawPosition.y << std::endl;
      std::cout << "x:" << position.x << " y:" << position.y << std::endl;
      game.choose(position.x, position.y);
      mouseUp = false;
    }else if(!mouseUp && !pressed){
      mouseUp = true;
    }

  }

  return 0;
}

sf::Vector2i coordToGrid(sf::Vector2i coords){
  int widthFactor = fieldWidth/gridWidth;
  int heightFactor = fieldHeight/gridHeight;
  sf::Vector2i gridCoords(((coords.x-(coords.x%widthFactor))/widthFactor), ((coords.y-(coords.y%heightFactor))/heightFactor));
  return(gridCoords);
}

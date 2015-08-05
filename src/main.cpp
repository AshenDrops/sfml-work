#include <SFML/Graphics.hpp>
#include <iostream>

#include "data.h"

#define winWidth 600
#define winHeight 600

#define fieldXOffset 75
#define fieldYOffset 75

#define fieldWidth 450
#define fieldHeight 450

#define gridWidth 3
#define gridHeight 3

sf::Vector2i coordToGrid(sf::Vector2i coords);
sf::Vector2f gridToCoord(sf::Vector2i gridCoords);

sf::Sprite xys[9];
bool drawXys[9];

sf::Texture xImg;

sf::Texture oImg;

class GameState{
  public:
    GameState(){
      // Populate board
      for(int i=0;i<gridHeight;i++){
        for(int j=0;j<gridWidth;j++){
          this->board[i][j] = ' ';
        }
      }
      for(int i=0;i<8;i++){
        xTracker[i]=0;
        oTracker[i]=0;
      }
      this->turn = 'x';
      this->turnNum = 0;
    }

    void choose(int x, int y){
      if(this->board[y][x] == ' '){
        this->board[y][x] = this->turn;
        this->draw(x, y);
        this->checkForWin();
        this->turnNum++;
        if(this->turn == 'x'){this->turn='y';}else{this->turn='x';}
        if(this->turnNum == 9){
          //this->endGame();
          std::cout << "It's over dog" << std::endl;
        }
      }else{
        std::cout << "That tile has already been played in." << std::endl;
      }
    }

    void draw(int x, int y){
      int* tracker;
      if(this->turn == 'y'){
        tracker = oTracker;
      }else{
        tracker = xTracker;
      }
      tracker[x]++;
      tracker[3+y]++;
      if(x==y) tracker[6]++;
      if(x+y==2) tracker[7]++;
      xys[this->turnNum].setPosition(gridToCoord(sf::Vector2i(x,y)));
      drawXys[this->turnNum] = true;
    }

    void checkForWin(){
      if(this->turn == 'x'){
        for(int i=0;i<8;i++){
          if(xTracker[i] == 3){
            std::cout<<"You win dog (X)"<<std::endl;
          }
        }
      }else{
        for(int i=0;i<8;i++){
          if(oTracker[i] == 3){
            std::cout<<"You win dog (O)"<<std::endl;
          }
        }
      }
    }

  private:
    char board[gridHeight][gridWidth];
    char turn;
    int turnNum;
    int xTracker[8];
    int oTracker[8];
};

int main(){
  // Create window -- 200x200 for each "tile"
  sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Tic-tac-toe", sf::Style::Close);

  // VSync
  window.setVerticalSyncEnabled(true);

  GameState game;
  bool mouseUp = true;

  sf::Texture bg;
  if(!bg.loadFromMemory(background_png, background_png_len)){
    std::cout << "Error with loading titlemenu.png from memory" << std::endl;
  }
  sf::Sprite bgSprite;
  bgSprite.setTexture(bg);

  if(!oImg.loadFromMemory(o_png, o_png_len)){
    std::cout << "Error with loading o.png from memory" << std::endl;
  }
  if(!xImg.loadFromMemory(x_png, x_png_len)){
    std::cout << "Error with loading x.png from memory" << std::endl;
  }

  for(int i=0;i<9;i++){
    drawXys[i] = false;
    if(i%2 == 0){
      xys[i].setTexture(xImg);
    }else{
      xys[i].setTexture(oImg);
    }
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
      if(rawPosition.x > fieldXOffset && rawPosition.x < fieldWidth + fieldXOffset && rawPosition.y > fieldYOffset && rawPosition.y < fieldWidth + fieldXOffset){
        sf::Vector2i position = coordToGrid(rawPosition);
        game.choose(position.x, position.y);
      }
      mouseUp = false;
    }else if(!mouseUp && !pressed){
      mouseUp = true;
    }

    window.clear(sf::Color::Black);

    window.draw(bgSprite);
    for(int i=0;i<9;i++){
      if(drawXys[i]) window.draw(xys[i]);
    }

    window.display();


  }

  return 0;
}

sf::Vector2i coordToGrid(sf::Vector2i coords){
  int widthFactor = fieldWidth/gridWidth;
  int heightFactor = fieldHeight/gridHeight;
  int x = coords.x - fieldXOffset;
  int y = coords.y - fieldYOffset;
  sf::Vector2i gridCoords(((x-(x%widthFactor))/widthFactor), ((y-(y%heightFactor))/heightFactor));
  return(gridCoords);
}

sf::Vector2f gridToCoord(sf::Vector2i gridCoords){
  int widthFactor = fieldWidth/gridWidth;
  int heightFactor = fieldHeight/gridHeight;
  sf::Vector2f coords(fieldXOffset+(gridCoords.x*widthFactor),fieldYOffset+(gridCoords.y*heightFactor));
  return(coords);
}

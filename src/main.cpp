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

bool showWinner;

int waitSeconds;
bool resetClock;

sf::Texture xImg;

sf::Texture oImg;

sf::Text text;

class GameState{
  public:
    GameState(){
      setUp();
    }
    void setUp(){
      // Populate board
      for(int i=0;i<gridHeight;i++){
        for(int j=0;j<gridWidth;j++){
          this->board[i][j] = ' ';
        }
      }
      for(int i=0;i<9;i++){
        drawXys[i] = false;
      }
      for(int i=0;i<8;i++){
        xTracker[i]=0;
        oTracker[i]=0;
      }
      this->turn = 'x';
      this->turnNum = 0;
      this->winner = ' ';
    }

    void choose(int x, int y){
      if(this->board[y][x] == ' '){
        this->board[y][x] = this->turn;
        this->draw(x, y);
        bool hasWon = this->checkForWin();
        if(this->turn == 'x'){this->turn='o';}else{this->turn='x';}
        if(this->turnNum == 8||hasWon){
          this->turnNum = 0;
          this->endGame();
          this->setUp();
          std::cout << "It's over dog" << std::endl;
        }else{
          this->turnNum++;
        }
      }else{
        std::cout << "That tile has already been played in." << std::endl;
      }
    }

    void endGame(){
      waitSeconds = 10;
      resetClock = true;
      if(this->winner == 'o'){
        text.setString("O is the Winner");
      }else if(this->winner == 'x'){
        text.setString("X is the Winner");
      }else{
        text.setString("No winner");
      }
      text.setPosition((winWidth/2)-(text.getLocalBounds().width/2), 10);
    }

    void draw(int x, int y){
      int* tracker;
      if(this->turn == 'o'){
        tracker = oTracker;
      }else{
        tracker = xTracker;
      }
      tracker[x]++;
      tracker[3+y]++;
      if(x==y) tracker[6]++;
      if(x+y==2) tracker[7]++;
      std::cout << "Uh:" << this->turnNum << std::endl;
      xys[this->turnNum].setPosition(gridToCoord(sf::Vector2i(x,y)));
      drawXys[this->turnNum] = true;
    }

    bool checkForWin(){
      /* this->printWinCheck(); */
      if(this->turn == 'x'){
        for(int i=0;i<8;i++){
          if(xTracker[i] == 3){
            std::cout<<"You win dog (X)"<<std::endl;
            this->winner = 'x';
            return true;
          }
        }
      }else{
        for(int i=0;i<8;i++){
          if(oTracker[i] == 3){
            std::cout<<"You win dog (O)"<<std::endl;
            this->winner = 'o';
            return true;
          }
        }
      }
      return false;
    }

  private:
    char board[gridHeight][gridWidth];
    char turn;
    int turnNum;
    int xTracker[8];
    int oTracker[8];
    char winner;
};

int main(){
  // Create window -- 200x200 for each "tile"
  sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Tic-tac-toe", sf::Style::Close);

  // VSync
  window.setVerticalSyncEnabled(true);

  sf::Clock clock;

  waitSeconds = 0;
  resetClock = false;

  GameState game;
  bool mouseUp = true;

  sf::Font font;
  if(!font.loadFromMemory(quicksand_bold_otf, quicksand_bold_otf_len)){
    std::cout << "Font failed to load" << std::endl;
  }
  text.setFont(font);
  text.setCharacterSize(48);
  text.setColor(sf::Color::Black);

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

    if(resetClock){
      clock.restart();
      resetClock = false;
    }

    if(waitSeconds != 0){
      window.draw(text);
      if(clock.getElapsedTime().asSeconds() >= waitSeconds){
        waitSeconds = 0;
      }
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

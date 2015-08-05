#include <SFML/Graphics.hpp>

int main(){
  // Create window -- 200x200 for each "tile"
  sf::Window window(sf::VideoMode(600, 600), "Tic-tac-toe", sf::Style::Close);

  //VSync
  window.setVerticalSyncEnabled(true);

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
  }

  return 0;
}

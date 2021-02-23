#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"

using namespace sf;

std::unique_ptr<Player> player{ new Player };

int main(){
  sf::RenderWindow window(sf::VideoMode(800, 600), "Tile Maze");
  static Clock clock;
  float dt = clock.restart().asSeconds();

  while (window.isOpen()){
      sf::Event event;
      while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){
        window.close();
      }
    }

      
    player->Update(dt);
    
    window.clear();
    player->Render(window);
    window.display();
  }
  return 0;
}

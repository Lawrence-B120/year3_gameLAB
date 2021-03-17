#include <SFML/Graphics.hpp>
#include <iostream>
#include "Windows.h"
#include "player.h"
#include "LevelSystem.h"

using namespace sf;
using namespace std;

std::unique_ptr<Player> player{ new Player };

void Load() {
    //gets the res in lab build
 /* char c[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, c);
    string s = string(c);
    ls::loadLevelFile(s + "\\res\\maze_2.txt");*/

    //gets  the res in debug
    char c[MAX_PATH];
    GetModuleFileName(NULL, c, MAX_PATH);
    string s = string(c);
    s = s.substr(0, s.find_last_of("\\/"));
    ls::loadLevelFile(s + "\\res\\maze_2.txt");
    
    //print the level to console
    for (size_t y = 0; y < ls::getHeight(600); ++y) {
        for (size_t x = 0; x < ls::getWidth(800); ++x) {
            std::cout << ls::getTile({ x, y });
        }
        std::cout << endl;
    }
}

void Render(RenderWindow window) {
    ls::Render(window);
}

int main(){
  sf::RenderWindow window(sf::VideoMode(800, 600), "Tile Maze");
  static Clock clock;
  float dt = clock.restart().asSeconds();
  Load();
  while (window.isOpen()){
      sf::Event event;
      while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){
        window.close();
      }
    }

    player->Update(dt);
    
    window.clear();
    //Render(window);
    ls::Render(window);
    player->Render(window);
    window.display();
  }
  return 0;
}

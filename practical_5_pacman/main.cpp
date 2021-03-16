#include <SFML/Graphics.hpp>
#include "entity.h"
#include "player.h"
#include "ghost.h"

using namespace sf;
using namespace std;

//std::unique_ptr<Player> player{ new Player };
//std::vector<Ghost> ghosts;
//Ghost ghosts[4];
std::vector<std::unique_ptr<Ghost>> ghosts;

std::vector<Entity*> entity;

void Load() {
    for (int i = 0; i < 4; i++)
    {
        Ghost* gho = new Ghost();
        entity.push_back(gho);
    }
    Player* player = new Player();
    entity.push_back(player);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "PacMan");
    static Clock clock;
    float dt = clock.restart().asSeconds();
    Load();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

       // player->Update(dt);
        for (int i = 0; i < 5; i++)
        {
            //ghosts[i].Update(dt);
            entity[i]->Update(dt);
        }
        window.clear();
        //Render(window);
       
        //player->Render(window);
        for (int i = 0; i < 5; i++)
        {
            //ghosts[i].Render(window);
            entity[i]->Render(window);
        }
        window.display();
    }
    return 0;
}

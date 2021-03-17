#include <SFML/Graphics.hpp>
#include "entity.h"
#include "player.h"
#include "ghost.h"

using namespace sf;
using namespace std;

EntityManager em;

void Load() {
    for (int i = 0; i < 4; i++)
    {
        Ghost* gho = new Ghost();
        shared_ptr<Ghost> lul = shared_ptr<Ghost>(gho);

        em.list.push_back(lul);       
    }
    Player* player = new Player();

    shared_ptr<Player> play = shared_ptr<Player>(player);
    em.list.push_back(play);
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
            //entity[i]->Update(dt);
            em.update(dt);
        }
        window.clear();
        //Render(window);
       
        //player->Render(window);
        for (int i = 0; i < 5; i++)
        {
            //ghosts[i].Render(window);
            //entity[i]->Render(window);
            em.render(window);
        }
        window.display();
    }
    return 0;
}

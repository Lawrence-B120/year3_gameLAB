#include <SFML/Graphics.hpp>
#include "entity.h"
#include "player.h"
#include "ghost.h"
#include "system_renderer.h"
#include "pacman.h"

using namespace sf;
using namespace std;

EntityManager em;

void Load() {
 /*   for (int i = 0; i < 4; i++)               moved to pacman.cpp
    {
        Ghost* gho = new Ghost();
        shared_ptr<Ghost> lul = shared_ptr<Ghost>(gho);

        em.list.push_back(lul);       
    }
    Player* player = new Player();

    shared_ptr<Player> play = shared_ptr<Player>(player);
    em.list.push_back(play);*/
    
    //instantiating the scenes
    gameScene.reset(new GameScene());
    menuScene.reset(new MenuScene());
    gameScene->load();
    menuScene->load();

    //start at main menu
    activeScene = menuScene;
}

void Update() {
    static Clock clock;
    float dt = clock.restart().asSeconds();
    activeScene->update(dt);
}

void Render(RenderWindow& window) {
    activeScene->render();
    //flush to screen
    Renderer::render();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(700, 725), "PacMan");
    static Clock clock;
    float dt = clock.restart().asSeconds();
    Load();
    Renderer::initialise(window);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

       //// player->Update(dt);
        //for (int i = 0; i < 5; i++)
        //{
        //    //ghosts[i].Update(dt);
        //    //entity[i]->Update(dt);
        //    em.update(dt);
        //}
        Update();
        window.clear();
        Render(window);
        ////Render(window); 
        ////player->Render(window);
        ////for (int i = 0; i < 5; i++)
        ////{
        ////    //ghosts[i].Render(window);
        ////    //entity[i]->Render(window);
        ////    em.render(window);
        ////}
        //for (int i = 0; i < 5; i++)
        //{
        //    //Renderer::queue(em.render(window));
        //    //Renderer::queue(em.list[i]->getShape());
        //    Renderer::queue(em.list[i]->getShape());
        //}
        //Renderer::render();

        window.display();
    }
    return 0;
}

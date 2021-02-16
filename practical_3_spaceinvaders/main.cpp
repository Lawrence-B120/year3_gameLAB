#include <SFML/Graphics.hpp>
#include <iostream>
#include "ship.h"
#include "game.h"
#include "bullet.h"

using namespace sf;
using namespace std;

sf::Texture spritesheet;
sf::Sprite invader;

std::vector<Ship*> ships;
Player* player;
int heightCount = 10;
int widthCount = 32;

void Load() {
    if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
        cerr << "Failed to load spritesheet!" << std::endl;
    }
    invader.setTexture(spritesheet);
    invader.setTextureRect(sf::IntRect(0, 0, 32, 32));
    //sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

#pragma region spawner
	//Invader* inv;
	//for (int i = 0; i < 3; i++)
	//{
	//	heightCount = 10;
	//	widthCount += widthCount;
	//	auto rect = IntRect(0,0, widthCount,32);
	//	
	//	//auto inv = new Invader(rect, { 100,100 });
	//	//ships.push_back(inv);
	//	for (int j = 0; j < 10; j++)
	//	{
	//		heightCount += 30;
	//		Vector2f position = Vector2f(100, heightCount);
	//		auto inv = new Invader(rect, position);
	//		ships.push_back(inv);
	//	}		
	//}
#pragma endregion

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			Invader* inv = new Invader(sf::IntRect(i * 32, 0, 32, 32), { j * 50.f + 50, i * 40.f + 50 });
			//i * 32 at the start changes the type of sprite for each row
			//j* 50.f + 50 is horizontal spacing
			//i * 40.f is for vertical spacing
			ships.push_back(inv);
		}
	}

	player = new Player();
	ships.push_back(player);
	
	//Important note, we used the New() operator here, which created the ship on the heap.If we wanted a stack version, 
	//we omit the new Newand would use Invader ‘inv = Invader()’.

	//As we are going to be storing the invader in a vector that will also later contain the player, 
	//this vector itself cannot be of type Invader.Instead, we need to use the base class that both inherit from - 
	//the Ship class.The way we have set this up, however, we can’t create a vector, as that would try to construct an abstract class.Instead, 
	//we create a vector of pointers to the objects!
}

void Update(RenderWindow& window) {
	static Clock clock;
	float dt = clock.restart().asSeconds();
	for (auto& s : ships) {
		s->Update(dt);
	}
	Bullet::Update(dt);
}

void Render(RenderWindow& window) {
	for (const auto s : ships) {
		window.draw(*s);
	}
	Bullet::Render(window);
}

int main(){
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Space_Invaders");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}



//NOTES--------------------------------------------------------------------------------------
//Now we need to call the update function for all of our ships every frame.Due to polymorphism this is very simple : 
//as Update() is a virtual function, when we call Update() on a Ship pointer it will run the Update() function of whatever is being pointed to.In other words, 
//if we call Update() on an item in a vector<*Ship> collection, and the Ship object that is pointed to is an Invader, 
//then the Update() function in the Invader class is called.If it is a Player object, the Update() function in the Player class is called.Got that ?

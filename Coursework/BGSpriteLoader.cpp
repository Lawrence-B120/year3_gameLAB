#include "BGSpriteLoader.h"
#include <iostream>


using namespace std;
using namespace sf;

Texture BGspriteSheet;
std::vector<Sprite> sprites;

void BGSpriteLoader::ReadSpriteSheet()
{
    if (!BGspriteSheet.loadFromFile("res/img/TileSet-7-560x80.png")) {
        cerr << "Failed to load spritesheet!" << std::endl;
    }

    for (int i = 0; i < 7; i++)
    {
        sprites[i].setTexture(BGspriteSheet);
        sprites[i].setTextureRect(sf::IntRect(i * 80, 0, 80, 80));
    }
}

void BGSpriteLoader::Load(lvlSys::TILE t)
{
 
    if (t == lvlSys::EMPTY)
    {
        //place sprite at position of t
    }
    else if (t == lvlSys::WALL)
    {
        //..
    }
    
}
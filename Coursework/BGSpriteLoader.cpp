#include "BGSpriteLoader.h"
#include <iostream>

using namespace std;
using namespace sf;

Texture BGspriteSheet;
std::vector<Sprite> totalSprites;
std::vector<Sprite> spriteTypes;

void BGSpriteLoader::ReadSpriteSheet()
{
    if (!BGspriteSheet.loadFromFile("res/img/TileSet-7-420x60.png")) {
        cerr << "Failed to load spritesheet!" << std::endl;
    }

    for (int i = 0; i < 7; i++)
    {
        spriteTypes.push_back(Sprite());
        std::cout << "";
        spriteTypes[i].setTexture(BGspriteSheet);
        spriteTypes[i].setTextureRect(sf::IntRect(i * 60, 0, 60, 60));
    }
}

void BGSpriteLoader::Load()
{
    auto tiles = lvlSys::getTileNames();
    //for each tile in the list, how many are of wall or empty etc.
    //want to set the position of all of the sprites
    auto width = lvlSys::getWidth();
    std::cout << "";
    for (int i = 0; i < tiles.size(); i++)
    {
        if (tiles[i] == lvlSys::WALL)
        {
            totalSprites.push_back(spriteTypes[1]);
        }
        else if (tiles[i] == lvlSys::CAMERA1)
        {
            totalSprites.push_back(spriteTypes[3]);
        }
        else if (tiles[i] == lvlSys::CAMERA2)
        {
            totalSprites.push_back(spriteTypes[4]);
        }
        else if (tiles[i] == lvlSys::CAMERA3)
        {
            totalSprites.push_back(spriteTypes[5]);
        }
        else if (tiles[i] == lvlSys::CAMERA4)
        {
            totalSprites.push_back(spriteTypes[6]);
        }
        else if (tiles[i] == lvlSys::ENEMY)
        {
            totalSprites.push_back(spriteTypes[2]);
        }
        else if (tiles[i] == lvlSys::FINISH)
        {
            totalSprites.push_back(spriteTypes[2]);
        }
        else if (tiles[i] == lvlSys::START)
        {
            totalSprites.push_back(spriteTypes[2]);
        }
        else if (tiles[i] == lvlSys::EMPTY)
        {
            totalSprites.push_back(spriteTypes[0]);
        }
        else if (tiles[i] == lvlSys::PUZZLE)
        {
            totalSprites.push_back(spriteTypes[2]);
        }
        totalSprites[i].setPosition(lvlSys::getTilePosition(Vector2ul(i % width, (i - (i % width)) / width)));
    }


    //have 7 textures in the sprite list, need to duplicate these sprites at the positions
    //of the tiles where WALL or EMPTY are and place the sprite on that position.

    //give each tile a sprite and set that sprite to the corresponding texture sheet one. so set a WALL sprite to the 2nd sprite
    //in the sheet.
    
}

void BGSpriteLoader::Render(RenderWindow& window)
{
    for (int i = 0; i < totalSprites.size(); i++)
    {
        window.draw(totalSprites[i]);
    }
}
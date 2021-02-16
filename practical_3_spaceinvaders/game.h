#pragma once
#include <SFML/Graphics.hpp>
#include "ship.h"
#include "bullet.h"
constexpr uint16_t gameWidth = 800;
constexpr uint16_t gameHeight = 600;
constexpr uint16_t invaders_rows = 5;
constexpr uint16_t invaders_columns = 12;

extern sf::Texture spritesheet; //this makes this variable available to the ship.cpp class
							//tells any other script that inlcudes game.h that this variable exists

extern std::vector<Ship*> ships; //handle to ship.cpp for movement code. remove this and see errors in ship.cpp


extern class Player* player;
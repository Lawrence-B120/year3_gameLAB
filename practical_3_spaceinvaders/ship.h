#pragma once
#include <SFML/Graphics.hpp>

class Ship : public sf::Sprite {
protected:
	sf::IntRect _sprite;
	Ship(); //default constructopr is hidden
	bool _exploded = false;
public:
	explicit Ship(sf::IntRect ir); //constructor that takes in a sprite
	 //Pure virtual deconstructor -- makes this an abstract class and avoids undefined behaviour
	virtual ~Ship() = 0;
	//Update, virtual so can be overridden, but not pure virtual
	virtual void Update(const float& dt);

	bool is_exploded() const;
	virtual void Explode();
};

class Invader : public Ship{
	public:
		Invader(sf::IntRect ir, sf::Vector2f pos);
		Invader();
		void Update(const float& dt) override;
		static bool direction;
		static float speed;
	
};
	
class Player : public Ship {
public:
	Player();
	void Update(const float& dt) override;
	static float speed;
};
	
#pragma once
#include "ecm.h"

class Player : public Entity {
private:
	float _speed;

public:
	void Update(double dt) override;
	Player();
	//const std::unique_ptr<sf::Shape> getShape() override;	/////
	//void Render(sf::RenderWindow& window) const override;
};
#pragma once
#include "ecm.h"

class Ghost : public Entity {
private:
	float _speed;
	float _counter = 1.0f;

public:
	void Update(double dt) override;
	Ghost();
	//void Render(sf::RenderWindow& window) const override;
};
#pragma once
#include <ecm.h>
#include "cmp_actor_movement.h"

class EnemyAIComponent : public ActorMovementComponent {
protected:
	sf::Vector2f _direction;
	enum state { ROAMING, ROTATING, ROTATED };
	state _state;
public:
	void update(double dt) override;
};
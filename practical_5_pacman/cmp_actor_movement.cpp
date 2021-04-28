#include "cmp_actor_movement.h"
#include <LevelSystem.h>

using namespace sf;
using namespace std;

int randMax = 4, randMin = 0;
int randRange = randMax - randMin + 1;
int result = 0;
float _counter = 1.0f;

const Keyboard::Key controls[4] = {
    Keyboard::A,  //player Left
    Keyboard::D,   //player Right
    Keyboard::W,   //player Up
    Keyboard::S,    //player Down
};

void ActorMovementComponent::update(double dt) {

}

ActorMovementComponent::ActorMovementComponent(Entity* p)
    : _speed(100.0f), Component(p) {}

bool ActorMovementComponent::validMove(const sf::Vector2f& pos) {
    return (LevelSystem::getTileAt(pos) != LevelSystem::WALL);
}

void ActorMovementComponent::move(const sf::Vector2f& p) {
    auto pp = _parent->getPosition() + p;
    if (validMove(pp)) {
        _parent->setPosition(pp);
    }
}

void ActorMovementComponent::move(float x, float y) {
    move(Vector2f(x, y));
}
float ActorMovementComponent::getSpeed() const { return _speed; }
void ActorMovementComponent::setSpeed(float speed) { _speed = speed; }

//void ActorMovementComponent::render() {}

PlayerMovementComponent::PlayerMovementComponent(Entity* p) : ActorMovementComponent(p) {}
void PlayerMovementComponent::update(double dt) {
    auto pos = Vector2f(0, 0); //before i was adding the position to itself. not just adding 1 or 2
    if (Keyboard::isKeyPressed(controls[0])) { //left
        _speed = -2.1f;
        pos = Vector2f(_speed, pos.y);
    }
    if (Keyboard::isKeyPressed(controls[1])) { //right
        _speed = 2.1f;
        pos = Vector2f(_speed, pos.y);
    }
    if (Keyboard::isKeyPressed(controls[2])) { //up
        _speed = -2.1f;
        pos = Vector2f(pos.x, _speed);
    }
    if (Keyboard::isKeyPressed(controls[3])) { //down
        _speed = 2.1f;
        pos = Vector2f(pos.x, _speed);
    }
    move(pos);
}

EnemyAIComponent::EnemyAIComponent(Entity* p) : ActorMovementComponent(p) {}



//void EnemyAIComponent::update(double dt) {
//	auto pos = Vector2f(0, 0); //before i was adding the position to itself. not just adding 1 or 2
//	_speed = 2.1f;
//	if (_counter <= 0.0f) //timer
//	{
//
//		result = rand() % randRange + randMin;
//		_counter = 100.0f;
//	}
//	_counter--;
//
//	// speed is between 1 and 2, then x vel, else y vel
//	if (result <= 2)
//	{
//		//xpos
//		if (result < 2)
//		{
//			if (_speed < 0)
//			{
//				_speed *= -1;
//			}
//		}
//		else
//		{
//			if (_speed > 0)
//			{
//				_speed *= -1;
//			}
//		}
//		pos = Vector2f(_speed, pos.y);
//	}
//	else if (result > 2)
//	{
//		//ypos
//		pos = Vector2f(pos.x, _speed);
//	}
//
//	//apply speed and direction
//	//_speed = 2.1f;
//
//	//if (_position.x < 0 || _position.x > 800 || _position.y < 0 || _position.y > 600) //bounds, opposite direction
//	//{
//	//	_speed *= -1;
//	//}
//
//	move(pos);
//	
//}
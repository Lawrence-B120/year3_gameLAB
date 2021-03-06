#include "player.h"
using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
    Keyboard::A,  //player Left
    Keyboard::D,   //player Right
    Keyboard::W,   //player up
    Keyboard::S,    //player down
};

void Player::Update(double dt) {
    //Move in four directions based on keys
    //auto pos = getPosition();
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
    
    Entity::Update(dt);
}

Player::Player()
    : _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
    _shape->setFillColor(Color::Magenta);
    _shape->setOrigin(Vector2f(25.f, 25.f));

}

void Player::Render(sf::RenderWindow& window) const {
    window.draw(*_shape);
}
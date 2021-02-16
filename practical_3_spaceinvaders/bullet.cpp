//#include "bullet.h"
//#include "game.h"
//using namespace sf;
//using namespace std;
//
//unsigned char Bullet::bulletPointer;
//Bullet Bullet::bullets[256];
//
//Bullet::Bullet() {};
//
////void Bullet::Init() {
////    for (auto& a : bullets)
////    {
////        a.setPosition(10, 10);
////        a.setTexture(spritesheet);
////        a.setOrigin(16, 16);
////    }
////}
//
//void Bullet::Update(const float& dt)
//{
//    for (auto& b : bullets) {
//        b._Update(dt);
//    }
//}
//
//void Bullet::_Update(const float& dt) {
//    move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));
//}
//
//void Bullet::Render(sf::RenderWindow& window)
//{
//
//}
//
////Bullet::~Bullet() = default;

#include "bullet.h"
#include "game.h"
#include "ship.h"
using namespace sf;
using namespace std;

//Create definition for the constructor
//...
unsigned char Bullet::bulletPointer;
Bullet Bullet::bullets[256];
Bullet::Bullet() {};

void Bullet::Update(const float& dt)
{
    for (auto& b : bullets) {
        b._Update(dt);
    }
}

void Bullet::_Update(const float& dt) {
    if (getPosition().y < -32 || getPosition().y > gameHeight + 32) {
        //off screen - do nothing
        return;
    }
    else {
        move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));
        const FloatRect boundingBox = getGlobalBounds();
        
        for (auto s : ships) {
            if (!_mode && s == player) {
                //player bulelts don't collide with player
                continue;
            }
            if (_mode && s != player) {
                //invader bullets don't collide with other invaders
                continue;
            }
            if (!s->is_exploded() &&
                s->getGlobalBounds().intersects(boundingBox)) {
                //Explode the ship
                s->Explode();
                //warp bullet off-screen
                setPosition(-100, -100);
                return;
            }
        }
    }
};

void Bullet::Render(sf::RenderWindow& window)
{
    for (const auto b : bullets) {
        window.draw(b);
    }
}

void Bullet::Fire(const sf::Vector2f& pos, const bool mode) {
    auto b = &bullets[bulletPointer++];
    b->setPosition(pos);
    b->_mode = mode;

    b->_sprite = IntRect(64, 32, 32, 32);
    b->setTexture(spritesheet);
    b->setTextureRect(b->_sprite);
    b->setOrigin(16, 16);
}
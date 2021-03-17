#include "entity.h"
using namespace std;
using namespace sf;

const Vector2f Entity::getPosition() { return _position; }

void Entity::setPosition(const Vector2f& pos) { _position = pos; }

void Entity::move(const Vector2f& pos) { _position += pos; }

void Entity::Update(const double dt) {
    _shape->setPosition(_position);
}

Entity::Entity(unique_ptr<Shape> s) : _shape(std::move(s)) {}

//struct cpp
void EntityManager::update(double dt) {
    for (int i = 0; i < list.size(); i++) {
        list[i]->Update(dt);
        //_shape->setPosition(_position);
   }
    
};

void EntityManager::render(sf::RenderWindow& window) {
    for (int i = 0; i < list.size(); i++) {
        list[i]->Render(window);
    }
    //window.draw(*_shape);
};
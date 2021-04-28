#include "cmp_actor_movement.h"
#include "LevelSystem.h"

using namespace sf;
using namespace std;

static const Vector2i directions[] = { {1, 0}, {0, 1}, {0, -1}, {-1, 0} };


void EnemyAIComponent::update(double dt) {
    _speed = 200.0f;
    //amount to move
    const auto mva = (float)(dt * _speed);
    //Curent position
    const Vector2f pos = _parent->getPosition();
    //Next position
    const Vector2f newpos = pos + _direction * mva;
    //Inverse of our current direction
    const Vector2i baddir = -1 * Vector2i(_direction);
    //Random new direction
    Vector2i newdir = directions[(rand() % 4)];

    switch (_state) {
    case ROAMING:
        if (LevelSystem::getTileAt(pos) == LevelSystem::WALL || LevelSystem::getTileAt(newpos) == LevelSystem::WALL)// Wall in front or at waypoint
        {
            _state = ROTATING; // start rotate
        }
        else {
            _state = ROAMING; //keep moving
        }
        break;

    case ROTATING:
        while (
            // Don't reverse
            newdir != baddir
            // and Don't pick a direction that will lead to a wall
            && LevelSystem::getTileAt(newpos) != LevelSystem::WALL
            ) {
            _direction = Vector2f(newdir); // pick new direction
        }
        _direction = Vector2f(newdir);
        _state = ROTATED;
        break;

    case ROTATED:
        //have we left the waypoint?
        if (LevelSystem::getTileAt(pos) != LevelSystem::WAYPOINT) {
            _state = ROAMING; //yes
        }
        move(_direction * mva); //No
        break;
    }
    ActorMovementComponent::update(dt);
}
#include "ship.h"
#include "game.h"
#include "bullet.h"
using namespace sf;
using namespace std;

Ship::Ship() {};
bool Invader::direction;
float Invader::speed = 1.0f;

float Player::speed;



const Keyboard::Key controls[3] = {
	Keyboard::A,  //player Left
	Keyboard::D,   //player Right
	Keyboard::W,   //Fire
};

Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

void Ship::Update(const float& dt) {}

Ship::~Ship() = default;

Invader::Invader() : Ship() {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
}

void Invader::Update(const float& dt) {
	Ship::Update(dt);
	for (int i = 0; i < ships.size() - 1; i++) {
		ships[i]->move(dt * (direction ? 1.0f : -1.0f) * speed, 0); //directional movement bool
	}
	
	if ((direction && getPosition().x > gameWidth - 16) || (!direction && getPosition().x < 16)) {
		direction = !direction;
		for (int i = 0; i < ships.size() - 1; ++i) {
			ships[i]->move(0, 24.0f);
		}
	}

	static float fireTime = 0.0f;
	fireTime -= dt;

	if (fireTime <= 0 && rand() % 100 == 0)
	{
		Bullet::Fire(Vector2f(getPosition().x, getPosition().y - 20), true);
		fireTime = 4.0f + (rand() % 60);
	}
}

Player::Player() : Ship(IntRect(160, 32, 32, 32)) {
	setPosition({ gameHeight * .5f, gameHeight - 32.f });
}

void Player::Update(const float& dt) { 
	Ship::Update(dt);		
	static float fireTime = 0.0f;
	fireTime -= dt;
	//static vector<Bullet*> bullets;
	if (fireTime <= 0 && Keyboard::isKeyPressed(controls[2])) {
		//bullets.push_back(new Bullet(getPosition(), false));
		Bullet::Fire(Vector2f(getPosition().x, getPosition().y - 20), false);
		fireTime = 0.7f;
	}
	//for (const auto s : bullets) {
	//	bullets.Update(dt);
	//}
	
	
	//key movement
	if (Keyboard::isKeyPressed(controls[0])) {
		speed = -3.0f;
	}
	if (Keyboard::isKeyPressed(controls[1])) {
		speed = 3.0f;
	}

	if ((getPosition().x < gameWidth - 32) && getPosition().x > 16) { //applying speed & boundary setting
		ships[ships.size() - 1]->move(speed, 0);	
	}
	else if (getPosition().x > gameWidth - 32) {
		ships[ships.size() - 1]->setPosition(getPosition().x - 30, getPosition().y);
	}
	else {
		ships[ships.size() - 1]->setPosition(getPosition().x + 20, getPosition().y);
	}
	
	
}

bool Ship::is_exploded() const
{
	return false;
}

void Ship::Explode() {
	setTextureRect(IntRect(128, 32, 32, 32));
	_exploded = true;
}
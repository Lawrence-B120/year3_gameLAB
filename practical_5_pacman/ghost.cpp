//#include "ghost.h"
//
//using namespace sf;
//using namespace std;
//
//int randMax = 4, randMin = 0;
//int randRange = randMax - randMin + 1;
//int result = 0;
//
//Color colors[4] = { Color::Blue, Color::Red, Color::Magenta, Color::Green };
//
//void ColorSetup() { //runs a randomiser called in the constructor for random colours in a list
//	result = rand() % randRange + randMin;
//}
//
//void Ghost::Update(double dt) {
//	//auto pos = Vector2f(getPosition().x, getPosition().y);
//	auto pos = Vector2f(0, 0); //before i was adding the position to itself. not just adding 1 or 2
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
//	move(pos);
//	if (_position.x < 0 || _position.x > 800 || _position.y < 0 || _position.y > 600) //bounds, opposite direction
//	{
//		_speed *= -1;
//	}
//
//	Entity::Update(dt);
//}
//
////Ghost::Ghost() : _speed(2.0f), Entity(make_unique<CircleShape>(25.f)) {
////	ColorSetup();
////	_shape->setFillColor(colors[result]);
////	_shape->setOrigin(Vector2f(15.f, 15.f));
////	setPosition(Vector2f(200, 200));
////}
////
////void Ghost::Render(sf::RenderWindow& window) const {
////	window.draw(*_shape);
////	_shape.get();
////}
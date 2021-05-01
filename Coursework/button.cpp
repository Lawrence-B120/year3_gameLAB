#include "button.h"
#include "GameManager.h"
#include "SystemRenderer.h"

using namespace sf;
using namespace std;

float timer = 0.0f;

void Button::load(Color c, int cs, string s, Vector2f p, Font f) {
	_color = c;
	_charSize = cs;
	_string = s;
	_position = p;
	_font = f;

	auto xLength = _string.length() * _charSize;
	_rect = IntRect(_position.x, _position.y, xLength, _charSize);
}

void Button::update(double dt, RenderWindow& window) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)
		&& _rect.contains(static_cast<sf::Vector2i>(sf::Mouse::getPosition(window))) && timer <= 0.0f)
	{
		std::cout << "mouse click";
		timer = 100.0f;
	}
	timer--;
}

void Button::render() {
	Text rendertext;
	//rendertext.setFont(_font);
	rendertext.setColor(_color);
	rendertext.setCharacterSize(_charSize);
	rendertext.setString(_string);
	rendertext.setPosition(_position);
	rendertext.setFont(_font);
	Renderer::getWindow().draw(rendertext);
}

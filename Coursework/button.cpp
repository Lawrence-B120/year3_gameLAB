#include "button.h"
#include "GameManager.h"
#include "SystemRenderer.h"

using namespace sf;
using namespace std;

sf::Color white2 = Color(255, 255, 255, 255);
string textToString;
void Button::load(string s) {
	//gets the currently loaded font type
	sf::Font fontType = MenuScene::GetFont();

	_text.setFont(fontType);
	_text.setColor(white2);
	_text.setCharacterSize(24);
	_text.setString(s);
	textToString = _text.getString();
	auto xLength = textToString.length() * _text.getCharacterSize();
	_rect = IntRect(_position.x, _position.y, xLength, _text.getCharacterSize());
}

//void Button::setPos(Vector2f pos) {
//	_position = pos; 
//}
//
//void Button::setText(Text t) {
//	t = _text;
//}
void Button::update(double dt, RenderWindow& window) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) 
		&& _rect.contains(static_cast<sf::Vector2i>(sf::Mouse::getPosition(window))))
	{
		std::cout << "mouse click";
	}
}

void Button::render(RenderWindow& window) {
	window.draw(_text);
	//Renderer::queue(&_text);
}
//void Button::Render(RenderWindow& window)
//{
//	window.draw(_text);
//}
#pragma once
#include <SFML/Graphics.hpp>

class Button {
private:
	sf::Text _text;
	sf::Vector2f _position;
	sf::IntRect _rect;
public:
	Button() = default;
	void update(double dt, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	//static void Render(sf::RenderWindow& window);
	void setPos(sf::Vector2f pos) { _position = pos; };
	void setText(sf::Text t) { t = _text; };
	void load(std::string s);
};

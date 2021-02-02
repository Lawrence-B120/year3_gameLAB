#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
	Keyboard::A,  //player 1 up
	Keyboard::Z,   //player 1 down
	Keyboard::Up,  //player 2 up
	Keyboard::Down  //player 2 down
};

const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
Vector2f ballVelocity;
bool server = false;
bool twoPlayer = false;

Font font;
Text text;
Color white = Color(255, 255, 255, 255);

CircleShape ball;
RectangleShape paddles[2];

void Reset() {
	ball.setPosition(Vector2f(gameWidth / 2, gameHeight / 2));
	ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };

	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition(gameWidth - paddleSize.x / 2, gameHeight / 2);

	// Update Score Text
	text.setString("test");
	// Keep Score Text Centered
	text.setPosition((gameWidth * .5f) - (text.getLocalBounds().width * .5f), 50);
	std::cout << text.getPosition().x << " " << text.getPosition().y << "\n" ;

}

void Load() {
	for (auto &p : paddles) {
		p.setSize(paddleSize - Vector2f(3, 3));
		p.setOrigin(paddleSize / 2.f);
	}

	ball.setRadius(ballRadius - 3);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);

	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition(gameWidth - paddleSize.x / 2, gameHeight / 2);

	ball.setPosition(Vector2f(gameWidth / 2, gameHeight / 2));
	ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };

	// Load font-face from res dir
	font.loadFromFile("res/fonts/PressStart2P-Regular.ttf");
	// Set text element to use font
	text.setFont(font);
	text.setColor(white);
	// set the character size to 24 pixels
	text.setCharacterSize(24);
}

void Update(RenderWindow& window) {
	static Clock clock;
	float dt = clock.restart().asSeconds();

	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	float direction1 = 0.0f;
	float direction2 = 0.0f;
	if (Keyboard::isKeyPressed(controls[0])) {
		direction1--;
	}
	if (Keyboard::isKeyPressed(controls[1])) {
		direction1++;
	}	

	if (twoPlayer)	{
		if (Keyboard::isKeyPressed(controls[2])) {
			direction2--;
		}
		if (Keyboard::isKeyPressed(controls[3])) {
			direction2++;
		}
	}
	else{
		if (paddles[1].getPosition().y < ball.getPosition().y)
		{
			direction2++;
		}
		if (paddles[1].getPosition().y > ball.getPosition().y)
		{
			direction2--;
		}
	}


	if(paddles[0].getPosition().y > gameHeight) {
		paddles[0].setPosition(Vector2f(paddles[0].getPosition().x, paddles[0].getPosition().y - 20.f));
	}	
	if(paddles[0].getPosition().y < 0) {
		paddles[0].setPosition(Vector2f(paddles[0].getPosition().x, paddles[0].getPosition().y + 20.f));
	}	
	if(paddles[1].getPosition().y > gameHeight) {
		paddles[1].setPosition(Vector2f(paddles[1].getPosition().x, paddles[1].getPosition().y - 20.f));
	}	
	if(paddles[1].getPosition().y < 0) {
		paddles[1].setPosition(Vector2f(paddles[1].getPosition().x, paddles[1].getPosition().y + 20.f));
	}

	paddles[0].move(0, direction1 * paddleSpeed * dt);
	paddles[1].move(0, direction2 * paddleSpeed * dt);


	ball.move(ballVelocity * dt);
	// check ball collision
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;
	if (by > gameHeight) { //bottom wall
	  // bottom wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, -10);
	}
	else if (by < 0) { //top wall
   // top wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, 10);
	}	
	else if (bx > gameWidth) {
		// right wall
		Reset();
		server = false;
	}else if (bx < 0) {
		// left wall
		Reset();
		server = true;
	}
	else if (
		//ball is inline or behind paddle
		bx < paddleSize.x &&
		//AND ball is below top edge of paddle
		by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
		//AND ball is above bottom edge of paddle
		by < paddles[0].getPosition().y + (paddleSize.y * 0.5)
		) {
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(10, 0);
	}
	else if (bx >  gameWidth - paddleSize.x &&
		//AND ball is below top edge of paddle
		by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&
		//AND ball is above bottom edge of paddle
		by < paddles[1].getPosition().y + (paddleSize.y * 0.5)) {
		// bounce off right paddle
		//std::cout << "score";
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(-10, 0);
	}
}

void Render(RenderWindow& window) {
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
}



int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}



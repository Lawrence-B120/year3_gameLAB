#include "pacman.h"
#include "system_renderer.h"
#include "player.h"
#include "ghost.h"
#include "ecm.h"
#include "cmp_sprite.h"
#include "cmp_actor_movement.h"
#include "LevelSystem.h"

#define GHOSTS_COUNT 4

using namespace sf;
using namespace std;

std::shared_ptr<Scene> gameScene;
std::shared_ptr<Scene> menuScene;
std::shared_ptr<Scene> activeScene;

std::shared_ptr<Entity> player;
std::vector<std::shared_ptr<Entity>> ghost_list;

sf::Font font;
sf::Color white = Color(255, 255, 255, 255);

sf::RenderWindow window;
void Scene::render() { _ents.render(/*window*/); }

void Scene::update(double dt) {
	for (int i = 0; i < _ents.list.size(); i++) {
		_ents.list[i]->Update(dt);
	}
}

void MenuScene::update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		activeScene = gameScene;
	}
	Scene::update(dt);
	text.setString("Almost Pacman");
}

void MenuScene::render() {
	Renderer::queue(&text);
	Scene::render();
}

void MenuScene::load() {
	// Load font-face from res dir
	font.loadFromFile("res/fonts/PressStart2P-Regular.ttf");
	// Set text element to use font
	text.setFont(font);
	text.setColor(white);
	// set the character size to 24 pixels
	text.setCharacterSize(24);
}

void GameScene::respawn() {
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	player->GetCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(150.f);

	auto ghost_spawns = ls::findTiles(ls::ENEMY);
	for (auto& g : ghost_list) {
		g->setPosition(ls::getTilePosition(ghost_spawns[rand() % ghost_spawns.size()]));
		g->GetCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(100.0f);
	}
		
}

void GameScene::update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}
	Scene::update(dt);
}

void GameScene::render() {
	//for (int i = 0; i < 5; i++)
	//{
	//	//Renderer::queue(_ents.list[i]->getShape());
	//	Renderer::queue(_ents.list[i]->render());
	//}
	for (int i = 0; i < 5; i++)
	{
		_ents.list[i]->Render();
	}

	ls::Render(Renderer::getWindow());
}

//void GameScene::load() {
//	Player* player = new Player();
//	shared_ptr<Player> play = shared_ptr<Player>(player);
//	_ents.list.push_back(play);
//
//	for (int i = 0; i < 4; i++)
//	{
//		Ghost* gho = new Ghost();
//		shared_ptr<Ghost> lul = shared_ptr<Ghost>(gho);
//
//		_ents.list.push_back(lul);
//	}
//}

void GameScene::load() {
	
	auto pl = make_shared<Entity>();

	auto s = pl->addComponent<ShapeComponent>();
	pl->addComponent<PlayerMovementComponent>();
	s->setShape<sf::CircleShape>(12.f);
	s->getShape().setFillColor(Color::Yellow);
	s->getShape().setOrigin(Vector2f(12.f, 12.f));

	_ents.list.push_back(pl);
	player = _ents.list[0];

	const sf::Color ghost_cols[]{ {208, 62, 25},    // red Blinky
							   {219, 133, 28},   // orange Clyde
							   {70, 191, 238},   // cyan Inky
							   {234, 130, 229} }; // pink Pinky

	for (int i = 0; i < GHOSTS_COUNT; ++i) {
		auto ghost = make_shared<Entity>();
		auto s = ghost->addComponent<ShapeComponent>();
		ghost->addComponent<EnemyAIComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(ghost_cols[i % 4]);
		s->getShape().setOrigin(Vector2f(12.f, 12.f));

		_ents.list.push_back(ghost);
		ghost_list.push_back(_ents.list[i + 1]);		
		
	}


	//load level
	ls::loadLevelFile("res/pacman.txt", 25.0f);
	respawn();
}
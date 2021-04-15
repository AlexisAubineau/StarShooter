#include "GameState.h"

//Initializer Functions
void GameState::initKeybinds()
{
	std::ifstream ifs(config->gameStateKeybindingPath);

	if (ifs.is_open()) {
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2) {
			keybinds[key] = supportedKeys->at(key2);
		}
	}
	ifs.close();
}

void GameState::initTextures()
{
}

void GameState::initPlayers()
{
	player = new Player(0, 0);
}

//Constructors / Destructors
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	initKeybinds();
	initTextures();
	initPlayers();
}

GameState::~GameState()
{
	delete player;
}

void GameState::updateInput(const float& dt)
{
	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT"))))
		player->move(-25.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT"))))
		player->move(25.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP"))))
		player->move(0.f, -25.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
		player->move(0.f, 25.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("SHOOT"))))
		player->attack();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))))
		endState();
}

void GameState::update(const float& dt)
{
	update_mouse_position();
	updateInput(dt);
	player->update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;
	player->render(target);
	player->projectileComponent->DrawAll(target);
}
 
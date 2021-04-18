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

void GameState::initTextures(){}

void GameState::initPlayers()
{
	player = new Player(20, 540);
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
	player->supportedKeys = supportedKeys;
	player->keybinds = keybinds;
	player->window = window;
	
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
}
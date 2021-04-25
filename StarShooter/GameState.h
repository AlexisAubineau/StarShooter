#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <fstream>
#include "Bullet.h"
#include "EnemySpawnerComponent.h"
#include "Player.h"
#include "State.h"
#include "PauseMenu.h"

class Entity;

class GameState :
	public State
{
private:
	//Variables
	Player* player;
	EnemySpawnerComponent* EnemyType1Spawner;
	PauseMenu* pause_menu;

	sf::Font font;

	//Functions
	void initKeybinds();
	void initTextures();
	void initPlayers();
	void initEnemies(sf::RenderWindow* window);
	void initFonts();
	void initPauseMenu();

public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	//Functions
	void updateInput(const float& dt);
	void updatePauseMenuButtons();
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};

#endif


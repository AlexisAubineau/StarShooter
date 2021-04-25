#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <fstream>
#include "Bullet.h"
#include "EnemySpawnerComponent.h"
#include "Player.h"
#include "State.h"

class Entity;

class GameState :
	public State
{
private:
	//Variables
	Player* player;
	EnemyMaster* enemy;
	Bullet* bullet;
	EnemySpawnerComponent* EnemyType1Spawner; 

	//Functions
	void initKeybinds();
	void initTextures();
	void initPlayers();
	void initEnemies(sf::RenderWindow* window);

public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	//Functions
	void updateInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};

#endif


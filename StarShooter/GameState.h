#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Config.h"

class GameState :
	public State
{
private:
	//Variables
	Player* player;
	std::string playerIdlePath = playerIdlePathGv;
	std::string gameStateKeybindingPath = gameStateKeybindingPathGv;

	//Functions
	void initKeybinds();
	void initTextures();
	void initPlayers();

public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	//Functions
	void updateInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};

#endif


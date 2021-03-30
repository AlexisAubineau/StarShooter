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

	//Functions
	void initKeybinds();
	void initTextures();
	void initPlayers();

	Config* config = new Config;;

public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	//Functions
	void updateInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};

#endif


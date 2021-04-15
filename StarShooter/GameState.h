#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <fstream>


#include "Bullet.h"
#include "State.h"
#include "PlayerGUI.h"

class GameState :
	public State
{
private:
	//Variables
	Player* player;
	Bullet* bullet;
	PlayerGUI* player_gui;

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


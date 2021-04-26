#ifndef GAME_H
#define GAME_H
#include<vector>
#include<stack>
#include<map>
#include <iostream>
#include <fstream>
#include <string>

#include "MainMenuState.h"
#include "Config.h"
#include "GraphicsSettings.h"
#include "State.h"

class Game
{
private:
	//Variables
	Config* config = new Config;
	GraphicsSettings gfxSettings;
	sf::RenderWindow *window;
	sf::Event sfEvent;

	sf::Clock dtClock; 
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;
	
	//Initialization
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStates();
	
public:

	//Contructors/Deconstructors
	Game();
	virtual ~Game();

	//Functions

	//Regular
	void endApplication();

	//Updates
	void updateDt();
	void updateSFMLEvents();
	void update();

	//Render
	void render();

	//Core
	void run();
};
#endif
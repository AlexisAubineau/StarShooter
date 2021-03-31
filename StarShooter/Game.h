#ifndef GAME_H
#define GAME_H

#include "Config.h"
#include "MainMenuState.h"
 
class Game
{
private:
	//Variables 
	sf::RenderWindow *window;
	sf::Event sfEvent;

	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;

	sf::Clock dtClock; 
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	Config* config = new Config;
	
	//Initialization
	void initVariables();
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
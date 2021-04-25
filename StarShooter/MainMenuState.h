#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <iostream>
#include <fstream>

#include "GameState.h"
#include "SettingsState.h"
#include "State.h"
#include "Gui.h"
#include "SettingsState.h"

class MainMenuState :
	public State
{
private:
	//variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();

public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();

	//Functions
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget* target = NULL);
	void render(sf::RenderTarget* target = NULL);
};

#endif

#pragma once
#include "State.h"

class SettingsState:
	public State
{
public:
	SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~SettingsState();

	//Functions
	void initKeybinds();
	void initTextures();

private:

	//Functions
	void update(const float& dt);
	void updateInput(const float& dt){};
	void render(sf::RenderTarget* target = NULL);
};


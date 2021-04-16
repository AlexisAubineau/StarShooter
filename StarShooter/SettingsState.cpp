#include "SettingsState.h"

SettingsState::SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,
	std::stack<State*>* states): State(window, supportedKeys, states)
{
	initKeybinds();
	initTextures();
}

SettingsState::~SettingsState()
{
}

void SettingsState::initKeybinds()
{
}

void SettingsState::initTextures()
{
}

void SettingsState::update(const float& dt)
{
}

void SettingsState::render(sf::RenderTarget* target)
{
}

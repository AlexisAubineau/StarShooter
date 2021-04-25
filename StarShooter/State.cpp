#include "State.h"

#include <iostream>

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
{
	this->window = window;
	this->supportedKeys = supportedKeys;
	this->states = states;
	quit = false;
	paused = false;
	keytime = 0.f;
	keytimeMax = 10.f;
}

State::~State()
{
	delete config;
}

//Accessors
const bool& State::getQuit() const
{
	return quit;
}

const bool State::getKeytime()
{
	if (keytime >= keytimeMax)
	{
		keytime = 0.f;
		return true;
	}
	return false;
}

//Functions
void State::endState()
{
	quit = true;
}

void State::pauseState()
{
	paused = true;
}

void State::resumeState()
{
	paused = false;
}

void State::update_mouse_position()
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}

void State::update_keytime(const float& dt)
{
	std::cout << keytime << std::endl;
	if (keytime < keytimeMax)
		keytime += 50.f * dt;
}


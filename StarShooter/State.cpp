#include "State.h"

#include <iostream>

#include "GameState.h"

State::State(StateData* state_data)
{
	//Initializer State
	stateData = state_data;
	window = state_data->window;
	supportedKeys = state_data->supportedKeys;
	states = state_data->states;
	quit = false;
	paused = false;
	keytime = 0.f;
	keytimeMax = 10.f;
	ratio = static_cast<float>(window->getSize().x) / static_cast<float>(window->getSize().y);
	gridSize = state_data->gridSize;
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

void State::update_mouse_position(sf::View* view)
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(*window);

	if(view)
		window->setView(*view);
	
	mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	mousePosGrid = 
		sf::Vector2u(
			static_cast<unsigned>(mousePosView.x) / static_cast<unsigned>(gridSize),
			static_cast<unsigned>(mousePosView.y) / static_cast<unsigned>(gridSize)
		);

	window->setView(window->getDefaultView());
}

void State::update_keytime(const float& dt)
{
	if (keytime < keytimeMax)
		keytime += 50.f * dt;
}


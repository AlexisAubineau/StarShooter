#pragma once
#include <map>
#include "Config.h"

class Player;

class InputComponent
{
public:
	InputComponent() = default;
	~InputComponent() = default;

	//Functions
	void updateInput(const float& dt, Player* player, std::map<std::string, int> keybinds, std::map<std::string, int>* supportedKeys);
};


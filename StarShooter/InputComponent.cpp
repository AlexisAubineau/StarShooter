#include "InputComponent.h"
#include "Player.h"

void InputComponent::updateInput(const float& dt, Player* player, std::map<std::string, int> keybinds,
	std::map<std::string, int>* supportedKeys, bool locationAllowed)
{
	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT"))) && locationAllowed) //g
		player->move(-25.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT"))) && locationAllowed) //d
		player->move(25.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP"))) && locationAllowed)
		player->move(0.f, -25.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))) && locationAllowed)
		player->move(0.f, 25.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("SHOOT"))))
		player->attack();
}

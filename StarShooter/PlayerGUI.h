#ifndef PLAYERGUI_H
#define PLAYERGUI_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


#include "Config.h"


class Player;

class PlayerGUI
{
private:
	Player* player;

	Config* config = new Config;

	sf::Font font;
	sf::RectangleShape hpBarBack;
	sf::RectangleShape hpBarInner;

	void initFont();
	void initHPBar();

public:
	PlayerGUI(Player* m_player);
	virtual ~PlayerGUI();

	//Function
	void updateHpBar();
	void update(const float& dt);

	void renderHPBar(sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};
#endif //PLAYERGUI_H

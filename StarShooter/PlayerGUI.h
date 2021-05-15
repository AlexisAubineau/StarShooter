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
	
	//Functions
	void initFont();
	void initHPBar();

	//Variables
	float height_back = 25.f;
	float width_back = 205.f;

	float x_back = 20.f;
	float y_back = 20.f;
	
	float height_inner = 20.f;
	float width_inner = 200.f;
	
	float x_inner = x_back + 2.5f;
	float y_inner = y_back + 1.5f;

	float hpBarMaxWidth = 200.f;
	float hpBarMinWidth = 0.f;

	sf::Font font;
	sf::RectangleShape hpBarBack;
	sf::RectangleShape hpBarInner;

public:
	PlayerGUI(Player* m_player);
	virtual ~PlayerGUI();

	//Function
	void updateHpBar();
	void update(const float& dt);

	void renderHPBar(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};
#endif //PLAYERGUI_H

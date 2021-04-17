#include "PlayerGUI.h"
#include "Player.h"

void PlayerGUI::initFont()
{
	font.loadFromFile(config->fontPath);
}

void PlayerGUI::initHPBar()
{
	hpBarBack.setSize(sf::Vector2f(width_back, height_back));
	hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	hpBarBack.setPosition(x_back, y_back);
	
	hpBarInner.setSize(sf::Vector2f(width_inner, height_inner));
	hpBarInner.setFillColor(sf::Color(20, 250, 20, 200));
	hpBarInner.setPosition(x_inner, y_inner);
}

PlayerGUI::PlayerGUI(Player* m_player)
{
	player = m_player;

	initFont();
	initHPBar();
}

PlayerGUI::~PlayerGUI()
{
}

// Functions
void PlayerGUI::updateHpBar()
{
	float percent = player->current_life / player->max_life;

	if (hpBarInner.getSize().x > hpBarMinWidth)
	{
		hpBarInner.setSize(sf::Vector2f(static_cast<float>(std::floor(hpBarMaxWidth * percent)), hpBarInner.getSize().y));
	}
}

void PlayerGUI::update(const float& dt)
{
	updateHpBar();
}

void PlayerGUI::renderHPBar(sf::RenderTarget* target)
{
	target->draw(hpBarBack);
	target->draw(hpBarInner);
}

void PlayerGUI::render(sf::RenderTarget* target)
{
	renderHPBar(target);
}

#include "PlayerGUI.h"

#include "Player.h"

void PlayerGUI::initFont()
{
	font.loadFromFile(config->fontPath);
}

void PlayerGUI::initHPBar()
{
	hpBarBack.setSize(sf::Vector2f(205.f, 25.f));
	hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	hpBarBack.setPosition(20.f, 20.f);
	
	hpBarInner.setSize(sf::Vector2f(player->health, 20.f));
	hpBarInner.setFillColor(sf::Color(20, 250, 20, 200));
	hpBarInner.setPosition(hpBarBack.getPosition().x + 2.5f, hpBarBack.getPosition().y + 1.5f);
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
	
}

void PlayerGUI::update(const float& dt)
{
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

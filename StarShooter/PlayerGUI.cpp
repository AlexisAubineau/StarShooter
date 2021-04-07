#include "PlayerGUI.h"

void PlayerGUI::initFont()
{
	font.loadFromFile(config->fontPath);
}

void PlayerGUI::initHPBar()
{
	hpBarBack.setSize(sf::Vector2f(100.f, 20.f));
	hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	hpBarBack.setPosition(20.f, 20.f);
	
	hpBarInner.setSize(sf::Vector2f(100.f, 20.f));
	hpBarInner.setFillColor(sf::Color(20, 250, 20, 200));
	hpBarInner.setPosition(hpBarBack.getPosition());
}

PlayerGUI::PlayerGUI(Player* player)
{
	this->player = player;

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

void PlayerGUI::renderHPBar(sf::RenderTarget& target)
{
	target.draw(hpBarBack);
	target.draw(hpBarInner);
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	renderHPBar(target);
}

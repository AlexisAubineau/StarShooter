#include "Player_projectile.h"

void Player_projectile::initVariables()
{
}

void Player_projectile::initComponents()
{
}

Player_projectile::Player_projectile(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("SHIP_PROJECTILE", 10.f, 0, 0, 4, 0, 120, 90);
}

Player_projectile::~Player_projectile()
{
	
}

void Player_projectile::update(const float& dt)
{
	this->move(m_projectile_speed,0,dt);
	this->animationComponent->play("SHIP_PROJECTILE",dt);
}

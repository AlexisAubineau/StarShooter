#include "ProjectileComponent.h"

void ProjectileComponent::initVariables()
{
}

void ProjectileComponent::initComponents()
{
}

ProjectileComponent::ProjectileComponent(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("SHIP_PROJECTILE", 10.f, 0, 0, 4, 0, 120, 90);
}

ProjectileComponent::~ProjectileComponent()
{
	
}

void ProjectileComponent::update(const float& dt)
{
	this->move(m_projectile_speed,0,dt);
	this->animationComponent->play("SHIP_PROJECTILE",dt);
}

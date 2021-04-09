#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
	delete component;
	delete config;
}

//Component functions
void Entity::setTexture(sf::Texture& texture)
{
	component->sprite.setTexture(texture);
}

//Functions
void Entity::setPosition(const float x, const float y)
{
	component->sprite.setPosition(x, y);
}

float Entity::Life(float life)
{
	return life;
}

void Entity::update(const float& dt)
{
}

void Entity::render(sf::RenderTarget* target)
{
	 target->draw(component->sprite);
}
 
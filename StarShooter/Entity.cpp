#include "Entity.h"

Entity::Entity()
{
	window = nullptr;
	movement_component = nullptr;
	hitbox_component = nullptr;
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

void Entity::setHitbox(HitboxComponent* hitbox)
{
	hitbox_component = hitbox;
}

void Entity::setMovement(MovementComponent* movement)
{
	movement_component = movement;
}

// Accessors

const sf::Vector2f& Entity::getPosition() const
{
	if (hitbox_component)
		return hitbox_component->getPosition();

	return component->sprite.getPosition();
}

const sf::Vector2u Entity::getGridPosition(const int gridSizeI) const
{
	if (hitbox_component)
		return sf::Vector2u(
			static_cast<int>(hitbox_component->getPosition().x) / gridSizeI,
			static_cast<int>(hitbox_component->getPosition().y) / gridSizeI
		);

	return sf::Vector2u(
		static_cast<int>(component->sprite.getPosition().x) / gridSizeI,
		static_cast<int>(component->sprite.getPosition().y) / gridSizeI
	);
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (hitbox_component)
		return hitbox_component->getGlobalBounds();
	return component->sprite.getGlobalBounds();
}

const sf::FloatRect& Entity::getNextPositionBounds(const float& dt) const
{
	if(hitbox_component && movement_component)
		return hitbox_component->getNextPosition(movement_component->getVelocity() * dt);
	return sf::FloatRect();
}

//Functions
void Entity::setPosition(const float x, const float y)
{
	if (hitbox_component)
		hitbox_component->setPosition(x, y);
	else
		component->sprite.setPosition(x, y);
}

float Entity::Life(float life)
{
	return life;
}

float Entity::maxLife(float maxLife)
{
	return maxLife;
}

void Entity::stopVelocity()
{
	if (movement_component)
		movement_component->stopVelocity();
}

void Entity::stopVelocityX()
{
	if (movement_component)
		movement_component->stopVelocityX();
}

void Entity::stopVelocityY()
{
	if (movement_component)
		movement_component->stopVelocityY();
}

void Entity::update(const float& dt)
{
}

void Entity::render(sf::RenderTarget& target)
{
	 target.draw(component->sprite);
}
 
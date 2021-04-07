#include "Component.h"

MovementComponent* Component::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	auto *const movementComponent = new MovementComponent(sprite, maxVelocity, acceleration, deceleration);
	return movementComponent;
}

AnimationComponent* Component::createAnimationComponent(sf::Texture& texture_sheet)
{
	auto *const animationComponent = new AnimationComponent(sprite, texture_sheet);
	return animationComponent;
}

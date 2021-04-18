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

ProjectileComponent* Component::createProjectileComponent(std::string textureName, std::string animationKey,std::string texturePathName,
	float timer, int startFrameX, int startFrameY, int frameX, int frameY, int width, int height, float velocity,
	float damage, float delay)
{
	auto* const projectileComponent = new ProjectileComponent(textureName,
		animationKey,
		texturePathName,
		timer,
		startFrameX,
		startFrameY,
		frameX,
		frameY,
		width,
		height,
		velocity,
		damage,
		delay);
	return projectileComponent;
}

InputComponent* Component::createInputComponent()
{
	auto* const inputComponent = new InputComponent();
	return inputComponent;
}

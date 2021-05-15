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

HitboxComponent* Component::createHitboxComponent(sf::Sprite& sprite, const float offset_x, const float offset_y, const float width, const float height, const bool isDebug)
{
	auto* const hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height, isDebug);
	return hitboxComponent;
}

EnemySpawnerComponent* Component::createEnemySpawnerComponent(std::string textureName, std::string animationKey,
	std::string texturePathName, float timer, int startFrameX, int startFrameY, int frameX, int frameY, int width,
	int height, float velocity, float damage, float life, float accel)
{
	auto* const enemySpawnerComponent = new EnemySpawnerComponent(textureName,
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
		life,
		accel);
	return  enemySpawnerComponent;
}

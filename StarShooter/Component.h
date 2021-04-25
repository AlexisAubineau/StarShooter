#ifndef COMPONENT_H
#define COMPONENT_H

#include "AnimationComponent.h"
#include "EnemySpawnerComponent.h"
#include "InputComponent.h"
#include "MovementComponent.h"
#include "HitboxComponent.h"
#include "ProjectileComponent.h"

class Component
{
	
public:
	std::map<std::string, sf::Texture> textures;
	sf::Sprite sprite;
	
	MovementComponent* createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	AnimationComponent* createAnimationComponent(sf::Texture& texture_sheet);
	ProjectileComponent* createProjectileComponent(std::string textureName,
		std::string animationKey,
		std::string texturePathName,
		float timer,
		int startFrameX,
		int startFrameY,
		int frameX,
		int frameY,
		int width,
		int height,
		float velocity,
		float damage,
		float delay);
	InputComponent* createInputComponent();
	HitboxComponent* createHitboxComponent(sf::Sprite& sprite, const float offset_x, const float offset_y, const float width, const float height, const bool isDebug);	EnemySpawnerComponent* createEnemySpawnerComponent(std::string textureName,
		std::string animationKey,
		std::string texturePathName,
		float timer,
		int startFrameX,
		int startFrameY,
		int frameX,
		int frameY,
		int width,
		int height,
		float velocity,
		float damage,
		float life,
		float accel);
};
#endif // COMPONENT_H
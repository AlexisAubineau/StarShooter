#ifndef COMPONENT_H
#define COMPONENT_H

#include "AnimationComponent.h"
#include "MovementComponent.h"
#include "ProjectileComponent.h"

class Component
{
	
public:
	std::map<std::string, sf::Texture> textures;
	sf::Sprite sprite;
	
	MovementComponent* createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	AnimationComponent* createAnimationComponent(sf::Texture& texture_sheet);
};
#endif // COMPONENT_H
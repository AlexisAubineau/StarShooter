#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include <SFML/Graphics/Sprite.hpp>

class MovementComponent
{
private:
	sf::Sprite& sprite;
	
	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;

	//Initializer functions

public:
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Accessors
	const sf::Vector2f& getVelocity() const;

	//Functions
	void move(const float x, const float y, const float& dt);
	void update(const float& dt);
};
 
#endif // !MOVEMENTCOMPONENT_H
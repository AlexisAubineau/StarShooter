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

	//Initializer functions

public:

	//Variables
	float m_dir_x = 0.f;
	float m_dir_y = 0.f;
	sf::Vector2f velocity;
	
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Accessors
	const sf::Vector2f& getVelocity() const;

	//Functions
	void move(const float x, const float y, const float& dt);
	void update(const float& dt);
};
 
#endif // !MOVEMENTCOMPONENT_H
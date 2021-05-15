#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include <SFML/Graphics.hpp>

enum movement_states { IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };

class MovementComponent
{
private:
	//Variables
	sf::Vector2f velocity;
	sf::Sprite& sprite;
	
	float maxVelocity;
	float acceleration;
	float deceleration;

	//Initializer functions

public:
	
	MovementComponent(sf::Sprite& sprite,
		float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Accessors
	const float& getMaxVelocity() const;
	const sf::Vector2f& getVelocity();

	//Functions
	const bool getState(const short unsigned state) const;
	void stopVelocity();
	void stopVelocityX();
	void stopVelocityY();

	void move(const float x, const float y, const float& dt);
	void update(const float& dt);
};
 
#endif // !MOVEMENTCOMPONENT_H
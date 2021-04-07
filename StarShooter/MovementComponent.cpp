#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, 
	float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite),
	maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
	this->maxVelocity = maxVelocity;
}

MovementComponent::~MovementComponent()
{

}

//Accesors
const sf::Vector2f& MovementComponent::getVelocity() const
{
	return velocity;
}

//Functions
void MovementComponent::move(const float dir_x, const float dir_y, const float&  dt)
{
	/* Accelerate a sprite until ir reaches the maxVelocity */

	velocity.x += acceleration * dir_x;
	velocity.y += acceleration * dir_y;
}


void MovementComponent::update(const float& dt)
{
	/*
		Decelerates the sprite and controls the maximum velocity.
		Move the sprite.
	*/
	
	if (velocity.x > 0.f) //Check for positive x 
	{
		//Max Velocity check 
		if (velocity.x > maxVelocity)
			velocity.x = maxVelocity;

		//Deceleration
		velocity.x -= deceleration;
		if (velocity.x < 0.f)
			velocity.x = 0.f;
	}
	else if (velocity.x < 0.f) //Check for negative x 
	{
		//Max velocity check
		if (velocity.x < -maxVelocity)
			velocity.x = -maxVelocity;
		
		//Deceleration
		velocity.x += deceleration;
		if (velocity.x > 0.f)
			velocity.x = 0.f;
	}
	if (velocity.y > 0.f) //Check for positive y 
	{
		//Max Velocity check
		if (velocity.y > maxVelocity)
			velocity.y = maxVelocity;

		//Deceleration
		velocity.y -= deceleration;
		if (velocity.y < 0.f)
			velocity.y = 0.f;
	}
	else if (velocity.y < 0.f) //Check for negative y 
	{
		//Max velocity check
		if (velocity.y < -maxVelocity)
			velocity.y = -maxVelocity;

		//Deceleration
		velocity.y += deceleration;
		if (velocity.y > 0.f)
			velocity.y = 0.f;
	}
	
	//Final move
	sprite.move(velocity * dt); //Uses velocity
}
 
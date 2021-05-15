#include "MovementComponent.h"

#include <iostream>

MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite),
	maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
	this->maxVelocity = maxVelocity;
}

MovementComponent::~MovementComponent()
{
	
}

const float& MovementComponent::getMaxVelocity() const
{
	return maxVelocity;
}

const sf::Vector2f& MovementComponent::getVelocity()
{
	return velocity;
}

//Functions
const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:

		if (velocity.x == 0.f && velocity.y == 0.f)
			return true;

		break;

	case MOVING:

		if (velocity.x != 0.f || velocity.y != 0.f)
			return true;

		break;

	case MOVING_LEFT:

		if (velocity.x < 0.f)
			return true;

		break;

	case MOVING_RIGHT:

		if (velocity.x > 0.f)
			return true;

		break;

	case MOVING_UP:

		if (velocity.y < 0.f)
			return true;

		break;

	case MOVING_DOWN:

		if (velocity.y > 0.f)
			return true;

		break;
	}

	return false;
}

void MovementComponent::stopVelocity()
{
	/* Reset Velocity */

	velocity.x = 0;
	velocity.y = 0;
}

void MovementComponent::stopVelocityX()
{
	velocity.x = 0;
}

void MovementComponent::stopVelocityY()
{
	velocity.y = 0;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	/* Accelerating a sprite until it reaches the max velocity. */

	velocity.x += acceleration * dir_x;
	velocity.y += acceleration * dir_y;
}

void MovementComponent::update(const float& dt)
{
	/*
	Decelerates the sprite and controls the maximum velocity.
	Moves the sprite.
	*/

	if (velocity.x > 0.f) //Check for positive x
	{
		//Max velocity check
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
		//Max velocity check
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
 
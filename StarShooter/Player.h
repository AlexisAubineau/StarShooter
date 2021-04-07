#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include "Entity.h"

class Player :
	public Entity
{
private:
	//Variables

	//Initializer functions
	void initVariables();
	void initComponents();
	void initTexture();

	//Initializer Components
	AnimationComponent* animationComponent;
	MovementComponent* movementComponent;

protected:

public:
	Player(float x, float y);
	virtual ~Player();

	//Functions
	void move(const float dir_x, const float dir_y, const float& dt);
	void setLifePlayer();
	float getLifePlayer();
	void PlayerShoot();
	virtual void update(const float& dt);
};

#endif
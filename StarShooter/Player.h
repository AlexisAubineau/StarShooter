#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <fstream>
#include "Entity.h"

class Player :
	public Entity
{
private:
	//Variables
	float health = 100.f;
	float shoot_delay = .5f;

	//Initializer functions
	void initVariables();
	void initComponents();
	void initTexture();

protected:
	//Initializer Components
	AnimationComponent* animationComponent;
	MovementComponent* movementComponent;

public:
	Player(float x, float y);
	virtual ~Player();
	ProjectileComponent* projectileComponent;
	//Functions
	void move(const float dir_x, const float dir_y, const float& dt);
	void attack();
	virtual void update(const float& dt);
	void updateInput(const float& dt);
};

#endif
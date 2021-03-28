#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Player_projectile.h"

class Player :
	public Entity
{
private:
	//Variables

	//Initializer functions
	void initVariables();
	void initComponents();

public:
	Player(float x, float y, sf::Texture& texture_sheet);
	virtual ~Player();

	//Functions

	void PlayerShoot();
	virtual void update(const float& dt);
};

#endif
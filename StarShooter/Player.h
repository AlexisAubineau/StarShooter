#ifndef PLAYER_H
#define PLAYER_H

#include "Config.h"
#include "Entity.h"
#include "ProjectileComponent.h"

class Player :
	public Entity
{
private:
	//Variables

	//Initializer functions
	void initVariables();
	void initComponents();
	void initTexture();

	Config* config = new Config;

protected:

public:
	Player(float x, float y);
	virtual ~Player();

	//Functions

	void setLifePlayer();
	float getLifePlayer();
	void PlayerShoot();
	virtual void update(const float& dt);

	std::map<std::string, sf::Texture> textures;
};

#endif
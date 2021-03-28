#ifndef PLAYER_PROJECTICLE
#define PLAYER_PROJECTILE

#include "Entity.h"

class Player_projectile :
    public Entity
{
private:
		//Variables

	//Initializer functions
	void initVariables();
	void initComponents();

public:
	Player_projectile(float x, float y, sf::Texture& texture_sheet);
	virtual ~Player_projectile();
	float m_projectile_speed = 20.0f;

	virtual void update(const float& dt);
};

#endif



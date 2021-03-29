#ifndef PLAYER_PROJECTICLE
#define PLAYER_PROJECTILE

#include "Entity.h"

class ProjectileComponent :
    public Entity
{
private:
		//Variables

	//Initializer functions
	void initVariables();
	void initComponents();

public:
	ProjectileComponent(float x, float y, sf::Texture& texture_sheet);
	virtual ~ProjectileComponent();
	float m_projectile_speed = 20.0f;

	virtual void update(const float& dt);
};

#endif



#ifndef ENEMYMASTER_H
#define ENEMYMASTER_H
#include "Entity.h"

class Entity;

class EnemyMaster :
	public Entity
{
private:
	

protected:
	AnimationComponent* animationComponent;
	MovementComponent* movementComponent;
	ProjectileComponent* projectileComponent;
	HitboxComponent* hitboxComponent;

public:
	EnemyMaster(float m_posx, float m_posy);
	virtual ~EnemyMaster();
	
	//Variables
	float m_shoot_delay = .5f;
	float m_life = 5.f;
	float m_damage = 1.0f;
	float m_velocity = 100.f;
	float m_accel = 5.f;
	
	sf::RenderWindow* window;

	//functions
	void move(const float& dt);
	void attack();

	virtual void update(const float& dt, std::string m_animationKey);
	virtual void render(sf::RenderTarget& target);
	
	//Initalizers
	void initVariables();
	void initComponents();
	void initTexture(std::string m_textureName, std::string m_pathname);
	void setAnimation(std::string m_animationKey,
		float m_timer,
		int m_startFrameX,
		int m_startFrameY,
		int m_frameX,
		int m_frameY,
		int m_width,
		int m_height);
};

#endif
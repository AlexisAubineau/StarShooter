#ifndef BULLET_H
#define BULLET_H
#include "Entity.h"

class Bullet :
	public Entity
{
private:
	//initializers
	void initComponents();

protected:
	//Components
	AnimationComponent* animationComponent;
	MovementComponent* movementComponent;

public:

	Bullet(float m_posx, float m_posy);
	virtual ~Bullet();

	//Variables
	float m_velocity = 10.f;
	float m_damage = 1.0f;


	//Functions
	virtual void Movement(const float& dt);
	virtual void update(const float& dt, std::string m_animationKey);
	virtual void render(sf::RenderTarget* target);

	void initTexture(std::string m_textureName);
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


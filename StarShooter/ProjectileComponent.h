#ifndef PROJECTILE_COMPONENT_H
#define PROJECTILE_COMPONENT_H

#include <list>

#include "Bullet.h"

class ProjectileComponent
{
private:
	std::list<Bullet*> m_BulletList;
	std::string m_textureName;
	std::string m_animationKey;
	float m_timer;
	int m_startFrameX;
	int m_startFrameY;
	int m_frameX;
	int m_frameY;
	int m_width;
	int m_height;
	float m_velocity;
	float m_damage;
public:
	ProjectileComponent(std::string textureName, 
						std::string animationKey,
						float timer,
						int startFrameX,
						int startFrameY,
						int frameX, 
						int frameY,
						int width,
						int height,
						float velocity,
						float damage);
	virtual ~ProjectileComponent();

	void FireProjectile();
	void update(const float& dt);
};


#endif

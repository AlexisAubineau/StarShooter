#include "ProjectileComponent.h"

#include <iostream>

#include "Bullet.h"


ProjectileComponent::ProjectileComponent(std::string textureName, std::string animationKey, float timer,
                                         int startFrameX, int startFrameY, int frameX, int frameY, int width, int height, float velocity, float damage)
{
	m_textureName = textureName;
	m_animationKey = animationKey;
	m_timer = timer;
	m_startFrameX = startFrameX;
	m_startFrameY = startFrameY;
	m_frameX = frameX;
	m_frameY = frameY;
	m_width = width;
	m_height = height;
	m_velocity = velocity;
	m_damage = damage;
}

ProjectileComponent::~ProjectileComponent()
{
}

void ProjectileComponent::FireProjectile(float x, float y)
{
	Bullet* bullet = new Bullet(x, y);
	//std::list<Bullet*> m_BulletList;
	bullet->m_damage = m_damage;
	bullet->m_velocity = m_velocity;
	bullet->initTexture(m_textureName);
	bullet->setAnimation(m_animationKey, m_timer, m_startFrameX, m_startFrameY, m_frameX, m_frameY, m_width, m_height);
	m_BulletList.push_back(bullet);
}

void ProjectileComponent::update(const float& dt)
{
	for (Bullet* element : m_BulletList)
	{
		element->update(dt,m_animationKey);
	}
}

void ProjectileComponent::DrawAll(sf::RenderTarget* target)
{
	for (Bullet* element : m_BulletList)
	{
		element->render(target);
	}
}

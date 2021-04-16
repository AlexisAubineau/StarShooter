#include "ProjectileComponent.h"
#include "Bullet.h"

ProjectileComponent::ProjectileComponent(std::string textureName, std::string animationKey, float timer,
                                         int startFrameX, int startFrameY, int frameX, int frameY, int width, int height, float velocity, float damage, float delay)
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
	m_delay = delay;
}

ProjectileComponent::~ProjectileComponent()
{
}

void ProjectileComponent::FireProjectile(float x, float y)
{
	if (m_time_interval > m_delay)
	{
		Bullet* bullet = new Bullet(x, y);
		bullet->m_damage = m_damage;
		bullet->m_velocity = m_velocity;
		bullet->initTexture(m_textureName);
		bullet->setAnimation(m_animationKey, m_timer, m_startFrameX, m_startFrameY, m_frameX, m_frameY, m_width, m_height);
		m_BulletList.push_back(bullet);
		clock.restart();
	}
}

void ProjectileComponent::update(const float& dt)
{
	m_time_interval = clock.getElapsedTime().asSeconds();
	
	for (Bullet* element : m_BulletList)
	{
		element->update(dt,m_animationKey);
	}
}

void ProjectileComponent::render(sf::RenderTarget* target)
{
	for (Bullet* element : m_BulletList)
	{
		element->render(target);
	}
}

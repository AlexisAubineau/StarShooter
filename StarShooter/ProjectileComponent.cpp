#include "ProjectileComponent.h"

#include <iostream>

#include "Bullet.h"

ProjectileComponent::ProjectileComponent(std::string textureName, std::string animationKey, std::string texturePathName,float timer,
                                         int startFrameX, int startFrameY, int frameX, int frameY, int width, int height, float velocity, float damage, float delay)
{
	m_textureName = textureName;
	m_animationKey = animationKey;
	m_texturePathName = texturePathName;
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
	for (Bullet* element : m_BulletList)
	{
		delete element;
	}
	m_BulletList.clear();
}

//Accessors
std::list<Bullet*> ProjectileComponent::getBulletList()
{
	if (m_BulletList.size() != 0)
	{
		return m_BulletList;
	}
	return std::list<Bullet*>{};
}

//Functions
void ProjectileComponent::FireProjectile(float x, float y)
{
	if (m_time_interval > m_delay)
	{
		Bullet* bullet = new Bullet(x, y);
		bullet->m_damage = m_damage;
		bullet->m_velocity = m_velocity;
		bullet->initTexture(m_textureName,m_texturePathName);
		bullet->setAnimation(m_animationKey, m_timer, m_startFrameX, m_startFrameY, m_frameX, m_frameY, m_width, m_height);
		m_BulletList.push_back(bullet);
		clock.restart();
	}
}

void ProjectileComponent::update(const float& dt, sf::RenderWindow* window)
{
	m_time_interval = clock.getElapsedTime().asSeconds();
	if (!m_BulletList.empty())
	{
		auto it = m_BulletList.begin();
		while (it != m_BulletList.end())
		{
			if (*it != nullptr)
				(*it)->update(dt, m_animationKey);
			
			if (out_of_bounds == true)
			{
				it = m_BulletList.erase(it);
				continue;
			}
			++it;
		}
	}
}

void ProjectileComponent::setProjectileTexture(std::string texturename, std::string texturePathName)
{
	m_textureName = texturename;
	m_texturePathName = texturePathName;
	
	for (Bullet* element : m_BulletList)
	{
		element->initTexture(m_textureName,m_texturePathName);
	}
}

void ProjectileComponent::SetBulletTags(std::string tag)
{
	for (Bullet* element : m_BulletList)
	{
		element->setTag(tag);
	}
}

void ProjectileComponent::render(sf::RenderTarget& target)
{
	for (Bullet* element : m_BulletList)
	{
		element->render(target);
	}
}

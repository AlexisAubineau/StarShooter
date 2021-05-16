#include "EnemySpawnerComponent.h"
#include "EnemyMaster.h"

EnemySpawnerComponent::EnemySpawnerComponent(std::string textureName, std::string animationKey,
	std::string texturePathName, float timer, int startFrameX, int startFrameY, int frameX, int frameY, int width,
	int height, float velocity, float damage, float life, float accel)
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
	m_accel = accel;
	m_life = life;
}

EnemySpawnerComponent::~EnemySpawnerComponent()
{
	for (EnemyMaster* element : m_EnemyList)
	{
		delete element;
	}
	m_EnemyList.clear();
}

std::list<EnemyMaster*> EnemySpawnerComponent::getEnemiesList()
{
	if(m_EnemyList.size() != 0)
	{
		return m_EnemyList;
	}
	return std::list<EnemyMaster*>{};
}

void EnemySpawnerComponent::spawnEnemy(float x, float y)
{
	EnemyMaster* enemy = new EnemyMaster(x,y);
	enemy->window = window;
	enemy->m_damage = m_damage;
	enemy->m_velocity = m_velocity;
	enemy->initTexture(m_textureName,m_texturePathName);
	enemy->setAnimation(m_animationKey, m_timer, m_startFrameX, m_startFrameY, m_frameX, m_frameY, m_width, m_height);
	m_EnemyList.push_back(enemy);
}

void EnemySpawnerComponent::setEnemyTexture(std::string texturename, std::string texturePathName)
{
	m_textureName = texturename;
	m_texturePathName = texturePathName;
	
	for (EnemyMaster* element : m_EnemyList)
	{
		element->initTexture(m_textureName,m_texturePathName);
	}
}

void EnemySpawnerComponent::update(const float& dt)
{
	for (EnemyMaster* element : m_EnemyList)
	{
		element->update(dt,m_animationKey);
	}
}

void EnemySpawnerComponent::render(sf::RenderTarget& target)
{
	for (EnemyMaster* element : m_EnemyList)
	{
		element->render(target);
	}
}

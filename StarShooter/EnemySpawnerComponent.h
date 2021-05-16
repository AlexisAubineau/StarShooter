#ifndef ENEMYSPAWNERCOMPONENT_H
#define ENEMYSPAWNERCOMPONENT_H

#include <list>
#include <string>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


class EnemyMaster;

class EnemySpawnerComponent
{
private:
	std::string m_textureName;
	std::string m_animationKey;
	std::string m_texturePathName;

	float m_life;
	float m_damage;
	float m_velocity;
	float m_accel;

	float m_timer;
	int m_startFrameX;
	int m_startFrameY;
	int m_frameX;
	int m_frameY;
	int m_width;
	int m_height;

	
	
public:
	std::list<EnemyMaster*> m_EnemyList;
	sf::RenderWindow* window;
	
	EnemySpawnerComponent(std::string textureName,
		std::string animationKey,
		std::string texturePathName,
		float timer,
		int startFrameX,
		int startFrameY,
		int frameX,
		int frameY,
		int width,
		int height,
		float velocity,
		float damage,
		float life,
		float accel);
	~EnemySpawnerComponent();

	//Accessors
	std::list<EnemyMaster*> getEnemiesList();

	void spawnEnemy(float x, float y);
	void setEnemyTexture(std::string texturename, std::string texturePathName);

	void deleteEnemy(bool colliding, EnemyMaster* enemy);
	
	void update(const float& dt);
	void render(sf::RenderTarget& target);
	
};

#endif

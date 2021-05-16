#ifndef PROJECTILE_COMPONENT_H
#define PROJECTILE_COMPONENT_H

#include <list>
#include <string>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

class Bullet;

class ProjectileComponent
{
private:
	std::string m_textureName;
	std::string m_animationKey;
	std::string m_texturePathName;
	sf::Clock clock;

	
	float m_timer;
	int m_startFrameX;
	int m_startFrameY;
	int m_frameX;
	int m_frameY;
	int m_width;
	int m_height;
	float m_velocity;
	float m_damage;
	float m_delay;
	float m_time_interval;
	bool out_of_bounds;

public:
	std::list<Bullet*> m_BulletList;
	ProjectileComponent(std::string textureName,
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
		float delay);
	virtual ~ProjectileComponent();

	//Accessors
	std::list<Bullet*> getBulletList();

	void FireProjectile(float x, float y);
	void update(const float& dt, sf::RenderWindow* window);
	void setProjectileTexture(std::string texturename, std::string texturePathName);
	void render(sf::RenderTarget& target);
};


#endif
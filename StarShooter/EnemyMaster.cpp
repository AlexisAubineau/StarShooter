#include "EnemyMaster.h"
#include <iostream>

void EnemyMaster::initComponents()
{
	// Movement Component Player
	movementComponent = component->createMovementComponent(m_velocity, m_accel, m_accel);

	// Component Projectile Player 
	projectileComponent = component->createProjectileComponent("ENEMY_PROJECTILE", "SHIP_PROJECTILE",config->EnemyType1Projectile, 10.f, 0, 0, 4, 0, 120, 90, -0.0025f, 10.f, m_shoot_delay);

	// Player Hitbox Component
	hitboxComponent = component->createHitboxComponent(component->sprite, 0, 0, 80, 60, true);
}

void EnemyMaster::initTexture(std::string m_textureName, std::string m_pathname)
{
	if (!component->textures[m_textureName].loadFromFile(m_pathname))
		std::cout << "ERROR::GAME_STATE::COULD_NOT_LOAD_ENEMY_TEXTURE" << std::endl;
	
	animationComponent = component->createAnimationComponent(component->textures[m_textureName]);
}

EnemyMaster::EnemyMaster(float m_posx, float m_posy)
{
	setPosition(m_posx, m_posy);
	initComponents();
	setHitbox(hitboxComponent);
	setMovement(movementComponent);
}

EnemyMaster::~EnemyMaster()
{
	delete movementComponent;
	delete animationComponent;
	delete projectileComponent;
	delete hitboxComponent;
}


void EnemyMaster::setAnimation(std::string m_animationKey, float m_timer, int m_startFrameX, int m_startFrameY,
	int m_frameX, int m_frameY, int m_width, int m_height)
{
	animationComponent->addAnimation(m_animationKey, m_timer, m_startFrameX, m_startFrameY, m_frameX, m_frameY, m_width, m_height);
}

void EnemyMaster::move(const float& dt)
{
	if (movementComponent)
	{
		movementComponent->move(-m_velocity, 0, dt);
	}
}

void EnemyMaster::attack()
{
	if (projectileComponent)
	{
		projectileComponent->FireProjectile((getPosition().x), (getPosition().y));
	}
	
}

void EnemyMaster::update(const float& dt, std::string m_animationKey)
{
	movementComponent->update(dt);
	move(dt);
	animationComponent->play(m_animationKey, dt);
	projectileComponent->update(dt, window);
	hitboxComponent->update();
	attack();
}

void EnemyMaster::render(sf::RenderTarget& target)
{
	target.draw(component->sprite);
	projectileComponent->render(target);
	hitboxComponent->render(&target);
}

void EnemyMaster::initVariables()
{
	max_life = 100.f;
	current_life = max_life;
	tile_damage = 8.f;
}

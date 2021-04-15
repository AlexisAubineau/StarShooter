#include "Bullet.h"

void Bullet::initComponents()
{
}

void Bullet::setAnimation(std::string m_animationKey, float m_timer,int m_startFrameX,int m_startFrameY, int m_frameX, int m_frameY,
	int m_width, int m_height)
{
	animationComponent->addAnimation(m_animationKey,m_timer,m_startFrameX,m_startFrameY,m_frameX,m_frameY,m_width,m_height);
}

void Bullet::initTexture(std::string m_textureName)
{
	if (!component->textures[m_textureName].loadFromFile(config->playerIdlePath)) {
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PROJECTILE_TEXTURE";
	}
		animationComponent = component->createAnimationComponent(component->textures[m_textureName]);
		
}

Bullet::Bullet(float m_posx, float m_posy)
{
	setPosition(m_posx,m_posy);

	movementComponent = component->createMovementComponent(m_velocity,0,0);
	
	
}

Bullet::~Bullet()
{
	delete movementComponent;
	delete animationComponent;
}

void Bullet::Movement(const float& dt)
{
	if (movementComponent)
	{
		movementComponent->move(m_velocity,0,dt);
	}
}

void Bullet::update(const float& dt, std::string m_animationKey)
{
	movementComponent->update(dt);
	if (animationComponent)
	{
		animationComponent->play(m_animationKey,dt);
	}

}

#include "Bullet.h"
#include <iostream>

void Bullet::initComponents()
{
	movementComponent = component->createMovementComponent(m_velocity, m_velocity * 100, -m_velocity * 10);
	hitboxComponent = component->createHitboxComponent(component->sprite, 40, 30, 90, 30, false);
}

void Bullet::setAnimation(std::string m_animationKey, float m_timer, int m_startFrameX, int m_startFrameY, int m_frameX, int m_frameY,
	int m_width, int m_height)
{
	animationComponent->addAnimation(m_animationKey, m_timer, m_startFrameX, m_startFrameY, m_frameX, m_frameY, m_width, m_height);
}

void Bullet::initTexture(std::string m_textureName, std::string m_pathname)
{
	if (!component->textures[m_textureName].loadFromFile(m_pathname)) 
		std::cout << "ERROR::GAME_STATE::COULD_NOT_LOAD_PROJECTILE_TEXTURE" << std::endl;
	
	animationComponent = component->createAnimationComponent(component->textures[m_textureName]);
}

Bullet::Bullet(float m_posx, float m_posy)
{
	setPosition(m_posx, m_posy);
	initComponents();
	setHitbox(hitboxComponent);
	setMovement(movementComponent);
}

Bullet::~Bullet()
{
	delete movementComponent;
	delete animationComponent;
	delete hitboxComponent;
}

void Bullet::Movement(const float& dt)
{
	if (movementComponent)
		movementComponent->move(m_velocity, 0, dt);
}

void Bullet::update(const float& dt, std::string m_animationKey)
{
	if (movementComponent)
	{
		Movement(dt);
		movementComponent->update(dt);
	}
	
	if (animationComponent)
		animationComponent->play(m_animationKey, dt);
	
	if (hitboxComponent)
		hitboxComponent->update();

}

void Bullet::render(sf::RenderTarget& target)
{
	hitboxComponent->render(&target);
	target.draw(component->sprite);
}

void Bullet::setTag(std::string tag)
{
	hitboxComponent->setTag(tag);
}

std::string Bullet::GetTag()
{
	return hitboxComponent->GetTag();
}

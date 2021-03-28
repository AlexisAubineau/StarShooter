#include "Player.h"

//Initializer functions
void Player::initVariables()
{
}

void Player::initComponents()
{
	
}

//Contructors / Destructors
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createMovementComponent(300.f, 15.f, 5.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("SHIP_IDLE", 10.f, 0, 0, 4, 0, 120, 90);
}

Player::~Player()
{

}

void Player::PlayerShoot()
{
}

// Functions

void Player::update(const float& dt)
{
	this->movementComponent->update(dt);

	this->animationComponent->play("SHIP_IDLE", dt);
}
 
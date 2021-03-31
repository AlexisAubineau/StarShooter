#include "Player.h"

//Initializer functions
void Player::initVariables()
{
}

void Player::initComponents()
{
	
}

void Player::initTexture()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile(config->playerIdlePath)) {
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
}

//Contructors / Destructors
Player::Player(float x, float y)
{
	this->initVariables();
	this->initTexture();
	this->setPosition(x, y);

	this->createMovementComponent(300.f, 15.f, 5.f);
	this->createAnimationComponent(this->textures["PLAYER_SHEET"]);

	this->setLifePlayer();

	std::cout << life << std::endl;
	
	this->animationComponent->addAnimation("SHIP_IDLE", 10.f, 0, 0, 4, 0, 120, 90);
}

Player::~Player()
{

}

void Player::setLifePlayer()
{
	this->life = 100.f;
}

float Player::getLifePlayer()
{
	return life;
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
 
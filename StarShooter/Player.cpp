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
	if (!component->textures["PLAYER_SHEET"].loadFromFile(config->playerIdlePath)) {
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
}

//Contructors / Destructors
Player::Player(float x, float y)
{
	initVariables();
	initTexture();
	setPosition(x, y);

	movementComponent = component->createMovementComponent(300.f, 15.f, 5.f);
	animationComponent = component->createAnimationComponent(component->textures["PLAYER_SHEET"]);

	std::cout << health << std::endl;
	
	animationComponent->addAnimation("SHIP_IDLE", 10.f, 0, 0, 4, 0, 120, 90);
}

Player::~Player()
{
	delete movementComponent;
	delete animationComponent;
}

void Player::move(const float dir_x, const float dir_y, const float& dt)
{
	if (movementComponent) {
		movementComponent->move(dir_x, dir_y, dt); //Sets velocity
	}
}

void Player::attack()
{
}

// Functions

void Player::update(const float& dt)
{
	movementComponent->update(dt);
	animationComponent->play("SHIP_IDLE", dt);
	Life(health);
	
}
 
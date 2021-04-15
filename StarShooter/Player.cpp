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

	// Movement Component Player
	movementComponent = component->createMovementComponent(300.f, 15.f, 5.f);

	// Animation Player
	animationComponent = component->createAnimationComponent(component->textures["PLAYER_SHEET"]);
	animationComponent->addAnimation("SHIP_IDLE", 10.f, 0, 0, 4, 0, 120, 90);

	// Component Projectile Player 
	projectileComponent = component->createProjectileComponent("SHIP_PROJECTILE_SHEET", "SHIP_PROJECTILE", 10.f, 0, 0, 4, 0, 120, 90, 10.f, 10.f);
}

Player::~Player()
{
	delete movementComponent;
	delete animationComponent;
	delete projectileComponent;
}

void Player::move(const float dir_x, const float dir_y, const float& dt)
{
	if (movementComponent) {
		movementComponent->move(dir_x, dir_y, dt); //Sets velocity
	}
}

void Player::attack()
{
	if (projectileComponent)
	{
		projectileComponent->FireProjectile(getPosition().x, getPosition().y);
		std::cout << "Hey je tire fdp !" << std::endl;
	}
	
}

// Functions

void Player::update(const float& dt)
{
	movementComponent->update(dt);
	animationComponent->play("SHIP_IDLE", dt);
	Life(health);
	
}

void Player::updateInput(const float& dt)
{
}
 
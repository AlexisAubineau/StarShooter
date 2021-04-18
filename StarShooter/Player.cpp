#include "Player.h"

//Initializer functions
void Player::initVariables()
{
}

void Player::initComponents()
{
	// Movement Component Player
	movementComponent = component->createMovementComponent(800.f, 15.f, 15.f);

	// Animation Player
	animationComponent = component->createAnimationComponent(component->textures["PLAYER_SHEET"]);
	animationComponent->addAnimation("SHIP_IDLE", 10.f, 0, 0, 4, 0, 120, 90);

	// Component Projectile Player 
	projectileComponent = component->createProjectileComponent("SHIP_PROJECTILE_SHEET", "SHIP_PROJECTILE", config->ProjectilePath, 10.f, 0, 0, 4, 0, 120, 90, 0.0025f, 10.f, shoot_delay);

	inputComponent = component->createInputComponent();
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
	initComponents();
	setPosition(x, y);
	
	player_gui = new PlayerGUI(this);
	
	maxLife(max_life);
	Life(current_life);
}

Player::~Player()
{
	delete movementComponent;
	delete animationComponent;
	delete projectileComponent;
	delete inputComponent;
	delete player_gui;
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
	}
	
}

// Functions

void Player::update(const float& dt)
{
	movementComponent->update(dt);
	animationComponent->play("SHIP_IDLE", dt);
	projectileComponent->update(dt);
	player_gui->update(dt);
	inputComponent->updateInput(dt, this, keybinds, supportedKeys, locationAllowed);
	checkLocationAllowed();
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(component->sprite);
	projectileComponent->render(target);
	player_gui->render(target);
}

void Player::checkLocationAllowed()
{
	player_location = component->sprite.getPosition();

	float x = player_location.x;
	float y = player_location.y;

	if (movementComponent->m_dir_x > 0 || movementComponent->m_dir_y > 0)
	{
		if (x + movementComponent->m_dir_x + 100 >= window->getSize().x || y + movementComponent->m_dir_y + 55 >= window->getSize().y)
		{
			std::cout << "false" << std::endl;
			locationAllowed = false;
			movementComponent->velocity = sf::Vector2f(0, 0);
			movementComponent->m_dir_x = 0;
			movementComponent->m_dir_y = 0;
		}
	}
	if (movementComponent->m_dir_x < 0 || movementComponent->m_dir_y < 0)
	{
		if (x - movementComponent->m_dir_x - 25 < 0 || y - movementComponent->m_dir_y - 20 < 0)
		{
			std::cout << movementComponent->m_dir_x << std::endl;;
			locationAllowed = false;
			movementComponent->velocity = sf::Vector2f(0, 0);
			movementComponent->m_dir_x = 0;
			movementComponent->m_dir_y = 0;
		}
	}
	else
	{
		locationAllowed = true;
	}
}

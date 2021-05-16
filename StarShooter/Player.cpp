#include "Player.h"


#include "Bullet.h"
#include "Tilemap.h"

//Initializer functions
void Player::initVariables()
{
	max_life = 200.f;
	current_life = max_life;
	damage = 1.f;
}

void Player::initComponents()
{
	// Movement Component Player
	movementComponent = component->createMovementComponent(500.f, 1500.f, 500.f);

	// Animation Player
	animationComponent = component->createAnimationComponent(component->textures["PLAYER_SHEET"]);
	animationComponent->addAnimation("SHIP_IDLE", 10.f, 0, 0, 4, 0, 120, 90);

	// Component Projectile Player 
	projectileComponent = component->createProjectileComponent("SHIP_PROJECTILE_SHEET", "SHIP_PROJECTILE", config->ProjectilePath, 10.f, 0, 0, 4, 0, 120, 90, 2000.f, 10.f, shoot_delay);

	// Input for player
	inputComponent = component->createInputComponent();

	// Player Hitbox Component
	hitboxComponent = component->createHitboxComponent(component->sprite, 0, 10, component->sprite.getGlobalBounds().width, 70, true);
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
	setHitbox(hitboxComponent);
	setMovement(movementComponent);
}

Player::~Player()
{
	delete movementComponent;
	delete animationComponent;
	delete projectileComponent;
	delete inputComponent;
	delete hitboxComponent;
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

void Player::updateProjectileCollision(Tilemap* tilemap, const float& dt)
{
	if (projectileComponent->getBulletList().size() != 0)
	{
		for (Bullet* element: projectileComponent->getBulletList())
		{
			tilemap->updateCollision(element, dt);
		}
	}
}

// Functions

void Player::update(const float& dt)
{
	movementComponent->update(dt);
	
	animationComponent->play("SHIP_IDLE", dt);
	
	projectileComponent->update(dt, window);
	
	inputComponent->updateInput(dt, this, keybinds, supportedKeys);

	hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(component->sprite);
	projectileComponent->render(target);
	hitboxComponent->render(&target);
}

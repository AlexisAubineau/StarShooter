#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <fstream>
#include "PlayerGUI.h"
#include "Entity.h"

class Player :
	public Entity
{
private:
	//Variables
	float shoot_delay = .5f;
	
	PlayerGUI* player_gui;
	sf::Vector2f player_location;

	//Initializer functions
	void initVariables();
	void initComponents();
	void initTexture();

protected:
	//Initializer Components
	AnimationComponent* animationComponent;
	MovementComponent* movementComponent;
	ProjectileComponent* projectileComponent;
	InputComponent* inputComponent;
	HitboxComponent* hitboxComponent;

public:
	Player(float x, float y);
	virtual ~Player();

	//Variables
	float max_life = 200.f;
	float current_life = 150.f;
	
	std::map<std::string, int> keybinds;
	std::map<std::string, int>* supportedKeys;
	sf::RenderWindow* window;
	
	//Functions
	void move(const float dir_x, const float dir_y, const float& dt);
	void attack();
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};

#endif
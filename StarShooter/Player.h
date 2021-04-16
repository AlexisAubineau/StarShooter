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

public:
	Player(float x, float y);
	virtual ~Player();

	float health = 150.f;
	std::map<std::string, int> keybinds;
	std::map<std::string, int>* supportedKeys;
	
	//Functions
	void move(const float dir_x, const float dir_y, const float& dt);
	void attack();
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};

#endif
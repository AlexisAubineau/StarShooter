#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

class MovementComponent
{
private:
	//Variables
	sf::Vector2f velocity;
	sf::Sprite& sprite;
	
	float maxVelocity;
	float acceleration;
	float deceleration;
	float m_dir_x = 0.f;
	float m_dir_y = 0.f;

	//Initializer functions

public:
	bool locationAllowed;
	
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Accessors
	const sf::Vector2f& getVelocity() const;

	//Functions
	void move(const float x, const float y, const float& dt);
	void update(const float& dt);
	void checkLocationAllowed(sf::RenderWindow* m_window, sf::Sprite m_sprite);
};
 
#endif // !MOVEMENTCOMPONENT_H
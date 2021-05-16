 #ifndef ENTITY_H
#define ENTITY_H

#include "Component.h"
#include "Config.h"

 class Entity
{
private:

protected:
	Component* component = new Component;
	HitboxComponent* hitbox_component;
	MovementComponent* movement_component;
 
public:
	Entity();
	virtual ~Entity();

	//Variables
	sf::RenderWindow* window;
 	
	Config* config = new Config;

	float max_life;
	float current_life;
	float tile_damage;


	//Component functions
	void setTexture(sf::Texture& texture);
	void setHitbox(HitboxComponent* hitbox);
	void setMovement(MovementComponent* movement);

	//Accessors
 	virtual const sf::Vector2f& getPosition() const;
	virtual const sf::Vector2i getGridPosition(const int gridSizeI) const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const sf::FloatRect& getNextPositionBounds(const float& dt) const;
	virtual float GetLife();

 	//Modifiers
	virtual float MaxLife(float m_max_life);
	virtual float CurrentLife(float m_current_life);
 	
	//Functions
	virtual void setPosition(const float x, const float y);
	virtual void stopVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();
	virtual float tileDamage();

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target) = 0;
};
 
#endif //ENTITY_H
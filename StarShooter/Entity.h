 #ifndef ENTITY_H
#define ENTITY_H

#include "Component.h"
#include "Config.h"

 class Entity
{
private:

protected:
	Component* component = new Component;
 
public:
	Entity();
	virtual ~Entity();

	//Variables
 	
	Config* config = new Config;


	//Component functions
	void setTexture(sf::Texture& texture);

	//Functions
	virtual void setPosition(const float x, const float y);
	sf::Vector2f getPosition();
	float Life(float life);
	float maxLife(float maxLife);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};
 
#endif //ENTITY_H
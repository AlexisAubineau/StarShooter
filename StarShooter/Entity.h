 #ifndef ENTITY_H
#define ENTITY_H

#include "Config.h"
#include "Component.h"

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
	float Life(float life);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};
 
#endif //ENTITY_H
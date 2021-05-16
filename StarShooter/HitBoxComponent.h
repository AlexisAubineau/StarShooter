#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

#include <list>
#include <SFML/Graphics.hpp>

class Entity;
class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::FloatRect nextPosition;
	float offsetX;
	float offsetY;
	std::string m_tag;
	bool CanDamage;
 
public:
	std::list<std::string> CollisionTagList;
	HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height, bool isDebug);
	~HitboxComponent();

	//Accessors
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);
	
	//Modifiers
	void setPosition(const sf::Vector2f& position);
	void setPosition(const float x, const float y);
	void SetCollisionEnable(bool state, std::list<Entity*> EntityList);
	void setTag(std::string tag);
	std::string GetTag();
	
	// Functions
	bool Intersets(const sf::FloatRect& frect);
	std::string CheckColliderInfo(HitboxComponent* Collider);
	
	
	void update();
	void render(sf::RenderTarget* target);
	void debugOutline(bool isDebug);
};

#endif // HITBOXCOMPONENT_H
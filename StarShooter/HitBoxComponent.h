#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

#include <SFML/Graphics.hpp>

class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;
 
public:
	HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height, bool isDebug);
	~HitboxComponent();

	// Functions
	bool checkInterset(const sf::FloatRect& frect);
	void update();
	void render(sf::RenderTarget* target);
	void debugOutline(bool isDebug);
};

#endif // HITBOXCOMPONENT_H
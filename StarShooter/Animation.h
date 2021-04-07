#ifndef ANIMATION_H
#define ANIMATION_H

#include"SFML\Graphics.hpp"

class Animation
{
public:
	//Variables
	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	float animationTimer;
	float timer;
	int width;
	int height;
	sf::IntRect startRect;
	sf::IntRect currentRect;
	sf::IntRect endRect;

	Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, float animationTimer, int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);

	//Functions
	void play(const float& dt);

	void reset();
};

#endif //ANIMATION_H
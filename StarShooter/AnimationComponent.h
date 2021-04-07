#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include<string>
#include<map>


#include "Animation.h"
#include"SFML\Graphics.hpp"

class AnimationComponent
{
private:
	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	std::map<std::string, Animation*> animations;
	
public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
	virtual ~AnimationComponent();

	//Functions
	void addAnimation(const std::string key, float animationTimer, int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);
	
	void play(const std::string key, const float& dt);
};
#endif
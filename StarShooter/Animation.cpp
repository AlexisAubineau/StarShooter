#include "Animation.h"

Animation::Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, float animationTimer, int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
	: sprite(sprite), textureSheet(texture_sheet), animationTimer(animationTimer), width(width), height(height)
{
	timer = 0.f;
	startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
	currentRect = startRect;
	endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

	sprite.setTexture(textureSheet, true);
	sprite.setTextureRect(startRect);
}

//Functions
void Animation::play(const float& dt)
{
	//Update Timer
	timer += 100.f * dt;
	if (timer >= animationTimer)
	{
		//reset timer
		timer = 0.f;

		//Animate
		if (currentRect != endRect)
		{
			currentRect.left += width;
		}
		else //Reset
		{
			currentRect.left = startRect.left;
		}

		sprite.setTextureRect(currentRect);
	}
}

void Animation::reset()
{
	timer = 0.f;
	currentRect = startRect;
}


#include "HitboxComponent.h"

#include <iostream>

#include "Entity.h"


HitboxComponent::HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height, bool isDebug)
	: sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
	nextPosition.left = 0.f;
	nextPosition.top = 0.f;
	nextPosition.width = width;
	nextPosition.height = height;
	
	hitbox.setPosition(sprite.getPosition().x + offset_x, sprite.getPosition().y + offset_y);
	hitbox.setSize(sf::Vector2f(width, height));
	hitbox.setFillColor(sf::Color::Transparent);
	
	debugOutline(isDebug);
}

HitboxComponent::~HitboxComponent()
{
}

//Accessors
const sf::Vector2f& HitboxComponent::getPosition() const
{
	return hitbox.getPosition();
}

const sf::FloatRect HitboxComponent::getGlobalBounds() const
{
	return hitbox.getGlobalBounds();
}

const sf::FloatRect& HitboxComponent::getNextPosition(const sf::Vector2f& velocity)
{
	nextPosition.left = hitbox.getPosition().x + velocity.x;
	nextPosition.top = hitbox.getPosition().y + velocity.y;
	return nextPosition;
}

//Modifiers
void HitboxComponent::setPosition(const sf::Vector2f& position)
{
	hitbox.setPosition(position);
	sprite.setPosition(position.x - offsetX, position.y - offsetY);
}

void HitboxComponent::setPosition(const float x, const float y)
{
	hitbox.setPosition(x, y);
	sprite.setPosition(x - offsetX, y - offsetY);
}


void HitboxComponent::SetCollisionEnable(bool state,std::list<Entity*> EntityList)
{
	if (state)
	{
		for (Entity* element : EntityList)
		{
			if(Intersets(element->getGlobalBounds()))
			{
				std::cout<< "I'm being touched." << std::endl;
				CollisionTagList.push_back(CheckColliderInfo(element->GetHitbox()));
				std::cout << CheckColliderInfo(element->GetHitbox()) << std::endl;
				element->stopVelocity();
			}
		}
	}
}


void HitboxComponent::setTag(std::string tag)
{
	m_tag = tag;
}

std::string HitboxComponent::GetTag()
{
	return m_tag;
}

//Functions
bool HitboxComponent::Intersets(const sf::FloatRect& frect)
{
	return hitbox.getGlobalBounds().intersects(frect);
}



std::string HitboxComponent::CheckColliderInfo(HitboxComponent* Collider)
{
	if (Intersets(Collider->hitbox.getGlobalBounds()))
	{
		std::string collidertag = Collider->m_tag;
		return  collidertag;
	}
}


void HitboxComponent::update()
{
	hitbox.setPosition(sprite.getPosition().x + offsetX, sprite.getPosition().y + offsetY);
}

void HitboxComponent::render(sf::RenderTarget* target)
{
	target->draw(hitbox);
}

void HitboxComponent::debugOutline(bool isDebug)
{
	if (isDebug == true)
	{
		hitbox.setOutlineThickness(-1.f);
		hitbox.setOutlineColor(sf::Color::Red);
	}
}

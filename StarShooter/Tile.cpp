#include "Tile.h"

#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>
#include <sstream>

Tile::Tile()
{
	collision = false;
	type = 0;
}

Tile::Tile(int grid_x, int grid_y, float gridSizef, sf::Texture& texture, const sf::IntRect& texture_rect, bool m_collision, short m_type)
{
	shape.setSize(sf::Vector2f(gridSizef, gridSizef));
	shape.setFillColor(sf::Color::White);
	//shape.setOutlineThickness(1.f);
	//shape.setOutlineColor(sf::Color::Black);
	shape.setPosition(static_cast<float>(grid_x * gridSizef), static_cast<float>(grid_y * gridSizef));
	shape.setTexture(&texture);
	shape.setTextureRect(texture_rect);
	
	collision = m_collision;
	type = m_type;
}

Tile::~Tile()
{
}

//Functions

const sf::Vector2f& Tile::getPosition() const
{
	return shape.getPosition();
}

const bool& Tile::getCollision() const
{
	return collision;
}

const sf::FloatRect Tile::getGlobalBounds() const
{
	return shape.getGlobalBounds();
}

const bool Tile::intersects(const sf::FloatRect bounds) const
{
	return shape.getGlobalBounds().intersects(bounds);
}

const std::string Tile::getAsString() const
{
	std::stringstream ss;

	ss << shape.getTextureRect().left << " " << shape.getTextureRect().top << " " << collision << " " << type;
	
	return ss.str();
}

void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(shape);
}

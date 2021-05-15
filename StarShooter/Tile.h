#ifndef TILE_H
#define TILE_H
#include <string>
#include <SFML/Graphics.hpp>

enum TileTypes { DEFAULT = 0, SPAWNER = 1 };

class Tile
{
private:

protected:
	sf::RectangleShape shape;
	bool collision;
	short type;

public:
	Tile();
	Tile(int grid_x, int grid_y, float gridSizef, sf::Texture& texture, const sf::IntRect& texture_rect, bool m_collision = false, short m_type = TileTypes::DEFAULT);
	~Tile();

	//Accessors
	const sf::Vector2f& getPosition() const;
	const bool& getCollision() const;
	const sf::FloatRect getGlobalBounds() const;
	const bool intersects(const sf::FloatRect bounds) const;

	//Functions
	const std::string getAsString() const;
	
	void update();
	void render(sf::RenderTarget& target);
};
#endif //TILE_H
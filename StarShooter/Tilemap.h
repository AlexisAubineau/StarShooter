#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include "Entity.h"
#include "Tile.h"

class Entity;

class Tilemap
{
private:
	void clear();
	
	float gridSizeF;
	int gridSizeI;
	int layers;
	sf::Vector2i maxSizeWorldGrid;
	sf::Vector2f maxSizeWorld;
	//   X           Y           Layer
	std::vector<std::vector<std::vector<Tile*>>> map;
	std::string textureFile;
	sf::Texture tileSheet;
	sf::RectangleShape collisionBox;

	//Culling
	int fromX;
	int toX;
	int fromY;
	int toY;
	int layer;

public:
	Tilemap(float gridSize, int width, int height, std::string texture_file);
	~Tilemap();

	//Accessors
	const sf::Texture* getTileSheet() const;

	//Functions
	void addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const bool& collision, const short& type);
	void removeTile(const int x, const int y, const int z);
	
	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);

	void updateCollision(Entity* entity, const float& dt);
	void CollisionTileDebug(bool debug);
	
	void update();
	void render(sf::RenderTarget& target, bool debug);
};
#endif //TILEMAP_H
#include "Tilemap.h"


#include <fstream>
#include <iostream>
#include <SFML/Graphics/Texture.hpp>

void Tilemap::clear()
{
	for (int x = 0; x < maxSizeWorldGrid.x; x++)
	{
		for (int y = 0; y < maxSizeWorldGrid.y; y++)
		{
			for (int z = 0; z < layers; z++)
			{
				delete map[x][y][z];
				map[x][y][z] = NULL;
			}
			map[x][y].clear();
		}
		map[x].clear();
	}
	map.clear();

	//std::cout << map.size() << "\n";
}

Tilemap::Tilemap(float gridSize, int width, int height, std::string texture_file)
{
	gridSizeF = gridSize;
	gridSizeI = static_cast<unsigned>(gridSizeF);
	maxSizeWorldGrid.x = width;
	maxSizeWorldGrid.y = height;
	maxSizeWorld.x = static_cast<float>(width) * gridSize;
	maxSizeWorld.y = static_cast<float>(height) * gridSize;
	layers = 1;
	textureFile = texture_file;

	fromX = 0;
	toX = 0;
	fromY = 0;
	toY = 0;
	layer = 0;

	map.resize(maxSizeWorldGrid.x, std::vector< std::vector<Tile*> >());
	for (int x = 0; x < maxSizeWorldGrid.x; x++)
	{
		for (int y = 0; y < maxSizeWorldGrid.y; y++)
		{
			map[x].resize(maxSizeWorldGrid.y, std::vector<Tile*>());

			for (int z = 0; z < layers; z++)
			{
				map[x][y].resize(layers, NULL);
			}
		}
	}

	if (!tileSheet.loadFromFile(texture_file))
		std::cout << "ERROR::Tilemap::FAILED TO LOAD TILETEXTURESHEET::FILENAME: " << texture_file << "\n";

	collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	
}

Tilemap::~Tilemap()
{
	clear();
}

//Accessors
const sf::Texture* Tilemap::getTileSheet() const
{
	return &tileSheet;
}

//Functions
void Tilemap::addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const bool& collision, const short& type)
{
	/* Take three indicies from the mouse position in the grid and add a tile to that position if the internal Tilemap array allows it. */

	if (x < maxSizeWorldGrid.x && x >= 0 &&
		y < maxSizeWorldGrid.y && y >= 0 &&
		z < layers && z >= 0)
	{
		if (map[x][y][z] == NULL)
		{
			/* OK To add tile. */
			map[x][y][z] = new Tile(x, y, gridSizeF, tileSheet, texture_rect, collision, type);
			std::cout << "DEGBUG: ADDED TILE!" << "\n";
		}
	}
}

void Tilemap::removeTile(const int x, const int y, const int z)
{
	/* Take three indicies from the mouse position in the grid and remove a tile at that position if the internal Tilemap array allows it. */

	if (x < maxSizeWorldGrid.x && x >= 0 &&
		y < maxSizeWorldGrid.y && y >= 0 &&
		z < layers && z >= 0)
	{
		if (map[x][y][z] != NULL)
		{
			/* OK To remove tile. */
			delete map[x][y][z];
			map[x][y][z] = NULL;
			std::cout << "DEGBUG: REMOVED TILE!" << "\n";
		}
	}
}

void Tilemap::saveToFile(const std::string file_name)
{
	/*
	 * Saves the entire Tilemap to a text-file.
	 *
	 * Format:
	 *
	 * Basic:
	 *	Size x y
	 *	gridSize
	 *	layers
	 *	texture file
	 *
	 * All tiles:
	 *	gridPos x y
	 *	layer
	 *	Texture rect x y
	 *	collision
	 *	type
	 */

	std::ofstream out_file;

	out_file.open(file_name);

	if (out_file.is_open())
	{
		out_file << maxSizeWorldGrid.x << " " << maxSizeWorldGrid.y << "\n"
			<< gridSizeI << "\n"
			<< layers << "\n"
			<< textureFile << "\n";

		for (int x = 0; x < maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < maxSizeWorldGrid.y; y++)
			{
				for (int z = 0; z < layers; z++)
				{
					if (map[x][y][z])
						out_file << x << " " << y << " " << z << " " <<
						map[x][y][z]->getAsString()
						<< " "; //MAKE SURE THIS LAST SPACE IS NOT SAVED!!!!
				}
			}
		}
	}
	else
	{
		std::cout << "ERROR::Tilemap::COULD NOT SAVE TO FILE::FILENAME: " << file_name << "\n";
	}

	out_file.close();
}

void Tilemap::loadFromFile(const std::string file_name)
{
	std::ifstream in_file;

	in_file.open(file_name);

	if (in_file.is_open())
	{
		sf::Vector2i size;
		int gridSize = 0;
		int m_layers = 0;
		std::string texture_file = "";
		int x = 0;
		int y = 0;
		int z = 0;
		int trX = 0;
		int trY = 0;
		bool collision = false;
		short type = 0;

		//Basics
		in_file >> size.x >> size.y >> gridSize >> m_layers >> texture_file;

		//Tiles
		gridSizeF = static_cast<float>(gridSize);
		gridSizeI = gridSize;
		maxSizeWorldGrid.x = size.x;
		maxSizeWorldGrid.y = size.y;
		layers = m_layers;
		textureFile = texture_file;

		clear();

		map.resize(maxSizeWorldGrid.x, std::vector< std::vector<Tile*> >());
		for (int x = 0; x < maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < maxSizeWorldGrid.y; y++)
			{
				map[x].resize(maxSizeWorldGrid.y, std::vector<Tile*>());

				for (int z = 0; z < layers; z++)
				{
					map[x][y].resize(layers, NULL);
				}
			}
		}

		if (!tileSheet.loadFromFile(texture_file))
			std::cout << "ERROR::Tilemap::FAILED TO LOAD TILETEXTURESHEET::FILENAME: " << texture_file << "\n";

		//Load all tiles
		while (in_file >> x >> y >> z >> trX >> trY >> collision >> type)
		{
			map[x][y][z] = new Tile(
				x, y,
				gridSizeF,
				tileSheet,
				sf::IntRect(trX, trY, gridSizeI, gridSizeI),
				collision,
				type
			);
		}
	}
	else
	{
		std::cout << "ERROR::Tilemap::COULD NOT LOAD FROM FILE::FILENAME: " << file_name << "\n";
	}

	in_file.close();
}

void Tilemap::updateCollision(Entity* entity, const float& dt)
{
	//WORLD BOUNDS
	if (entity->getPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > maxSizeWorld.x)
	{
		entity->setPosition(maxSizeWorld.x - entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}
	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(entity->getPosition().x, 0.f);
		entity->stopVelocityY();
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > maxSizeWorld.y)
	{
		entity->setPosition(entity->getPosition().x, maxSizeWorld.y - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}

	//TILES
	layer = 0;

	fromX = entity->getGridPosition(gridSizeI).x - 1;
	if (fromX < 0)
		fromX = 0;
	else if (fromX > static_cast<int>(maxSizeWorldGrid.x))
		fromX = maxSizeWorldGrid.x;

	toX = entity->getGridPosition(gridSizeI).x + 3;
	if (toX < 0)
		toX = 0;
	else if (toX > static_cast<int>(maxSizeWorldGrid.x))
		toX = maxSizeWorldGrid.x;

	fromY = entity->getGridPosition(gridSizeI).y - 1;
	if (fromY < 0)
		fromY = 0;
	else if (fromY > static_cast<int>(maxSizeWorldGrid.y))
		fromY = maxSizeWorldGrid.y;

	toY = entity->getGridPosition(gridSizeI).y + 3;
	if (toY < 0)
		toY = 0;
	else if (toY > static_cast<int>(maxSizeWorldGrid.y))
		toY = maxSizeWorldGrid.y;
	
	for (int x = fromX; x < toX; x++)
	{
		for (int y = fromY; y < toY; ++y)
		{
			if (map[x][y][layer] != nullptr)
			{
				sf::FloatRect entityBounds = entity->getGlobalBounds();
				sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);
				sf::FloatRect wallBounds = map[x][y][layer]->getGlobalBounds();

				if (map[x][y][layer]->getCollision() && map[x][y][layer]->intersects(nextPositionBounds))
				{
					std::cout << "Collision" << std::endl;
					
					//Bottom collision
					if (entityBounds.top < wallBounds.top
						&& entityBounds.top + entityBounds.height < wallBounds.top + wallBounds.height
						&& entityBounds.left < wallBounds.left + wallBounds.width
						&& entityBounds.left + entityBounds.width > wallBounds.left
						)
					{
						entity->stopVelocityY();
						entity->setPosition(entityBounds.left, wallBounds.top - entityBounds.height);
					}

					//Top collision
					else if (entityBounds.top > wallBounds.top
						&& entityBounds.top + entityBounds.height > wallBounds.top + wallBounds.height
						&& entityBounds.left < wallBounds.left + wallBounds.width
						&& entityBounds.left + entityBounds.width > wallBounds.left
						)
					{
						entity->stopVelocityY();
						entity->setPosition(entityBounds.left, wallBounds.top + wallBounds.height);
					}

					//Right collision
					if (entityBounds.left < wallBounds.left
						&& entityBounds.left + entityBounds.width < wallBounds.left + wallBounds.width
						&& entityBounds.top < wallBounds.top + wallBounds.height
						&& entityBounds.top + entityBounds.height > wallBounds.top
						)
					{
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left - entityBounds.width, entityBounds.top);
					}

					//Left collision
					else if (entityBounds.left > wallBounds.left
						&& entityBounds.left + entityBounds.width > wallBounds.left + wallBounds.width
						&& entityBounds.top < wallBounds.top + wallBounds.height
						&& entityBounds.top + entityBounds.height > wallBounds.top
						)
					{
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left + wallBounds.width, entityBounds.top);
					}
				}
			}
		}
	}
}

void Tilemap::CollisionTileDebug(bool debug)
{
	if(debug)
	{
		collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
		collisionBox.setOutlineColor(sf::Color::Red);
		collisionBox.setOutlineThickness(1.f);
	}
	else
	{
		collisionBox.setFillColor(sf::Color(0, 0, 0, 0));
	}
}

void Tilemap::update()
{

}

void Tilemap::render(sf::RenderTarget& target, bool debug)
{
	// Tile Culling System
	/*if(entity)
	{
		layer = 0;

		fromX = entity->getGridPosition(gridSizeI).x - 1;
		if (fromX < 0)
			fromX = 0;
		else if (fromX > static_cast<int>(maxSizeWorldGrid.x))
			fromX = maxSizeWorldGrid.x;

		toX = entity->getGridPosition(gridSizeI).x + 3;
		if (toX < 0)
			toX = 0;
		else if (toX > static_cast<int>(maxSizeWorldGrid.x))
			toX = maxSizeWorldGrid.x;

		fromY = entity->getGridPosition(gridSizeI).y - 1;
		if (fromY < 0)
			fromY = 0;
		else if (fromY > static_cast<int>(maxSizeWorldGrid.y))
			fromY = maxSizeWorldGrid.y;

		toY = entity->getGridPosition(gridSizeI).y + 3;
		if (toY < 0)
			toY = 0;
		else if (toY > static_cast<int>(maxSizeWorldGrid.y))
			toY = maxSizeWorldGrid.y;

		for (int x = this->fromX; x < this->toX; x++)
		{
			for (int y = this->fromY; y < this->toY; y++)
			{
				this->map[x][y][this->layer]->render(target);
				if (map[x][y][layer] != nullptr && this->map[x][y][this->layer]->getCollision())
				{
					this->collisionBox.setPosition(this->map[x][y][this->layer]->getPosition());
					target.draw(this->collisionBox);
				}
			}
		}
	}*/
	for (auto& x : map)
	{
		for (auto& y : x)
		{
			for (auto* z : y)
			{
				if (z != NULL)
				{
					z->render(target);
					if (z->getCollision())
					{
						collisionBox.setPosition(z->getPosition());
						CollisionTileDebug(debug);
						target.draw(collisionBox);
					}
				}
			}
		}
	}
}
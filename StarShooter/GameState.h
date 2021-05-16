#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "EnemySpawnerComponent.h"
#include "Player.h"
#include "State.h"
#include "PauseMenu.h"
#include "Tilemap.h"

class Entity;

class GameState :
	public State
{
private:
	//Variables
	sf::View view;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	
	Player* player;
	EnemySpawnerComponent* EnemyType1Spawner;
	PauseMenu* pause_menu;
	PlayerGUI* player_gui;

	std::list<Entity*> GameObjects;

	sf::Font font;

	Tilemap* tilemap;

	//Functions
	void initDeferredRender();
	void initView();
	void initBackground();
	void initKeybinds();
	void initTextures();
	void initPlayers();
	void initEnemies(sf::RenderWindow* window);
	void initFonts();
	void initGUI();
	void initPauseMenu();
	void initTilemap();

public:
	GameState(StateData* state_data);
	virtual ~GameState();

	//Functions
	void updateView(const float& dt);
	void updateInput(const float& dt);
	void updatePauseMenuButtons();
	void updateTileMap(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target);
};

#endif


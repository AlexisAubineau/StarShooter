#include "GameState.h"
#include "EnemyMaster.h"

//Initializer Functions
void GameState::initDeferredRender()
{
	renderTexture.create(stateData->gfxSettings->resolution.width, stateData->gfxSettings->resolution.height);
	
	renderSprite.setTexture(renderTexture.getTexture());
	renderSprite.setTextureRect(sf::IntRect(0, 0, stateData->gfxSettings->resolution.width, stateData->gfxSettings->resolution.height));
}

void GameState::initView()
{
	view.setSize(sf::Vector2f(static_cast<float>(stateData->gfxSettings->resolution.width), static_cast<float>(stateData->gfxSettings->resolution.height)));
	view.setCenter(static_cast<float>(stateData->gfxSettings->resolution.width) / 2.f, static_cast<float>(stateData->gfxSettings->resolution.height) / 2.f);
}

void GameState::initKeybinds()
{
	std::ifstream ifs(config->gameStateKeybindingPath);

	if (ifs.is_open()) {
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2) {
			keybinds[key] = supportedKeys->at(key2);
		}
	}
	ifs.close();
}

void GameState::initTextures(){}

void GameState::initPlayers()
{
	player = new Player(100, 540);
}

void GameState::initEnemies(sf::RenderWindow* m_window)
{
	EnemyType1Spawner = new EnemySpawnerComponent("ENEMY_TYPE1",
		"ENEMY",
		config->EnemyType1Sprite,
		2.f,
		0,
		0,
		0,
		0,
		90,
		60,
		10.f,
		1.f,
		5.f,
		2.0f);
	EnemyType1Spawner->window = m_window;
	EnemyType1Spawner->spawnEnemy(980, 600);
	
	EnemyType1Spawner->spawnEnemy(840,320);
	EnemyType1Spawner->spawnEnemy(980,610);
}

void GameState::initFonts()
{
	if (!font.loadFromFile(config->fontPath))
		std::cout << "ERROR::MAINMENUSTATE COULD'NT LOAD FONT" << std::endl;
}

void GameState::initGUI()
{
	player_gui = new PlayerGUI(player);
}

void GameState::initPauseMenu()
{
	pause_menu = new PauseMenu(*window, font);
	pause_menu->addButton("EXIT_STATE", 800.f, "QUIT");
}

void GameState::initTilemap()
{
	tilemap = new Tilemap(stateData->gridSize, 10, 10, config->TileSheetScene);
	tilemap->loadFromFile(config->tilemapSave);
}

//Constructors / Destructors
GameState::GameState(StateData* state_data)
	: State(state_data)
{
	initDeferredRender();
	initView();
	initKeybinds();
	initTextures();
	initPlayers();
	initEnemies(window);
	initFonts();
	initGUI();
	initPauseMenu();
	initTilemap();
}

GameState::~GameState()
{
	delete player;
	delete EnemyType1Spawner;
	delete pause_menu;
	delete tilemap;
	delete player_gui;
}

//Functions

void GameState::updateView(const float& dt)
{
	view.setCenter(std::floor(player->getPosition().x), std::floor(player->getPosition().y));
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))) && getKeytime())
		if (!paused)
			pauseState();
		else
			resumeState();
}

void GameState::updatePauseMenuButtons()
{
	if (pause_menu->isButtonPressed("EXIT_STATE"))
		endState();
}

void GameState::updateTileMap(const float& dt)
{	
	tilemap->update();

	//Update Collision Player
	tilemap->updateCollision(player, dt);

	//Update Collision for all enemies with colliding tiles
	if (EnemyType1Spawner->getEnemiesList().size() != 0)
	{
		for (EnemyMaster* element : EnemyType1Spawner->getEnemiesList())
		{
			tilemap->updateCollision(element, dt);
		}
	}

	//Update Collision Projectile Player
	player->updateProjectileCollision(tilemap, dt);

	//Update Collision Projectile Enemies
	
}

void GameState::update(const float& dt)
{
	update_mouse_position(&view);
	update_keytime(dt);
	updateInput(dt);

	player->supportedKeys = supportedKeys;
	player->keybinds = keybinds;
	player->window = window;
	
	if (!paused) // Resume update
	{
		player->update(dt);
		updateView(dt);
		EnemyType1Spawner->update(dt);
		player_gui->update(dt);
		updateTileMap(dt);
	}
	else // Pause update
	{
		pause_menu->update(mousePosWindow);
		updatePauseMenuButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	//Buffered Render
	renderTexture.clear();
	
	renderTexture.setView(view);
	
	tilemap->render(renderTexture, false);
	
	player->render(renderTexture);
	
	EnemyType1Spawner->render(renderTexture);

	
	if (paused) // Pause menu render
	{
		renderTexture.setView(renderTexture.getDefaultView());
		pause_menu->render(renderTexture);
	}
	renderTexture.setView(renderTexture.getDefaultView());
	player_gui->render(renderTexture);

	//Final render
	renderTexture.display();
	//renderSprite.setTexture(renderTexture.getTexture());
	target->draw(renderSprite);
}
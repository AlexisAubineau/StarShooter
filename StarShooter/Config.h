#pragma once
#include <string>
#include <SFML/System/String.hpp>

class Config
{
	
public:
	// Config file;
	const std::string windowSettingsPath = "Config/window.ini";
	const std::string keySupportedPath = "Config/supported_keys.ini";
	const std::string gameStateKeybindingPath = "Config/gamestate_keybinds.ini";
	const std::string mainMenuKeybindingPath = "Config/mainmenustate_keybinds.ini";
	const std::string playerKeybindingPath = "Config/player_keybinds.ini";
	const std::string editorKeybindingPath = "Config/editor_keybinds.ini";

	// Sprites
	const std::string playerIdlePath = "Resources/Images/Sprites/Player/SHIP_IDLE_SHEET.png";
	const std::string ProjectilePath = "Resources/Images/Sprites/Player/SHIP_PROJECTILE_SHEET.png";
	const std::string EnemyType1Sprite = "Resources/Images/Sprites/Enemies/ENEMY_TYPE1.png";
	const std::string EnemyType1Projectile = "Resources/Images/Sprites/Enemies/ENEMY_PROJECTILE_SHEET.png";
	const std::string TileSheetScene = "Resources/Images/Tiles/texturesheet.png";

	// Background
	const sf::String backgroundPath = "Resources/Images/Backgrounds/bg1.png";
	const sf::String backgroundGamePath = "Resources/Images/Backgrounds/game.png";
	
	// Font
	const sf::String fontPath = "Fonts/Dosis-Light.ttf";

	// Tilemap scene
	const sf::String tilemapSave = "Save/world.slmp";
	
	~Config() = default;
};

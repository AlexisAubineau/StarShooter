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

	// Sprites
	const std::string playerIdlePath = "Resources/Images/Sprites/Player/SHIP_IDLE_SHEET.png";
	const std::string ProjectilePath = "Resources/Images/Sprites/SHIP_PROJECTILE_SHEET.png";

	// Background
	const sf::String backgroundPath = "Resources/Images/Backgrounds/bg1.png";
	
	// Font
	const sf::String fontPath = "Fonts/Dosis-Light.ttf";
	
	~Config() = default;
};

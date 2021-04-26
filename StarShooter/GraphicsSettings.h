#ifndef GRAPHICSSETTINGS_H
#define GRAPHICSSETTINGS_H

#include <fstream>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/VideoMode.hpp>
#include "Config.h"

class GraphicsSettings
{
private:
	Config* config = new Config;

public:
	GraphicsSettings();
	~GraphicsSettings() = default;

	//Variables
	sf::VideoMode resolution;
	bool fullscreen;
	bool verticalSync;
	unsigned frameRateLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;
	std::string title;

	//Functions
	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);
};
#endif // GRAPHICSSETTINGS_H
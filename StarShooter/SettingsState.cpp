#include "SettingsState.h"
#include <fstream>
#include <iostream>
#include <sstream>

void SettingsState::initVariables()
{
	video_modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initBackground()
{
	background.setSize(
		sf::Vector2f
		(
			static_cast<float>(window->getSize().x),
			static_cast<float>(window->getSize().y)
		)
	);

	background.setFillColor(sf::Color::Black);
}

void SettingsState::initFonts()
{
	if (!font.loadFromFile(config->fontPath))
		std::cout << "ERROR::MAINMENUSTATE COULD'NT LOAD FONT" << std::endl;
}

void SettingsState::initKeybinds()
{
	std::ifstream ifs(config->mainMenuKeybindingPath);

	if (ifs.is_open()) {
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2) {
			keybinds[key] = supportedKeys->at(key2);
		}
	}
	ifs.close();
}

void SettingsState::initGUI()
{
	buttons["BACK"] = new gui::Button(
		gfxSettings.resolution.width - 400, gfxSettings.resolution.height - 200, 250.f, 50.f,
		&font, "Back", 50,
		sf::Color(255, 255, 255, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	buttons["APPLY"] = new gui::Button(
		gfxSettings.resolution.width - 200, gfxSettings.resolution.height - 200, 250.f, 50.f,
		&font, "Apply", 50,
		sf::Color(255, 255, 255, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	std::vector<std::string> video_modes_str;
	for(auto &i : video_modes)
	{
		video_modes_str.push_back(std::to_string(i.width) + "x" + std::to_string(i.height));
	}
	
	dropDownLists["RESOLUTION"] = new gui::DropDownList(880, 450, 450, 50, font, video_modes_str.data(), video_modes_str.size());
}

void SettingsState::initText()
{
	optionsText.setFont(font);

	optionsText.setPosition(sf::Vector2f(100.f, 450.f));
	optionsText.setCharacterSize(40);
	optionsText.setFillColor(sf::Color(255, 255, 255, 200));

	
	optionsText.setString(
		"Resolution \n\nFullscreen \n\nVSync \n\nAntialiasing \n\n"
	);
}

SettingsState::SettingsState(sf::RenderWindow* window, GraphicsSettings& gfxSettings, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states), gfxSettings(gfxSettings)
{
	initVariables();
	initBackground();
	initFonts();
	initKeybinds();
	initGUI();
	initText();
}

SettingsState::~SettingsState()
{
	//Buttons
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); it++) {
		delete it->second;
	}

	//DropDownlists
	auto it2 = dropDownLists.begin();
	for (it2 = dropDownLists.begin(); it2 != dropDownLists.end(); it2++) {
		delete it2->second;
	}
}

//Accessors

//Functions
void SettingsState::updateInput(const float& dt)
{

}

void SettingsState::updateGUI(const float& dt)
{
	/*Update all the buttons in the state and handles their functionality*/
	//Buttons
	for (auto& it : buttons)
	{
		it.second->update(this->mousePosView);
	}
	
	//Quit the game 
	if (buttons["BACK"]->isPressed()) 
	{
		endState();
	}
	
	//Apply selected settings
	if (buttons["APPLY"]->isPressed()) 
	{
		gfxSettings.resolution = video_modes[dropDownLists["RESOLUTION"]->getActiveElementId()];
		optionsText.setPosition(sf::Vector2f(100, (static_cast<float>(gfxSettings.resolution.height) / 2) - 100));
		window->create(gfxSettings.resolution, gfxSettings.title, sf::Style::Default);
	}

	//DropDownList
	for (auto& it : dropDownLists)
	{
		it.second->update(this->mousePosView, dt);
	}
}

void SettingsState::update(const float& dt)
{
	update_mouse_position();
	updateInput(dt);
	updateGUI(dt);
}

void SettingsState::renderGUI(sf::RenderTarget* target)
{
	//Buttons
	for (auto& it : buttons)
	{
		it.second->render(target);
	}
	//DropDownLists
	for (auto& it : dropDownLists)
	{
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	target->draw(background);

	renderGUI(target);

	target->draw(optionsText);
}
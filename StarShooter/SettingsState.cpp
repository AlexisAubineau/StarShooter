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

	/*if (!backgroundTexture.loadFromFile(config->backgroundPath))
		std::cout << "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE" << std::endl;

	background.setTexture(&backgroundTexture);*/
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
		1500.f, 880.f, 250.f, 50.f,
		&font, "Back", 50,
		sf::Color(255, 255, 255, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	buttons["APPLY"] = new gui::Button(
		1300.f, 880.f, 250.f, 50.f,
		&font, "Apply", 50,
		sf::Color(255, 255, 255, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	std::vector<std::string> video_modes_str;
	for(auto &i : video_modes)
	{
		video_modes_str.push_back(std::to_string(i.width) + "x" + std::to_string(i.height));
	}
	
	dropDownLists["RESOLUTION"] = new gui::DropDownList(800, 450, 200, 50, font, video_modes_str.data(), video_modes_str.size());
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

SettingsState::SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
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
		//TEST Remove later !! 
		window->create(video_modes[dropDownLists["RESOLUTION"]->getActiveElementId()], "Test", sf::Style::Default);
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

	//REMOVE LATER !!
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x - 20, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}
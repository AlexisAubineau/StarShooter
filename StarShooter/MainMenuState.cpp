#include "MainMenuState.h"

#include "EditorSate.h"

//Initialiazer fuctions
void MainMenuState::initVariables()
{
}

void MainMenuState::initBackground()
{
	background.setSize(
		sf::Vector2f
		(
			static_cast<float>(window->getSize().x), 
			static_cast<float>(window->getSize().y)
		)
	);
	
	if (!backgroundTexture.loadFromFile(config->backgroundPath)) {
		std::cout << "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE" << std::endl;
	}

	background.setTexture(&backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!font.loadFromFile(config->fontPath)) {
		std::cout << "ERROR::MAINMENUSTATE COULD'NT LOAD FONT" << std::endl;
	}
}

void MainMenuState::initKeybinds()
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

void MainMenuState::initButtons()
{
	buttons["GAME_STATE"] = new gui::Button(
		100.f, 480.f, 250.f, 65.f,
		&font, "Play", 50,
		sf::Color(255, 255, 255, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
	
	buttons["SETTINGS_STATE"] = new gui::Button(
		100.f, 580.f, 250.f, 65.f,
		&font, "Settings", 50,
		sf::Color(255, 255, 255, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["EDITOR_STATE"] = new gui::Button(
		100.f, 680.f, 250.f, 65.f,
	    &font, "Editor", 50,
		sf::Color(255, 255, 255, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	buttons["EXIT_STATE"] = new gui::Button(
		100.f, 880.f, 250.f, 65.f,
		&font, "Quit", 50,
		sf::Color(255, 255, 255, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

MainMenuState::MainMenuState(StateData* state_data)
	: State(state_data)
{
	initVariables();
	initBackground();
	initFonts();
	initKeybinds();
	initButtons();
}

MainMenuState::~MainMenuState()
{
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); it++) {
		delete it->second;
	}
}

void MainMenuState::updateInput(const float& dt)
{
	
}

void MainMenuState::updateButtons()
{
	/*Update all the buttons in the state and handles their functionality*/
	for (auto &it : buttons)
	{
		it.second->update(mousePosWindow);
	}

	//New Game
	if (buttons["GAME_STATE"]->isPressed()) {
		states->push(new GameState(stateData));
	}

	//Editor
	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->states->push(new EditorState(stateData));
	}

	if (buttons["SETTINGS_STATE"]->isPressed())
	{
		/* You could activate him to see what it is and set some value to test like Resolution and fullscreen
		 * but so many work on ratio to do and no enough time to made it ^^'
		 */
		
		//states->push(new SettingsState(stateData));
	}

	//Quit the game 
	if (buttons["EXIT_STATE"]->isPressed()) {
		endState();
	}
}

void MainMenuState::update(const float& dt)
{
	update_mouse_position();
	updateInput(dt);

	updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	target->draw(background);
	
	renderButtons(target);
}
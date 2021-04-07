#include "Game.h"

//Static functions

//Initializer functions

void Game::initVariables()
{
	window = NULL;
    fullscreen = false;
    dt = 0.f;
}

void Game::initWindow()
{
    /*Create a SFML Window using option from a window.ini file.*/
    std::ifstream ifs(config->windowSettingsPath);
    videoModes = sf::VideoMode::getFullscreenModes();

    std::string title = "None";
    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
    bool fullscreen = false;
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;
    unsigned antialiasing_level = 0;
	
	if (ifs.is_open())
	{
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> fullscreen;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
        ifs >> antialiasing_level;
	}

    ifs.close();
	
	windowSettings.antialiasingLevel = antialiasing_level;
    if(fullscreen)
	    window = new sf::RenderWindow (window_bounds, title, sf::Style::Fullscreen, windowSettings);
    else
        window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
    window->setFramerateLimit(framerate_limit);
    window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initKeys()
{
    std::ifstream ifs(config->keySupportedPath);

    if (ifs.is_open()) {
        std::string key = "";
        int key_value = 0;

        while (ifs >> key >> key_value) {
            supportedKeys[key] = key_value;
        }
    }
    ifs.close();

    //DEBUG REMOVE LATER !!
    for (auto i : supportedKeys)
        std::cout << i.first << " " << i.second << "\n";
}

void Game::initStates()
{
    states.push(new MainMenuState(window, &supportedKeys, &states));
}

//Contructors/Deconstructors
Game::Game()
{
    initWindow();
    initKeys();
    initStates();
}

Game::~Game()
{
	delete window;

    while (!states.empty()) {
        delete states.top();
        states.pop();
    }
}


//Functions

void Game::endApplication()
{
    std::cout << "Ending Application!" << "\n";
}

void Game::updateDt()
{
	/*Updates the dt variable with the time it takes to update and render one frame. */
	
    dt = dtClock.restart().asSeconds() ;
}

void Game::updateSFMLEvents()
{
    while (window->pollEvent(sfEvent))
    {
        if (sfEvent.type == sf::Event::Closed)
            window->close();
    }
}

void Game::update()
{
    this->updateSFMLEvents();

    if (!states.empty()) {
        states.top()->update(dt);

        if (states.top()->getQuit()) {
            
            states.top()->endState();
            delete states.top();
            states.pop();
        }
    }
    //Application end
    else {
        endApplication();
        window->close();
    }
}

void Game::render()
{
    window->clear();

	//Render items
    if (!states.empty())
        states.top()->render(window);
	
    this->window->display();
}

void Game::run()
{
    while (window->isOpen())
    {
        updateDt(); 
		update();
		render();
    }
}

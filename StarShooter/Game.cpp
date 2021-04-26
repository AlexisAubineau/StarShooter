#include "Game.h"

//Static functions

//Initializer functions

void Game::initVariables()
{
	window = NULL;
    dt = 0.f;
}

void Game::initGraphicsSettings()
{
    gfxSettings.loadFromFile(config->windowSettingsPath);
}

void Game::initWindow()
{
    if(gfxSettings.fullscreen)
	    window = new sf::RenderWindow (
            gfxSettings.resolution, 
            gfxSettings.title, 
            sf::Style::Fullscreen, 
            gfxSettings.contextSettings);
    else
        window = new sf::RenderWindow(
            gfxSettings.resolution, 
            gfxSettings.title, 
            sf::Style::Titlebar | sf::Style::Close, 
            gfxSettings.contextSettings);
    window->setFramerateLimit(gfxSettings.frameRateLimit);
    window->setVerticalSyncEnabled(gfxSettings.verticalSync);
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
    states.push(new MainMenuState(window, gfxSettings, &supportedKeys, &states));
}

//Contructors/Deconstructors
Game::Game()
{
    initVariables();
    initGraphicsSettings();
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

#include "EditorSate.h"
#include <fstream>
#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>
#include <sstream>

//Initializer functions
void EditorState::initVariables()
{
	texture_rect = sf::IntRect(0, 0, static_cast<int>(stateData->gridSize), static_cast<int>(stateData->gridSize));
	collision = false;
	type = DEFAULT;
	cameraSpeed = 100.f;
}

void EditorState::initView()
{
	view.setSize(sf::Vector2f(static_cast<float>(stateData->gfxSettings->resolution.width), static_cast<float>(stateData->gfxSettings->resolution.height)));
	view.setCenter(static_cast<float>(stateData->gfxSettings->resolution.width) / 2.f, static_cast<float>(stateData->gfxSettings->resolution.height) / 2.f);
}

void EditorState::initBackground()
{

}

void EditorState::initFonts()
{
	if (!font.loadFromFile(config->fontPath))
	{
		throw("ERROR::EDITORSTATE::COULD NOT LOAD FONT");
	}
}

void EditorState::initText()
{
	cursorText.setFont(font);
	cursorText.setFillColor(sf::Color::White);
	cursorText.setCharacterSize(12);
}

void EditorState::initKeybinds()
{
	std::ifstream ifs(config->editorKeybindingPath);

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			keybinds[key] = supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void EditorState::initPauseMenu()
{
	pause_menu = new PauseMenu(*window, font);
	pause_menu->addButton("SAVE_FILE", 400.f, "SAVE");
	pause_menu->addButton("LOAD_FILE", 500.f, "LOAD");
	pause_menu->addButton("EXIT_STATE", 800.f, "QUIT");
}

void EditorState::initButtons()
{
	
}

void EditorState::initGui()
{
	sidebar.setSize(sf::Vector2f(80.f, static_cast<float>(stateData->gfxSettings->resolution.height)));
	sidebar.setFillColor(sf::Color(50, 50, 100));
	sidebar.setOutlineColor(sf::Color(200, 200, 150));
	sidebar.setOutlineThickness(1.f);
	
	selectorRect.setSize(sf::Vector2f(stateData->gridSize, stateData->gridSize));
	
	selectorRect.setFillColor(sf::Color(255,255,255,150));
	selectorRect.setOutlineThickness(1.f);
	selectorRect.setOutlineColor(sf::Color::Green);

	selectorRect.setTexture(tilemap->getTileSheet());
	selectorRect.setTextureRect(texture_rect);

	textureSelector = new gui::TextureSelector(5.f, 20.f, 500.f, 500.f,stateData->gridSize, tilemap->getTileSheet(), font, "Tiles");
	
}

void EditorState::initTilemap()
{
	tilemap = new Tilemap(stateData->gridSize, 10, 10, config->TileSheetScene);
}

EditorState::EditorState(StateData* state_data)
	: State(state_data)
{
	initVariables();
	initView();
	initBackground();
	initFonts();
	initText();
	initKeybinds();
	initPauseMenu();
	initButtons();
	initTilemap();
	initGui();
}

EditorState::~EditorState()
{
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
	
	delete pause_menu;
	delete tilemap;
	delete textureSelector;
}

//Functions

void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))) && getKeytime())
		if (!paused)
			pauseState();
		else
			resumeState();
}

void EditorState::updateEditorInput(const float& dt)
{
	// Move view
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAMERA_UP"))))
	{
		view.move(0.f, -cameraSpeed * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAMERA_DOWN"))))
	{
		view.move(0.f, cameraSpeed * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAMERA_LEFT"))))
	{
		view.move(-cameraSpeed * dt, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAMERA_RIGHT"))))
	{
		view.move(cameraSpeed * dt, 0.f);
	}
	
	//Add a tile in tilemap
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && getKeytime())
	{
		if(!sidebar.getGlobalBounds().contains(sf::Vector2f(mousePosWindow)))
		{
			if (!textureSelector->getActive())
			{
				tilemap->addTile(mousePosGrid.x, mousePosGrid.y, 0, texture_rect, collision, type);
			}
			else
			{
				texture_rect = textureSelector->getTextureRect();
			}
		}
	}
	//Remove a tile in tilemap
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && getKeytime())
	{
		if (!sidebar.getGlobalBounds().contains(sf::Vector2f(mousePosWindow)))
		{
			if (!textureSelector->getActive())
			{
				tilemap->removeTile(mousePosGrid.x, mousePosGrid.y, 0);
			}
		}
	}

	// Toggle collision
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("TOGGLE_COLLISION"))) && getKeytime())
	{
		if (collision)
			collision = false;
		else
			collision = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("TYPE_INC"))) && getKeytime())
	{
		++type;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("TYPE_DEC"))) && getKeytime())
	{
		if(type > 0)
			--type;
	}
}

void EditorState::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionlaity.*/

	for (auto& it : buttons)
	{
		it.second->update(mousePosWindow);
	}
}

void EditorState::updateGui(const float& dt)
{
	textureSelector->update(mousePosWindow, dt);

	if(!textureSelector->getActive())
	{
		selectorRect.setTextureRect(texture_rect);
		selectorRect.setPosition(mousePosGrid.x * stateData->gridSize, mousePosGrid.y * stateData->gridSize);
	}

	//Update Text near cursor
	cursorText.setPosition(mousePosView.x + 100.f, mousePosView.y - 50.f);

	/* Info text for mouse position / mouse position on grid / Shadow of sprite before was placed */
	std::stringstream ss;
	ss << mousePosView.x << " " << mousePosView.y <<
		"\n" << mousePosGrid.x << " " << mousePosGrid.y <<
		"\n" << texture_rect.left << " " << texture_rect.top <<
		"\n" << "Collision: " << collision << 
		"\n" << "Type: " << type;
	cursorText.setString(ss.str());
}

void EditorState::updatePauseMenuButtons()
{
	if (pause_menu->isButtonPressed("EXIT_STATE"))
		endState();
	if (pause_menu->isButtonPressed("SAVE_FILE"))
		tilemap->saveToFile(config->tilemapSave);
	if (pause_menu->isButtonPressed("LOAD_FILE"))
		tilemap->loadFromFile(config->tilemapSave);
}

void EditorState::update(const float& dt)
{
	update_mouse_position(&view);
	update_keytime(dt);
	updateInput(dt);
	
	if(!paused)
	{
		updateButtons();
		updateGui(dt);
		updateEditorInput(dt);
	}
	else
	{
		pause_menu->update(mousePosWindow);
		updatePauseMenuButtons();
	}
}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : buttons)
	{
		it.second->render(&target);
	}
}

void EditorState::renderGui(sf::RenderTarget& target)
{
	target.setView(window->getDefaultView());
	target.draw(sidebar);
	
	if(!textureSelector->getActive())
	{
		target.setView(view);
		target.draw(selectorRect);
	}
		
	target.setView(window->getDefaultView());
	textureSelector->render(target);

	target.setView(view);
	target.draw(cursorText);

	
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	target->setView(view);
	
	tilemap->render(*target, true);

	target->setView(window->getDefaultView());
	
	renderButtons(*target);
	renderGui(*target);

	if (paused) // Pause menu render
	{
		target->setView(window->getDefaultView());
		pause_menu->render(*target);
	}
}

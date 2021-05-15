#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "Tilemap.h"

class State;
class Gui;
class PauseMenu;
class Tilemap;

class EditorState :
	public State
{
private:
	//Variables
	sf::View view;
	float cameraSpeed;
	
	sf::Font font;
	sf::Text cursorText;
	std::map<std::string, gui::Button*> buttons;
	PauseMenu* pause_menu;

	Tilemap* tilemap;

	sf::RectangleShape sidebar;

	sf::IntRect texture_rect;
	sf::RectangleShape selectorRect;

	gui::TextureSelector* textureSelector;

	bool collision;
	short type;

	//Functions
	void initVariables();
	void initView();
	void initBackground();
	void initFonts();
	void initText();
	void initKeybinds();
	void initButtons();
	void initPauseMenu();
	void initGui();
	void initTilemap();

public:
	EditorState(StateData* state_data);
	virtual ~EditorState();

	//Functions
	void updateInput(const float& dt);
	void updateEditorInput(const float& dt);
	void updateButtons();
	void updateGui(const float& dt);
	void updatePauseMenuButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};

#endif

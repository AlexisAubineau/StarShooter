#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "Gui.h"
#include "State.h"
#include "GraphicsSettings.h"

class SettingsState :
	public State
{
private:
	//variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::DropDownList*> dropDownLists;

	sf::Text optionsText;

	std::vector<sf::VideoMode> video_modes;
	sf::Uint32 screen_style;
	
	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initGUI();
	void initButtons();
	void initDropDownLists();
	void initText();
	
public:
	SettingsState(StateData* state_data);
	virtual ~SettingsState();

	//Accessors

	//Functions
	void updateInput(const float& dt);
	void updateGUI(const float& dt);
	void update(const float& dt);
	void renderGUI(sf::RenderTarget* target = NULL);
	void render(sf::RenderTarget* target = NULL);
};

#endif // SETTINGSSTATE_H
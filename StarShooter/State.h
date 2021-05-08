#ifndef STATE_H
#define STATE_H

#include<stack>
#include<map>


#include "Config.h"
#include"SFML\Graphics.hpp"

class State
{
private:

protected:
	std::stack<State*>* states;
	sf::RenderWindow* window;
	bool quit;
	bool paused;
	float keytime;
	float keytimeMax;
	float ratio;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	
	//Ressources
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;

	//Functions
	virtual void initKeybinds() = 0;

public:

	Config* config = new Config;
	
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	//Accessors
	const bool& getQuit() const;
	const bool getKeytime();

	//Functions
	virtual void endState();
	void pauseState();
	void resumeState();

	virtual void update_mouse_position();
	virtual void update_keytime(const float& dt);
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;
};
#endif
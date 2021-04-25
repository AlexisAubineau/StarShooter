#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	: font(font)
{
	//Init Background
	background.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x), 
			static_cast<float>(window.getSize().y)
		)
	);
	
	background.setFillColor(sf::Color(20, 20, 20, 100));

	// Init Container
	container.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x) / 4.f,
			static_cast<float>(window.getSize().y) - 100.f
		)
	);

	container.setFillColor(sf::Color(20, 20, 20, 200));
	container.setPosition(
		static_cast<float>(window.getSize().x) / 2.f - container.getSize().x / 2.f, 
		30.f
	);

	//Init Text
	menuText.setFont(font);
	menuText.setFillColor(sf::Color(255, 255, 255, 200));
	menuText.setCharacterSize(60);
	menuText.setString("PAUSED");
	menuText.setPosition(
		container.getPosition().x + container.getSize().x / 2.f - menuText.getGlobalBounds().width / 2.f, 
		container.getPosition().y + 40.f
	);
}

PauseMenu::~PauseMenu()
{
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); it++) {
		delete it->second;
	}
}

std::map<std::string, gui::Button*>& PauseMenu::getButtons()
{
	return buttons;
}

// Functions
const bool PauseMenu::isButtonPressed(const std::string key)
{
	return buttons[key]->isPressed();
}

void PauseMenu::addButton(const std::string key, float y, const std::string text)
{
	float width = 250.f;
	float height = 50.f;
	float x = container.getPosition().x + container.getSize().x / 2.f - width / 2.f;
	buttons[key] = new gui::Button(
		x, y, width, height,
		&font, text, 50,
		sf::Color(255, 255, 255, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

void PauseMenu::update(const sf::Vector2f& mousePos)
{
	for (auto &i : buttons)
	{
		i.second->update(mousePos);
	}
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(background);
	target.draw(container);

	for (auto &i: buttons)
	{
		i.second->render(&target);
	}

	target.draw(menuText);
}

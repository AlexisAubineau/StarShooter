#ifndef GUI_H
#define GUI_H

#include"SFML\Graphics.hpp"
#include <vector>

enum button_states{ BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

namespace gui
{
	class Button
	{
	private:
		short unsigned buttonState;
		short unsigned id;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;

	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color, 
			sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent,
			short unsigned id = 0);
		virtual ~Button();

		//Accessors
		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned& getId() const;

		//Modifier
		void setText(const std::string text);
		void setId(const short unsigned id);

		//Functions
		void update(const sf::Vector2i& mousePosWindow);
		void render(sf::RenderTarget* target);
	};

	class DropDownList
	{
	private:
		float keytime;
		float keytimeMax;
		sf::Font& font;
		gui::Button* activeElement;
		std::vector<gui::Button*> list;
		bool showList;
	
	public:
		DropDownList(float x, float y, float width, float height, sf::Font& font, std::string m_list[], unsigned nrOfElements, unsigned default_index = 0);
		virtual ~DropDownList();

		//Accessors
		const bool getKeyTime();
		const unsigned short& getActiveElementId() const;

		//Functions
		void updateKeytime(const float& dt);
		void update(const sf::Vector2i& mousePosWindow, const float& dt);
		void render(sf::RenderTarget* target);
	};
	
	class TextureSelector
	{
	private:
		float keytime;
		const float keytimeMax;
		float gridSize;
		bool active;
		bool hidden;
		Button* hide_btn;
		
		sf::RectangleShape bound;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::Vector2u mousePosGrid;
		sf::IntRect textureRect;
		

	public:
		TextureSelector(float x, float y, float width, float height, float m_gridSize, const sf::Texture* texture_sheet, sf::Font& font, std::string text);
		~TextureSelector();

		//Accessors
		const bool& getActive() const;
		const sf::IntRect& getTextureRect() const;
		const bool getKeyTime();

		//Functions
		void updateKeytime(const float& dt);
		void update(const sf::Vector2i& mousePosWindow, const float& dt);
		void render(sf::RenderTarget& target);
	};
}
#endif
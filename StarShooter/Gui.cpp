#include "Gui.h"

gui::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color, 
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
	sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
	short unsigned m_id)
{
	buttonState = BTN_IDLE;
	id = m_id;

	shape.setPosition(sf::Vector2f(x, y));
	shape.setSize(sf::Vector2f(width, height));
	shape.setFillColor(idle_color);
	shape.setOutlineThickness(1.f);
	shape.setOutlineColor(outline_idle_color);

	this->font = font;
	
	this->text.setFont(*font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		shape.getPosition().y
	);
	
	textIdleColor = text_idle_color;
	textHoverColor = text_hover_color;
	textActiveColor = text_active_color;

	idleColor = idle_color;
	hoverColor = hover_color;
	activeColor = active_color;
	
	outlineIdleColor = outline_idle_color;
	outlineHoverColor = outline_hover_color;
	outlineActiveColor = outline_active_color;
}

gui::Button::~Button()
{

}

//Accessors

const bool gui::Button::isPressed() const
{
	if (buttonState == BTN_ACTIVE)
		return true;

	return false;
}

const std::string gui::Button::getText() const
{
	return text.getString();
}

const unsigned short& gui::Button::getId() const
{
	return id;
}

//Modifiers

void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void gui::Button::setId(const unsigned short id)
{
	this->id = id;
}

//Functions

void gui::Button::update(const sf::Vector2i& mousePosWindow)
{
	/*Update the booleans for hover and pressed*/

	//Idle
	buttonState = BTN_IDLE;

	//Hover
	if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow))){
		buttonState = BTN_HOVER;

		//Active
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			buttonState = BTN_ACTIVE;
		}
	}

	switch (buttonState)
	{
	case BTN_IDLE:
		shape.setFillColor(idleColor);
		text.setFillColor(textIdleColor);
		shape.setOutlineColor(outlineIdleColor);
		break;

	case BTN_HOVER:
		shape.setFillColor(hoverColor);
		text.setFillColor(textHoverColor);
		shape.setOutlineColor(outlineHoverColor);
		break;

	case BTN_ACTIVE:
		shape.setFillColor(activeColor);
		text.setFillColor(textActiveColor);
		shape.setOutlineColor(outlineActiveColor);
		break;

	default:
		shape.setFillColor(sf::Color::Red);
		text.setFillColor(sf::Color::Blue);
		shape.setOutlineColor(sf::Color::Green);
		break;
	}
}

void gui::Button::render(sf::RenderTarget* target)
{
	target->draw(shape);
	target->draw(text);
}

/**************************************
 *
 *	DropDownList
 *	
 **************************************/


gui::DropDownList::DropDownList(float x, float y, float width, float height, sf::Font& font, std::string m_list[], unsigned nrOfElements, unsigned default_index)
	: font(font), showList(false) , keytimeMax(1.f), keytime(0.f)
{
	activeElement = new gui::Button(
		x, y, width, height,
		&font, m_list[default_index], 24,
		sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 200)
	);

	for (unsigned short i = 0; i < nrOfElements; i++)
	{
		list.push_back(new gui::Button(
			x, y + ((i+1) * height), width, height,
			&font, m_list[i], 24,
			sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
			sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
			sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0),
			i
		));
	}
}

gui::DropDownList::~DropDownList()
{
	delete activeElement;
	for (auto& i : list)
	{
		delete i;
	}
}

//Accessors
const bool gui::DropDownList::getKeyTime()
{
	if(keytime >= keytimeMax)
	{
		keytime = 0.f;	
		return true;
	}
	return false;
}

const unsigned short& gui::DropDownList::getActiveElementId() const
{
	return activeElement->getId();
}

//Functions
void gui::DropDownList::updateKeytime(const float& dt)
{
	if (keytime < keytimeMax)
		keytime += 10.f * dt;
}

void gui::DropDownList::update(const sf::Vector2i& mousePosWindow, const float& dt)
{
	updateKeytime(dt);
	
	activeElement->update(mousePosWindow);

	//Show and hide list
	if (activeElement->isPressed() && getKeyTime())
	{
		if (showList)
			showList = false;
		else
			showList = true;
	}
	
	if(showList)
	{
		for (auto& i : list)
		{
			i->update(mousePosWindow);

			if(i->isPressed() && getKeyTime())
			{
				showList = false;
				activeElement->setText(i->getText());
				activeElement->setId(i->getId());
			}
		}
	}
}

void gui::DropDownList::render(sf::RenderTarget* target)
{
	activeElement->render(target);
	if (showList)
	{
		for (auto& i : list)
		{
			i->render(target);
		}
	}
}

/**************************************
 *
 *	Texture Selector
 *
 **************************************/

gui::TextureSelector::TextureSelector(float x, float y, float width, float height, float m_gridSize, const sf::Texture* texture_sheet, sf::Font& font, std::string text)
	: keytimeMax(1.f), keytime(0.f)
{
	gridSize = m_gridSize;
	active = false;
	hidden = false;
	float offset = 100.f;
	
	bound.setSize(sf::Vector2f(width, height));
	bound.setPosition(x + offset, y);
	bound.setFillColor(sf::Color(50, 50, 50, 100));
	bound.setOutlineThickness(1.f);
	bound.setOutlineColor(sf::Color(255, 255, 255, 200));

	sheet.setTexture(*texture_sheet);
	sheet.setPosition(x + offset, y);

	if(sheet.getGlobalBounds().width > bound.getGlobalBounds().width)
	{
		sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(bound.getGlobalBounds().width), static_cast<int>(sheet.getGlobalBounds().height)));
	}
	if (sheet.getGlobalBounds().height > bound.getGlobalBounds().height)
	{
		sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(bound.getGlobalBounds().height), static_cast<int>(sheet.getGlobalBounds().width)));
	}

	selector.setPosition(x + offset, y);
	selector.setSize(sf::Vector2f(gridSize, gridSize));
	selector.setFillColor(sf::Color::Transparent);
	selector.setOutlineThickness(1.f);
	selector.setOutlineColor(sf::Color::Red);

	textureRect.width = static_cast<int>(gridSize);
	textureRect.height = static_cast<int>(gridSize);

	hide_btn = new gui::Button(
		x, y, 70.f, 45.f,
		&font, text, 35,
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 250), sf::Color(255, 255, 255, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50)
	);
}

gui::TextureSelector::~TextureSelector()
{
	delete hide_btn;
}

// Accessors

const bool& gui::TextureSelector::getActive() const
{
	return active;
}

const sf::IntRect& gui::TextureSelector::getTextureRect() const
{
	return textureRect;
}

const bool gui::TextureSelector::getKeyTime()
{
	if (keytime >= keytimeMax)
	{
		keytime = 0.f;
		return true;
	}
	return false;
}

//Functions

void gui::TextureSelector::updateKeytime(const float& dt)
{
	if (keytime < keytimeMax)
		keytime += 10.f * dt;
}

void gui::TextureSelector::update(const sf::Vector2i& mousePosWindow, const float& dt)
{
	updateKeytime(dt);
	hide_btn->update(mousePosWindow);

	if(hide_btn->isPressed() && getKeyTime())
	{
		if (hidden)
			hidden = false;
		else
			hidden = true;
	}
	
	if (!hidden)
	{
		//Update GUI Texture Selector
		if (bound.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
			active = true;
		else
			active = false;

		if (active)
		{
			mousePosGrid.x = (mousePosWindow.x - static_cast<int>(bound.getPosition().x)) / static_cast<unsigned>(gridSize);
			mousePosGrid.y = (mousePosWindow.y - static_cast<int>(bound.getPosition().y)) / static_cast<unsigned>(gridSize);

			selector.setPosition(bound.getPosition().x + mousePosGrid.x * gridSize, bound.getPosition().y + mousePosGrid.y * gridSize);
		}

		//Update TextureRect
		textureRect.left = static_cast<int>(selector.getPosition().x - bound.getPosition().x);
		textureRect.top = static_cast<int>(selector.getPosition().y - bound.getPosition().y);

	}
}

void gui::TextureSelector::render(sf::RenderTarget& target)
{
	if(!hidden)
	{
		target.draw(bound);
		target.draw(sheet);

		if (active)
			target.draw(selector);
	}
	
	hide_btn->render(&target);
}


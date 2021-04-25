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
		shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
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

void gui::Button::update(const sf::Vector2f& mousePos)
{
	/*Update the booleans for hover and pressed*/

	//Idle
	buttonState = BTN_IDLE;

	//Hover
	if (shape.getGlobalBounds().contains(mousePos)) {
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

void gui::DropDownList::update(const sf::Vector2f& mousePos, const float& dt)
{
	updateKeytime(dt);
	
	activeElement->update(mousePos);

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
			i->update(mousePos);

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

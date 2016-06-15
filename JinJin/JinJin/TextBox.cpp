#include "TextBox.h"
#include <iostream>

TextBox::TextBox(const sf::String &str,const sf::Font &f, const sf::Vector2f v, const sf::Vector2f origin) : 
	font (f),
	box(v), 
	draw(false)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(bounds.width / 2.f , bounds.height / 2.f + 800);

	box.setPosition(400, 400);
	text.setFont(font);
	text.setPosition(100, 100);
	text.setCharacterSize(800);
	box.setFillColor(sf::Color::Black);
	box.setOutlineThickness(5);
	box.setOutlineColor(sf::Color::White);
}

void TextBox::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const{

	if (draw)
	{
		//target.draw(box, states);
		target.draw(text, states);
	}
	
}

void TextBox::displayText(sf::String str, sf::Vector2f pos)
{
	text.setString(str);
	text.setPosition(pos);
}

unsigned int TextBox::getCategory() const
{
	return Category::Text;
}

void TextBox::setDrawing(bool val)
{
	draw = val;
}

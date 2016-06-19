#include "TextBox.h"
#include <iostream>

TextBox::TextBox(const sf::Font &f, sf::Color color) :
	font (f), 
	draw(false)
{

	text.setFont(font);
	text.setColor(color);

}

void TextBox::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const{

	if (draw)
	{
		target.draw(text, states);

	}
}

void TextBox::displayText(sf::String str, int size)
{
	text.setString(str);
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(bounds.width / 2.f + size*static_cast<float>(0.5), bounds.height / 2.f + size*static_cast<float>(0.75));
	text.setCharacterSize(size);
}

unsigned int TextBox::getCategory() const
{
	return Category::Text;
}

void TextBox::setDrawing(bool val)
{
	draw = val;

}

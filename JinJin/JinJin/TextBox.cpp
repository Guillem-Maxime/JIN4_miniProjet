#include "TextBox.h"
#include <iostream>

TextBox::TextBox(const sf::Font &f, sf::Color color) :
	font (f), 
	draw(false)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(bounds.width / 2.f + 400, bounds.height / 2.f + 600);

	text.setFont(font);
	text.setPosition(100, 100);
	text.setColor(color);
	text.setCharacterSize(800);

}

void TextBox::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const{

	if (draw)
	{
		//target.draw(box, states);
		target.draw(text, states);

	}
}

void TextBox::displayText(sf::String str)
{
	text.setString(str);
}

unsigned int TextBox::getCategory() const
{
	return Category::Text;
}

void TextBox::setDrawing(bool val)
{
	draw = val;

}

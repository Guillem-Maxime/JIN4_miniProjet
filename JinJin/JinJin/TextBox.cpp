#include "TextBox.h"
#include <iostream>

TextBox::TextBox(const sf::String &str,const sf::Font &f, const sf::Vector2f v, const sf::Vector2f origin) : 
	font (f),
	text(str, font,20),
	box(v)
{
	//text.setOrigin(origin);
	//box.setOrigin(origin);
	box.setFillColor(sf::Color::Black);
	box.setOutlineThickness(5);
	box.setOutlineColor(sf::Color::White);
}

void TextBox::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const{

	target.draw(box, states);
	target.draw(text, states);
	
}

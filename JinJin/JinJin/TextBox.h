#pragma once
#include "SceneNode.h"

class TextBox : public SceneNode {
public:
	TextBox(const sf::String &str, const sf::Font &f, const sf::Vector2f v, const sf::Vector2f origin);
	void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;


private:
	sf::Text text;
	sf::Font font;
	sf::RectangleShape box;
};
#pragma once
#include "SceneNode.h"

class TextBox : public SceneNode {
public:
	TextBox(const sf::Font &f, sf::Color color);
	void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

	void displayText(sf::String str, int size);

	unsigned int getCategory() const;

	void setDrawing(bool val);

private:
	sf::Text text;
	sf::Font font;
	sf::RectangleShape box;

	bool draw;
};
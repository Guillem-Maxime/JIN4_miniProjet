#pragma once
#include "SceneNode.h"

/* Gère l'objet s'occupant du background */
class SpriteNode : public SceneNode
{
public:
	explicit SpriteNode(const sf::Texture &texture);
	SpriteNode(const sf::Texture &texture, const sf::IntRect &rect);

private:
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

	sf::Sprite sprite;

};


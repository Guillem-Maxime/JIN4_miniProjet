#pragma once
#include "SceneNode.h"
#include "TextureHolder.h"

class Spikes : public SceneNode {
public:
	Spikes(const TextureHolder& textures);
	Spikes(const sf::Texture & texture, const sf::IntRect & rect);
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual unsigned int getCategory() const;

	virtual sf::FloatRect getBoundingRect() const;

private:
	sf::Sprite sprite;

};
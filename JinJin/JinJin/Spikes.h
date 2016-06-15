#pragma once
#include "SceneNode.h"
#include "TextureHolder.h"

class Spikes : public SceneNode {
public:
	Spikes(const TextureHolder& textures);
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
	//virtual unsigned int getCategory() const;

	virtual sf::FloatRect getBoundingRect() const;

private:
	sf::Sprite sprite;

};
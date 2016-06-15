#pragma once
#include "SceneNode.h"
#include "TextureHolder.h"

class Lamps : public SceneNode {
public:
	Lamps(const TextureHolder& textures);
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual unsigned int getCategory() const;

private:
	sf::Sprite sprite;

};

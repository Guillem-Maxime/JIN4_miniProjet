#pragma once
#include "Entity.h"
#include "TextureHolder.h"

class Plateform : public Entity
{
public:
	Plateform(const TextureHolder& textures);
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual unsigned int getCategory() const;

private:
	sf::Sprite sprite;
};


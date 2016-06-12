#pragma once
#include "Entity.h"
#include "TextureHolder.h"
class Shadow : public Entity
{
public:
	Shadow(const TextureHolder& textures);
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual unsigned int getCategory() const;

	virtual sf::FloatRect getBoundingRect() const;

private:
	sf::Sprite sprite;
};


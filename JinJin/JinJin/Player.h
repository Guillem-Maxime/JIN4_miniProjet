#pragma once
#include "Entity.h"
#include "TextureHolder.h"

class Player : public Entity
{
public:
	Player(const TextureHolder& textures);
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

private:
	sf::Sprite sprite;
	
};

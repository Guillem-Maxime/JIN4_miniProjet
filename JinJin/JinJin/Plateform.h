#pragma once
#include "Entity.h"
#include "TextureHolder.h"

/* Classe les objets plateforme */
class Plateform : public Entity
{
public:
	Plateform(const TextureHolder& textures);
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual unsigned int getCategory() const;

	virtual sf::FloatRect getBoundingRect() const;

	void inverse();

private:
	sf::Sprite sprite;
	bool inversed;
};


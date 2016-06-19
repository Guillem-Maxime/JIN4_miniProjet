#pragma once
#include "Entity.h"
#include "TextureHolder.h"

/* Classe les objets plateforme */
class Plateform : public Entity
{
public:

	Plateform(const TextureHolder& textures, int type);
	Plateform(const TextureHolder& textures, int type, int range);
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual unsigned int getCategory() const;

	virtual sf::FloatRect getBoundingRect() const;

	void inverse();

private:
	virtual void updateCurrent(sf::Time dt);

private:
	sf::Sprite sprite;
	bool inversed;

	bool isMooving;
	int range;
	sf::Time time;
};


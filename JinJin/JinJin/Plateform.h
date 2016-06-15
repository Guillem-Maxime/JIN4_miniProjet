#pragma once
#include "Entity.h"
#include "TextureHolder.h"

/* Classe les objets plateforme */
class Plateform : public Entity
{
public:

	//Le type indique le type de texture à charger : 
	/* 1: Plateforme horizontale
	* 2: Plateforme verticale
	* 3: Petite Plateforme
	* 4: Sol
	* 5: Murs
	*/
	Plateform(const TextureHolder& textures, int type);
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual unsigned int getCategory() const;

	virtual sf::FloatRect getBoundingRect() const;

	void inverse();

private:
	sf::Sprite sprite;
	bool inversed;
};


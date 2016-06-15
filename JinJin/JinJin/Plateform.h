#pragma once
#include "Entity.h"
#include "TextureHolder.h"

/* Classe les objets plateforme */
class Plateform : public Entity
{
public:
	//le int indique le type de plate forme : 
	//1 pour une plate forme horizontale longue
	//2 pour une plateforme verticale longue
	//3 pour une plate forme simple
	Plateform(const TextureHolder& textures, int type);
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual unsigned int getCategory() const;

	virtual sf::FloatRect getBoundingRect() const;

	void inverse();

private:
	sf::Sprite sprite;
	bool inversed;
};


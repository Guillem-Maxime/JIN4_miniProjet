#pragma once
#include "Fps.h"
#include "Entity.h"
#include "TextureHolder.h"

/* Classe les objets plateforme */
class Plateform : public Entity
{
public:

	Plateform(const TextureHolder& textures, int type);
	Plateform(const TextureHolder& textures, int type, int range, bool isHor);
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual unsigned int getCategory() const;

	virtual sf::FloatRect getBoundingRect() const;

	void inverse();

private:
	virtual void updateCurrent(sf::Time dt);

private:
	sf::Sprite sprite;
	bool inversed;

	bool isMoving;		//Ce booleen indique si la plateforme bouge
	bool isHorizontal;	//Ce booleen indique si le mouvement est horizontal (true) ou vertical (false)
	int range;			//Cet int indique de quelle distance ce déplace la plateforme
	sf::Time time;
	int ticks;
};


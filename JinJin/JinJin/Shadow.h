#pragma once
#include "Entity.h"
#include "TextureHolder.h"

 /* Classe des objets ombres plateforme */
class Shadow : public Entity
{
public:
	Shadow(const TextureHolder& textures, int type);
	Shadow(const TextureHolder & textures, int type, int range, bool isHor);
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual unsigned int getCategory() const;

	virtual sf::FloatRect getBoundingRect() const;

	void inverse();

	void updateCurrent(sf::Time dt);

private:
	sf::Sprite sprite;
	bool inversed;
	bool isMoving;
	bool isHorizontal;
	int range;
	sf::Time time;
};


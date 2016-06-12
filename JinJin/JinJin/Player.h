#pragma once
#include "Entity.h"
#include "TextureHolder.h"

/* Classe de l'objet joueur (son entité) */
class Player : public Entity
{
public:
	Player(const TextureHolder& textures);
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual unsigned int getCategory() const;

	virtual sf::FloatRect getBoundingRect() const;

	bool getGrounded();
	void setGrounded(bool g);

	void jump(float playerspeed);

private:
	sf::Sprite sprite;
	bool grounded;

	bool jumping;

	sf::Time jumpTime;
	
};

#pragma once
#include "Entity.h"
#include "TextureHolder.h"

/* Classe de l'objet joueur (son entit�) */
class Player : public Entity
{
public:
	Player(const TextureHolder& textures);
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
	void changeRect(sf::IntRect rect);
	virtual unsigned int getCategory() const;

	virtual sf::FloatRect getBoundingRect() const;

	bool getGrounded();
	bool getJumping();
	void setGrounded(bool g);

	void setJumping(bool j);

	void jump(float playerspeed);

private:
	sf::Sprite sprite;
	bool grounded;

	bool jumping;

	sf::Time jumpTime;
	
};

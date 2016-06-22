#pragma once

#include <SFML/Graphics.hpp>
#include "SceneNode.h"

static const float pi = 3.141592654f;

/* Classe M�re pour les classes pouvant changer leur position*/
class Entity : public SceneNode
{
public:
	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity() const;
	void setNextMove(sf::Vector2f nm);

protected:
	sf::Vector2f velocity;

private:
	virtual void updateCurrent(sf::Time dt);
};


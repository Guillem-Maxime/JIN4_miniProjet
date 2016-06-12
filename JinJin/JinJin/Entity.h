#pragma once

#include <SFML/Graphics.hpp>
#include "SceneNode.h"

/* Classe Mère pour les classes pouvant changer leur position*/
class Entity : public SceneNode
{
public:
	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity() const;

private:
	sf::Vector2f velocity;

	virtual void updateCurrent(sf::Time dt);
};


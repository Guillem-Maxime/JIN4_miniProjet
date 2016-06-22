#include "Entity.h"

void Entity::setVelocity(sf::Vector2f velocity)
{
	this->velocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
	velocity.x = vx;
	velocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{
	return velocity;
}

void Entity::setNextMove(sf::Vector2f nm)
{
	nextMove = nm;
}

void Entity::updateCurrent(sf::Time dt)
{
	move(velocity * dt.asSeconds() + nextMove);
}

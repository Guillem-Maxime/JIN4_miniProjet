#include "Player.h"
#include <iostream>

const sf::Time TimePerFrame = sf::seconds(1.f / 30.f);

Player::Player(const TextureHolder & textures) : sprite(textures.get(Textures::Player)), grounded(false)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Player::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

unsigned int Player::getCategory() const
{
	return Category::Player;
}

sf::FloatRect Player::getBoundingRect() const
{
	//on adapte le rectangle de collision pour n'avoir que la partie inferieure
	sf::FloatRect a = sprite.getGlobalBounds();
	a.top += a.height*0.75;
	a.height /= 4;
	return getWorldTransform().transformRect(a);
}

bool Player::getGrounded()
{
	return grounded;
}

void Player::setGrounded(bool g)
{
	grounded = g;
}

void Player::jump(float playerspeed)
{
	//si le joueur est au sol et qu'il ne saute pas il peut rentrer dans la phacse saut
	if (jumpTime == sf::Time::Zero && grounded)
		jumping = 1;
	// s'il saute son temps de saut doit être augmenté du temps d'une frame
	if (jumping)
		jumpTime += TimePerFrame;
		
	//tant qu'il saute  sa vitesse augmente
	if (jumping && jumpTime.asSeconds() < 1.f)
	{
		setVelocity(getVelocity() + sf::Vector2f(0.f, -2*playerspeed));
	}
	//il peut re-sauter en arrivant au sol 
	if(grounded && jumpTime.asSeconds() > 1.f)
	{
		jumping = 0;
		jumpTime = sf::Time::Zero;
	}
}

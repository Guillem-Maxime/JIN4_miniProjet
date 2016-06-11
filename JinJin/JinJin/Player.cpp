#include "Player.h"
#include <iostream>

const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

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
	if (jumpTime == sf::Time::Zero && grounded)
		jumping = 1;
	if (jumping)
		jumpTime += TimePerFrame;
		
	if (jumping && jumpTime < sf::seconds(15.f))
	{
		setVelocity(getVelocity() + sf::Vector2f(0.f, -1.5*playerspeed));
	}
	if(grounded && jumpTime > sf::seconds(15.f))
	{
		jumping = 0;
		jumpTime = sf::Time::Zero;
	}
}

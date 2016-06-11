#include "Player.h"
#include <iostream>

Player::Player(const TextureHolder & textures) : sprite(textures.get(Textures::Player))
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
	return getWorldTransform().transformRect(sprite.getGlobalBounds());
}

bool Player::getGrounded()
{
	return grounded;
}

void Player::setGrounded(bool g)
{
	grounded = g;
}

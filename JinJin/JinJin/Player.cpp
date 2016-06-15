#include "Player.h"
#include <iostream>


Player::Player(const TextureHolder & textures) : sprite(textures.get(Textures::Player)), grounded(false)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	sprite.setTextureRect(sf::IntRect(157, 119, 86, 141));
}

void Player::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

void Player::changeRect(sf::IntRect rect)
{
	sprite.setTextureRect(rect);
}

unsigned int Player::getCategory() const
{
	return Category::Player;
}

sf::FloatRect Player::getBoundingRect() const
{
	//on adapte le rectangle de collision pour n'avoir que la partie inferieure
	sf::FloatRect a = sprite.getGlobalBounds();
	a.top += a.height*float(0.75);
	a.height /= 4;
	a.left += a.width*float(0.25);
	a.width /= 2;
	return getWorldTransform().transformRect(a);
}

bool Player::getGrounded()
{
	return grounded;
}

bool Player::getJumping()
{
	return jumping;
}

void Player::setGrounded(bool g)
{
	grounded = g;
}

void Player::setJumping(bool j)
{
	jumping = j;
}

void Player::jump(float playerspeed)
{
	if (grounded)
		jumping = true;
	if(jumping)
		setVelocity(getVelocity() + sf::Vector2f(0.f, -playerspeed));
}

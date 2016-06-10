#include "Player.h"

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

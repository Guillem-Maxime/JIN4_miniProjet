#include "Player.h"

Player::Player(const TextureHolder & textures) : sprite(textures.get(Textures::Player))
{

}

void Player::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

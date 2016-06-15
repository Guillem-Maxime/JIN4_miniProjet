#include "Spikes.h"

Spikes::Spikes(const TextureHolder & textures) : sprite(textures.get(Textures::Spike))
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

Spikes::Spikes(const sf::Texture & texture, const sf::IntRect & rect) : sprite(texture, rect)
{
}
void Spikes::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

unsigned int Spikes::getCategory() const
{
	return Category::None;
}

sf::FloatRect Spikes::getBoundingRect() const
{
	return sf::FloatRect();
}

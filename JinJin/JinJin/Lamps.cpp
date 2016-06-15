#include "Lamps.h"

Lamps::Lamps(const TextureHolder & textures): sprite(sf::Sprite(textures.get(Textures::Lamp)))
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Lamps::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

unsigned int Lamps::getCategory() const
{
}

#include "Spikes.h"

Spikes::Spikes(const TextureHolder & textures) : sprite(sf::Sprite(textures.get(Textures::Spike)))
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Spikes::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

sf::FloatRect Spikes::getBoundingRect() const
{
	//on adapte le rectangle de colision pour n'avoir que le bord superieur
	sf::FloatRect a = sprite.getGlobalBounds();
	a.height /= 10;
	return getWorldTransform().transformRect(a);
}

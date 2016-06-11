#include "Plateform.h"

Plateform::Plateform(const TextureHolder & textures) : sprite(textures.get(Textures::Platform))
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Plateform::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

unsigned int Plateform::getCategory() const
{
	return Category::Platform;
}

sf::FloatRect Plateform::getBoundingRect() const
{
	sf::FloatRect a = sprite.getGlobalBounds();
	a.height /= 30;
	return getWorldTransform().transformRect(a);
	
}

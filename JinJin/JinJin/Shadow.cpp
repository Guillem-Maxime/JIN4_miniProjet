#include "Shadow.h"



Shadow::Shadow(const TextureHolder& textures) : sprite(textures.get(Textures::Shadow))
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Shadow::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

unsigned int Shadow::getCategory() const
{
	return Category::Platform;
}

sf::FloatRect Shadow::getBoundingRect() const
{
	return sf::FloatRect();
}

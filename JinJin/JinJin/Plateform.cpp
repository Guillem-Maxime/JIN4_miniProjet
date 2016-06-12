#include "Plateform.h"

Plateform::Plateform(const TextureHolder & textures) : sprite(textures.get(Textures::Platform)), inversed(false)
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
	if (!inversed)
	{
		//on adapte le rectangle de colision pour n'avoir que le bord superieur
		sf::FloatRect a = sprite.getGlobalBounds();
		a.height /= 30;
		return getWorldTransform().transformRect(a);
	} else
	{
		return sf::FloatRect();
	}
	
}

void Plateform::inverse()
{
	inversed = !inversed;
}

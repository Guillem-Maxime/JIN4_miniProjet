#include "Shadow.h"




Shadow::Shadow(const TextureHolder& textures, int type) : inversed(false)
{
	switch (type) {
	case 1:
		sprite = sf::Sprite(textures.get(Textures::Shadow1));
		break;
	case 2:
		sprite = sf::Sprite(textures.get(Textures::Shadow2));
		break;
	case 3:
		sprite = sf::Sprite(textures.get(Textures::Shadow3));
		break;
	}
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Shadow::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

unsigned int Shadow::getCategory() const
{
	return Category::Shadow;
}

sf::FloatRect Shadow::getBoundingRect() const
{
	//même remarque que pour les plateformes
	if (inversed)
	{
		sf::FloatRect a = sprite.getGlobalBounds();
		a.height /= 10;
		return getWorldTransform().transformRect(a);
	} else
	{
		return sf::FloatRect();
	}
}

void Shadow::inverse()
{
	inversed = !inversed;
}

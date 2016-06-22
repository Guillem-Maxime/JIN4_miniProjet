#include "Plateform.h"

#include <iostream>

Plateform::Plateform(const TextureHolder & textures, int type) : inversed(false)
{
	switch (type) {
	case 1 :
		sprite = sf::Sprite(textures.get(Textures::Platform1));
		break;
	case 2 :
		sprite = sf::Sprite(textures.get(Textures::Platform2));
		break;
	case 3 :
		sprite = sf::Sprite(textures.get(Textures::Platform3));
		break;
	case 4 :
		sprite = sf::Sprite(textures.get(Textures::Floor));
		break;
	case 5:
		sprite = sf::Sprite(textures.get(Textures::Wall));
		break;
	}
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	setVelocity(10,0);
}

Plateform::Plateform(const TextureHolder & textures, int type, int range, bool isHor) : Plateform(textures,type)
{
	isHorizontal = isHor;
	isMoving = true;
	this->range = range;
	time = sf::Time::Zero;
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
		a.height /= 10;
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

void Plateform::updateCurrent(sf::Time dt)
{
	if (isMoving)
	{
		
		time += dt;
		ticks++;
		if (isHorizontal)
		{
			nextMove = sf::Vector2f(range * cos(ticks/60 ) * dt.asSeconds(), 0) ;

		} else
		{
			nextMove = sf::Vector2f(0, range * cos(ticks/60 )* dt.asSeconds());
			
		}

		move(nextMove);
	}
}

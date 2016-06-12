#pragma once

#include <SFML\Graphics.hpp>
#include <functional>
#include <cassert>

/* Gestion des commandes envoyées*/

namespace Category
{
	/* Type des receveurs de la commande*/
	enum Type
	{
		None = 0,
		Scene = 1 << 0,
		Player = 1 << 1,
		Platform = 1 << 2,
		Shadow = 1 << 3,
		Text = 1 << 4,
	};
}

class SceneNode;

struct Command
{
	Command();

	std::function<void(SceneNode&, sf::Time)> action;
	unsigned int category;
};

/* Convertisseur de classe */
template <typename GameObject, typename Function> std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
{
	return [=](SceneNode& node, sf::Time dt) {
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		fn(static_cast<GameObject&>(node), dt);
	};
}


#pragma once

#include <SFML\Graphics.hpp>

#include <memory>
#include <vector>
#include <algorithm>
#include <cassert>
#include <set>

#include "Command.h"

/* Classe de base des objets du graphe de scène */

class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> USPtr;

	SceneNode();

	void attachChild(USPtr child);
	USPtr detachChild(const SceneNode &node);

	void update(sf::Time dt);

	sf::Transform getWorldTransform() const;
	sf::Vector2f getWorldPosition() const;

	virtual unsigned int getCategory() const;

	void onCommand(const Command& command, sf::Time dt);

	virtual sf::FloatRect getBoundingRect() const;
	bool checkNodeCollision(SceneNode& node);
	bool checkSceneCollision(SceneNode& sceneGraph);


private:

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const final;
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

	virtual void updateCurrent(sf::Time dt);
	void updateChildren(sf::Time dt);

	void drawBoundingRect(sf::RenderTarget & target, sf::RenderStates) const;

	std::vector<USPtr> children;
	SceneNode* parent;
};

//renvoie true si les deux noeuds sont en collision
bool	collision(const SceneNode& l, const SceneNode& r);
#pragma once

#include <SFML\Graphics.hpp>

#include <memory>
#include <vector>
#include <algorithm>
#include <cassert>

#include "Command.h"

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

private:

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const final;
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

	virtual void updateCurrent(sf::Time dt);
	void updateChildren(sf::Time dt);

	std::vector<USPtr> children;
	SceneNode* parent;
};


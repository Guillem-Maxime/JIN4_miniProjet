#pragma once

#include <SFML\Graphics.hpp>

#include <memory>
#include <vector>
#include <algorithm>
#include <cassert>

class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> USPtr;

	SceneNode();

	void attachChild(USPtr child);
	USPtr detachChild(const SceneNode &node);

private:

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const final;
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

	std::vector<USPtr> children;
	SceneNode* parent;
};


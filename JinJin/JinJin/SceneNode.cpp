#include "SceneNode.h"

#include <iostream>

typedef std::unique_ptr<SceneNode> USPtr;

SceneNode::SceneNode() : parent(nullptr), children()
{
}

void SceneNode::attachChild(USPtr child)
{
	child->parent = this;
	children.push_back(std::move(child));
}

USPtr SceneNode::detachChild(const SceneNode & node)
{
	auto found = std::find_if(children.begin(), children.end(), [&](USPtr &p) -> bool { return p.get() == &node; });
	assert(found != children.end());

	USPtr res = std::move(*found);
	res->parent = nullptr;
	children.erase(found);

	return res;
}

void SceneNode::update(sf::Time dt)
{
	updateChildren(dt);
	updateCurrent(dt);
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform trans = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->parent)
	{	
		trans = node->getTransform() *trans;
	}
	
	return trans;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

unsigned int SceneNode::getCategory() const
{
	return Category::Scene;
}

void SceneNode::onCommand(const Command & command, sf::Time dt)
{
	if (command.category & getCategory())
		command.action(*this, dt);

	for (auto& child : children)
	{
		child->onCommand(command, dt);
	}
}

sf::FloatRect SceneNode::getBoundingRect() const
{
	return sf::FloatRect();
}

bool SceneNode::checkNodeCollision(SceneNode & node)
{
	if (this != &node && this->getCategory() != node.getCategory() && collision(*this, node))
		return true;

	if(this->getCategory() == Category::Scene)
	{
		for (auto& child : children)
		{
			if (child->checkNodeCollision(node))
				return true;

		}
	}
	

	return false;

}

bool SceneNode::checkSceneCollision(SceneNode & sceneGraph)
{
	if (checkNodeCollision(sceneGraph))
		return true;
	
	for	(auto& child : sceneGraph.children)
	{
		if (checkSceneCollision(*child))
			return true;
	}
	return false;
}



void SceneNode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	drawCurrent(target, states);

	for (auto &child : children)
	{
		child->draw(target, states);
	}

	//drawBoundingRect(target, states);
	
}

void SceneNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
}

void SceneNode::updateCurrent(sf::Time dt)
{
}

void SceneNode::updateChildren(sf::Time dt)
{
	for (auto &child : children)
	{
		child->update(dt);
	}
}

void SceneNode::drawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const
{
	sf::FloatRect rect = getBoundingRect();

	sf::RectangleShape shape;
	shape.setPosition(sf::Vector2f(rect.left, rect.top));
	shape.setSize(sf::Vector2f(rect.width, rect.height));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1.f);

	target.draw(shape);
}

bool collision(const SceneNode & l, const SceneNode & r)
{
	return l.getBoundingRect().intersects(r.getBoundingRect());
}

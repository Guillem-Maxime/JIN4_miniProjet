#include "SceneNode.h"

typedef std::unique_ptr<SceneNode> USPtr;

SceneNode::SceneNode()
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
	for (const auto node = this; node != nullptr; node->parent)
	{
		trans = node->getTransform() *trans;
	}

	return trans;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

void SceneNode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	drawCurrent(target, states);

	for (auto &child : children)
	{
		child->draw(target, states);
	}
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




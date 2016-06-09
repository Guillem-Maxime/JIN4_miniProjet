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

void SceneNode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	drawCurrent(target, states);

	for (auto &child : children)
	{
		child->draw(target, states);
	}
}




#include "World.h"


World::World(sf::RenderWindow & window) : window(window), worldView(window.getDefaultView()), worldBounds( 0.f,0.f,8000.f,2000.f)
, spawnPosition(worldView.getSize().x/2.f, worldView.getSize().y / 2.f)
,player(nullptr)
{
	loadTextures();
	buildScene();

	worldView.setCenter(spawnPosition);
}

void World::update(sf::Time dt)
{
	
	player->setVelocity(0.f, 0.f);

	while (!comQueue.isEmpty())
		sceneGraph.onCommand(comQueue.pop(), dt);

	sceneGraph.update(dt);

	
	const float borderDistance = 200.f;

	sf::Vector2f position = player->getPosition();
	position.x = std::max(position.x, worldBounds.left + borderDistance);
	position.x = std::min(position.x, worldBounds.left + worldBounds.width - borderDistance);
	position.y = std::max(position.y, worldBounds.top + borderDistance);
	position.y = std::min(position.y, worldBounds.top + worldBounds.height - borderDistance);

	player->setPosition(position);

	sf::FloatRect viewBounds(worldView.getCenter() - worldView.getSize() / 2.f, worldView.getSize());


	worldView.move(player->getVelocity() * dt.asSeconds());

	sf::Vector2f center = worldView.getCenter();
	center.x = std::min(center.x, worldBounds.width -borderDistance );
	center.x = std::max(center.x, 0.f + borderDistance);
	center.y = std::min(center.y, worldBounds.height -borderDistance);
	center.y = std::max(center.y, 0.f + borderDistance);

	worldView.setCenter(center);

}

void World::draw()
{
	window.setView(worldView);
	window.draw(sceneGraph);
}

CommandQueue & World::getCommandQueue()
{
	return comQueue;
}

void World::loadTextures()
{
	textures.load(Textures::Player, "Media/Sprites/1.png");
	textures.load(Textures::Platform, "Media/Sprites/2.png");
	textures.load(Textures::Background, "Media/Tiles/1.jpg");
}

void World::buildScene()
{
	for (auto i = 0; i < LayerCount; ++i)
	{
		SceneNode::USPtr layer = std::make_unique<SceneNode>();
		sceneLayers[i] = layer.get();

		sceneGraph.attachChild(std::move(layer));
	}

	sf::Texture& texture = textures.get(Textures::Background);
	sf::IntRect textureRect(worldBounds);
	texture.setRepeated(true);

	std::unique_ptr<SpriteNode> backSprite = std::make_unique<SpriteNode>(texture, textureRect);
	backSprite->setPosition(worldBounds.left, worldBounds.top);
	sceneLayers[Back]->attachChild(std::move(backSprite));

	std::unique_ptr<Player> mainChar = std::make_unique<Player>(textures);
	player = mainChar.get();
	player->setPosition(spawnPosition);
	player->setVelocity(0.f, 0.f);
	sceneLayers[Front]->attachChild(std::move(mainChar));

	std::vector<sf::Vector2f> pos;
	pos.push_back(sf::Vector2f(400, 400));
	pos.push_back(sf::Vector2f(800, 410));
	pos.push_back(sf::Vector2f(200, 800));

	for (auto position : pos)
	{
		std::unique_ptr<Plateform> p = std::make_unique<Plateform>(textures);
		p->setPosition(position);
		sceneLayers[Front]->attachChild(std::move(p));
	}



}

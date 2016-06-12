#include "World.h"

#include <iostream>


World::World(sf::RenderWindow & window) : window(window), worldView(window.getDefaultView()), worldBounds( 0.f,0.f,8000.f,2000.f)
, spawnPosition(200, 400)
,player(nullptr), grounded(false)
{
	loadTextures();
	buildScene();

	worldView.setCenter(spawnPosition);
}

void World::update(sf::Time dt)
{
	
	player->setVelocity(0.f, 400.f);

	while (!comQueue.isEmpty())
		sceneGraph.onCommand(comQueue.pop(), dt);

	player->setGrounded(sceneGraph.checkSceneCollision(sceneGraph));
	if (player->getGrounded())
	{
		sf::Vector2f v = player->getVelocity();
		player->setVelocity(v.x, v.y - 400.f);
	}
	
	sceneGraph.update(dt);

	
	const float borderDistance = 200.f;

	sf::Vector2f position = player->getPosition();
	position.x = std::max(position.x, worldBounds.left + borderDistance);
	position.x = std::min(position.x, worldBounds.left + worldBounds.width - borderDistance);
	position.y = std::max(position.y, worldBounds.top + borderDistance);
	position.y = std::min(position.y, worldBounds.top + worldBounds.height - borderDistance);

	player->setPosition(position);

	if (player->getPosition().y > 1700)
		reset();

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

void World::reset()
{
	player->setPosition(spawnPosition);
	worldView.setCenter(spawnPosition);
}

void World::loadTextures()
{
	textures.load(Textures::Player, "Media/Sprites/1.png");
	textures.load(Textures::Platform, "Media/Sprites/2.png");
	textures.load(Textures::Shadow, "Media/Sprites/3.png");
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


	std::vector<sf::Vector2f> pos;
	pos.push_back(sf::Vector2f(200, 800));
	pos.push_back(sf::Vector2f(350, 700));
	pos.push_back(sf::Vector2f(400, 400));
	pos.push_back(sf::Vector2f(500, 600));
	pos.push_back(sf::Vector2f(550, 550));
	pos.push_back(sf::Vector2f(600, 396));
	pos.push_back(sf::Vector2f(700, 400));
	pos.push_back(sf::Vector2f(800, 410));
	pos.push_back(sf::Vector2f(1000, 400));

	for (auto position : pos)
	{
		/*std::unique_ptr<Plateform> p = std::make_unique<Plateform>(textures);
		p->setPosition(position);

		std::unique_ptr<Shadow> s = std::make_unique<Shadow>(textures);
		s->setPosition(sf::Vector2f(70, 50));

		p->attachChild(std::move(s));
		sceneLayers[Front]->attachChild(std::move(p));*/

		std::unique_ptr<Plateform> p = std::make_unique<Plateform>(textures);
		float a = -30 * 0.003*position.x;
		p->setPosition(sf::Vector2f(a, -20));
		
		std::unique_ptr<Shadow> s = std::make_unique<Shadow>(textures);
		s->setPosition(position);

		s->attachChild(std::move(p));
		sceneLayers[Front]->attachChild(std::move(s));
	}

	std::unique_ptr<Player> mainChar = std::make_unique<Player>(textures);
	player = mainChar.get();
	player->setPosition(spawnPosition);
	player->setVelocity(0.f, 0.f);
	sceneLayers[Front]->attachChild(std::move(mainChar));
	


}




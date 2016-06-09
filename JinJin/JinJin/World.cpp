#include "World.h"

World::World(sf::RenderWindow & window) : window(window), worldView(window.getDefaultView()), worldBounds( 0.f,0.f,2000.f,2000.f)
, spawnPosition(worldView.getSize().x/2.f, worldView.getSize().y / 2.f)
,player(nullptr)
{
	loadTextures();
	buildScene();

	worldView.setCenter(spawnPosition);
}

void World::update(sf::Time dt)
{
	worldView.move(player->getVelocity() * dt.asSeconds());

	sceneGraph.update(dt);
}

void World::draw()
{
	window.setView(worldView);
	window.draw(sceneGraph);
}

void World::loadTextures()
{
	textures.load(Textures::Player, "Media/Sprites/1.png");
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
	player->setVelocity(10.f, 2.f);
	sceneLayers[Front]->attachChild(std::move(mainChar));



}

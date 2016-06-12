#include "World.h"

#include <iostream>


/* Initialisation */
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
	//Gravité exercé sur le joueur
	player->setVelocity(0.f, 400.f);

	//Application des commandes dans la liste
	while (!comQueue.isEmpty())
		sceneGraph.onCommand(comQueue.pop(), dt);

	//Le joueur touche-t-il le sol ? Si oui, plus de gravité
	player->setGrounded(sceneGraph.checkSceneCollision(sceneGraph));
	if (player->getGrounded())
	{
		sf::Vector2f v = player->getVelocity();
		player->setVelocity(v.x, v.y - 400.f);
	}
	
	//mise à jour du graphe de scène (principalement déplacement des entitéés) 
	sceneGraph.update(dt);

	//On contraint le joueur à rester dans la zone de jeu
	const float borderDistance = 200.f;

	sf::Vector2f position = player->getPosition();
	position.x = std::max(position.x, worldBounds.left + borderDistance);
	position.x = std::min(position.x, worldBounds.left + worldBounds.width - borderDistance);
	position.y = std::max(position.y, worldBounds.top + borderDistance);
	position.y = std::min(position.y, worldBounds.top + worldBounds.height - borderDistance);

	player->setPosition(position);

	//Si le joueur tombe trop bas, il recommence
	if (player->getPosition().y > 1700)
		reset();

	//La vue du monde est centrée sur le joueur (mêmes mouvements que lui et est contrainte aussi)
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
	//rajouter le reset de l'inversion des plateformes une fois implémenté dasn update
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
	//création des couches
	for (auto i = 0; i < LayerCount; ++i)
	{
		SceneNode::USPtr layer = std::make_unique<SceneNode>();
		sceneLayers[i] = layer.get();

		sceneGraph.attachChild(std::move(layer));
		
	}

	//initialisation de l'arrière plan
	sf::Texture& texture = textures.get(Textures::Background);
	sf::IntRect textureRect(worldBounds);
	texture.setRepeated(true);

	std::unique_ptr<SpriteNode> backSprite = std::make_unique<SpriteNode>(texture, textureRect);
	backSprite->setPosition(worldBounds.left, worldBounds.top);
	sceneLayers[Back]->attachChild(std::move(backSprite));

	//création des plateformes
	//Positions voulue pour les ombres
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

	//on crée les ombres puis la plateforme associée
	for (auto position : pos)
	{
		std::unique_ptr<Plateform> p = std::make_unique<Plateform>(textures);
		float a = -30.f * 0.003*position.x;
		p->setPosition(sf::Vector2f(a, -20));
		
		std::unique_ptr<Shadow> s = std::make_unique<Shadow>(textures);
		s->setPosition(position);

		s->attachChild(std::move(p));
		sceneLayers[Front]->attachChild(std::move(s));
	}

	//On crée le personnage
	std::unique_ptr<Player> mainChar = std::make_unique<Player>(textures);
	player = mainChar.get();
	player->setPosition(spawnPosition);
	player->setVelocity(0.f, 0.f);
	sceneLayers[Front]->attachChild(std::move(mainChar));
	


}




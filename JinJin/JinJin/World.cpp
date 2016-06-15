#include "World.h"

#include <iostream>


/* Initialisation */
World::World(sf::RenderWindow & window, EventHandler &handler) : window(window), worldView(window.getDefaultView()), worldBounds( 0.f,0.f,8000.f,2000.f)
, spawnPosition(440, 1570)
,player(nullptr), grounded(false), inversed(false), evHandler(handler)

{
	loadTextures();

	buildScene();

	worldView.setCenter(spawnPosition);

	window.setFramerateLimit(60);
}

void World::update(sf::Time dt)
{

	//Gravité exercé sur le joueur

	//Le joueur touche-t-il le sol ? Si oui, plus de gravité
	player->setGrounded(sceneGraph.checkSceneCollision(sceneGraph));
	if (!player->getGrounded() && !player->getJumping())
	{
		player->setVelocity(0.f, 400.f);
	} else
	{
		player->setVelocity(0.f, 0.f);
	}

	//Application des commandes dans la liste
	while (!comQueue.isEmpty())
		sceneGraph.onCommand(comQueue.pop(), dt);

	
	//mise à jour du graphe de scène (principalement déplacement des entitéés) 
	sceneGraph.update(dt);

	//On contraint le joueur à rester dans la zone de jeu
	const float borderDistance = 380.f;

	sf::Vector2f position = player->getPosition();
	position.x = std::max(position.x, worldBounds.left + borderDistance);
	position.x = std::min(position.x, worldBounds.left + worldBounds.width - borderDistance);
	position.y = std::max(position.y, worldBounds.top + borderDistance);
	position.y = std::min(position.y, worldBounds.top + worldBounds.height - borderDistance + 40);

	player->setPosition(position);



	//Si le joueur tombe trop bas, il recommence
	if (player->getPosition().y > 1650){
		++deathCount;
		switch (deathCount)
		{
		case 1:
			evHandler.addDrawText("Dommage", 200);
			break;
		case 2:
			evHandler.addDrawText("Incapable", 200);
			break;
		default:
			evHandler.addDrawText("lol", 800);
			break;
		}
		
		reset();
	}

	//La vue du monde est centrée sur le joueur (mêmes mouvements que lui et est contrainte aussi)
	sf::FloatRect viewBounds(worldView.getCenter() - worldView.getSize() / 2.f, worldView.getSize());

	worldView.move(player->getVelocity() * dt.asSeconds());

	sf::Vector2f center = worldView.getCenter();
	center.x = std::min(center.x, worldBounds.width -borderDistance );
	center.x = std::max(center.x, 0.f + borderDistance);
	center.y = std::min(center.y, worldBounds.height -borderDistance);
	center.y = std::max(center.y, 0.f + borderDistance);

	worldView.setCenter(center);
	text->setPosition(player->getPosition());
	
	if (!inversed && player->getPosition().x > 3200 && player->getPosition().x < 5350) {
		evHandler.addInverse();
		inversed = true;
	}
	
	if (player->getPosition().x > 5350 && player->getPosition().y < 650) {
		inversed = false;
		evHandler.addDrawText("You've beaten the game", 200);
		player->setVelocity(sf::Vector2f(0,0));
	}

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
	evHandler.addInverse();
	inversed = false;
}

void World::loadTextures()
{
	textures.load(Textures::Player, "Media/Sprites/sheet.png");
	textures.load(Textures::Platform1, "Media/Sprites/Platform1.png");
	textures.load(Textures::Platform2, "Media/Sprites/Platform2.png");
	textures.load(Textures::Platform3, "Media/Sprites/Platform3.png");
	textures.load(Textures::Shadow1, "Media/Sprites/Shadow1.png");
	textures.load(Textures::Shadow2, "Media/Sprites/Shadow2.png");
	textures.load(Textures::Shadow3, "Media/Sprites/Shadow3.png");
	textures.load(Textures::Background, "Media/Tiles/background.png");

	textures.load(Textures::Floor, "Media/Sprites/Floor.png");
	textures.load(Textures::Wall, "Media/Sprites/Wall.png");

	textures.load(Textures::Lamp, "Media/Sprites/Lamp.png");
	textures.load(Textures::Spike, "Media/Sprites/Spike.png");
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


	buildLevel();

	//On crée le personnage
	std::unique_ptr<Player> mainChar = std::make_unique<Player>(textures);
	player = mainChar.get();
	player->setPosition(spawnPosition);
	player->setVelocity(0.f, 0.f);
	sceneLayers[Front]->attachChild(std::move(mainChar));
	
	//On crée une textBox
	sf::Font font;
	if (!font.loadFromFile("Neon.ttf")){
		std::cout << "erreur loadfromfile font" << std::endl;
	}
	std::unique_ptr<TextBox> textTB = std::make_unique<TextBox>(font, sf::Color(255, 140, 0));
	text = textTB.get();

	sceneLayers[Text]->attachChild(std::move(textTB));

}

void World::buildLevel() {

	//Nos trois conteneur de plateforme : Plateforme1, 2 et 3 et Shadow1, 2 et 3, Lampes et Piques
	std::vector<sf::Vector2f> posPF1;
	std::vector<sf::Vector2f> posPF2;
	std::vector<sf::Vector2f> posPF3;

	std::vector<sf::Vector2f> posSh1;
	std::vector<sf::Vector2f> posSh2;
	std::vector<sf::Vector2f> posSh3;

	std::vector<sf::Vector2f> posLamps;
	std::vector<sf::Vector2f> posSpikes;

	//On dessine le bord du niveau
	//Le sol
	std::unique_ptr<Plateform> pFloor = std::make_unique<Plateform>(textures, 4);
	pFloor->setPosition(sf::Vector2f(3707.5, 1675));
	sceneLayers[Front]->attachChild(std::move(pFloor));

	//Les murs
	std::unique_ptr<Plateform> pWall1 = std::make_unique<Plateform>(textures, 5);
	pWall1->setPosition(sf::Vector2f(142, 1290));
	sceneLayers[Front]->attachChild(std::move(pWall1));
	pWall1 = std::make_unique<Plateform>(textures, 5);
	pWall1->setPosition(sf::Vector2f(142, 890));
	sceneLayers[Front]->attachChild(std::move(pWall1));

	std::unique_ptr<Plateform> pWall2 = std::make_unique<Plateform>(textures, 5);
	pWall2->setPosition(sf::Vector2f(7280, 1290));
	sceneLayers[Front]->attachChild(std::move(pWall2));


	//Le premier module
	posLamps.push_back(sf::Vector2f(300, 1230));
	posPF2.push_back(sf::Vector2f(535, 1430));
	posSh2.push_back(sf::Vector2f(555, 1450));
	posPF2.push_back(sf::Vector2f(535, 1570));
	posSh2.push_back(sf::Vector2f(555, 1590));
	posPF3.push_back(sf::Vector2f(460, 1500));
	posSh3.push_back(sf::Vector2f(480, 1520));
	posPF1.push_back(sf::Vector2f(645, 1395));
	posSh1.push_back(sf::Vector2f(665, 1415));
	posPF1.push_back(sf::Vector2f(885, 1395));
	posSh1.push_back(sf::Vector2f(905, 1415));
	posPF2.push_back(sf::Vector2f(1005, 1430));
	posSh2.push_back(sf::Vector2f(1025, 1450));
	posPF2.push_back(sf::Vector2f(1005, 1570));
	posSh2.push_back(sf::Vector2f(1025, 1590));
	posPF3.push_back(sf::Vector2f(1075, 1500));
	posSh3.push_back(sf::Vector2f(1095, 1520));

	//La longue plateforme seule
	posLamps.push_back(sf::Vector2f(1400, 1230));
	posPF1.push_back(sf::Vector2f(1400, 1395));
	posSh1.push_back(sf::Vector2f(1400, 1415));

	
	//Les trois petites plateformes seules
	posLamps.push_back(sf::Vector2f(1990, 1230));
	posPF3.push_back(sf::Vector2f(1750, 1430));
	posSh3.push_back(sf::Vector2f(1700, 1470));
	posPF3.push_back(sf::Vector2f(1990, 1480));
	posSh3.push_back(sf::Vector2f(1990, 1520));
	posPF3.push_back(sf::Vector2f(2230, 1390));
	posSh3.push_back(sf::Vector2f(2250, 1430));


	//Le deuxième module
	posPF2.push_back(sf::Vector2f(2555, 1570));
	posSh2.push_back(sf::Vector2f(2595, 1590));
	posPF2.push_back(sf::Vector2f(2555, 1430));
	posSh2.push_back(sf::Vector2f(2595, 1450));
	posPF1.push_back(sf::Vector2f(2640, 1325));
	posSh1.push_back(sf::Vector2f(2680, 1345));
	posPF1.push_back(sf::Vector2f(2880, 1325));
	posSh1.push_back(sf::Vector2f(2920, 1345));
	posPF2.push_back(sf::Vector2f(2965, 1570));
	posSh2.push_back(sf::Vector2f(3005, 1590));
	posPF2.push_back(sf::Vector2f(2965, 1430));
	posSh2.push_back(sf::Vector2f(3005, 1450));

	//a partir de là il y a les ombres
	posLamps.push_back(sf::Vector2f(3355, 1570));
	posPF1.push_back(sf::Vector2f(3375, 1325));
	posSh1.push_back(sf::Vector2f(3425, 1300));

	posPF1.push_back(sf::Vector2f(3800, 1250));
	posSh1.push_back(sf::Vector2f(3865, 1200));

	posPF1.push_back(sf::Vector2f(4000, 1050));
	posSh1.push_back(sf::Vector2f(4105, 1000));

	posPF3.push_back(sf::Vector2f(3800, 950));
	posSh3.push_back(sf::Vector2f(3865, 900));
	
	posPF1.push_back(sf::Vector2f(4100, 800));
	posSh1.push_back(sf::Vector2f(4205, 750));


	//Les trois petites plateformes
	posLamps.push_back(sf::Vector2f(4750, 550));
	posPF3.push_back(sf::Vector2f(4650, 600));

	posSh3.push_back(sf::Vector2f(4450, 580));
	posPF3.push_back(sf::Vector2f(4750, 650));
	posSh3.push_back(sf::Vector2f(4750, 750));
	posPF3.push_back(sf::Vector2f(4850, 600));
	posSh3.push_back(sf::Vector2f(5050, 585));

	//The Last One
	posLamps.push_back(sf::Vector2f(5250, 450));
	posLamps.push_back(sf::Vector2f(5550, 450));
	posPF1.push_back(sf::Vector2f(5450, 650));
	posSh1.push_back(sf::Vector2f(5450, 700));

	//On cree le level
	//On cree les ombres en premier pour qu'elles soient en dessous
	for (auto position : posSh1) {
		std::unique_ptr<Shadow> s = std::make_unique<Shadow>(textures, 1);
		s->setPosition(sf::Vector2f(position));
		sceneLayers[Front]->attachChild(std::move(s));
	}
	for (auto position : posSh2) {
		std::unique_ptr<Shadow> s = std::make_unique<Shadow>(textures, 2);
		s->setPosition(sf::Vector2f(position));
		sceneLayers[Front]->attachChild(std::move(s));
	}

	for (auto position : posSh3) {
		std::unique_ptr<Shadow> s = std::make_unique<Shadow>(textures, 3);
		s->setPosition(sf::Vector2f(position));
		sceneLayers[Front]->attachChild(std::move(s));
	}

	//Puis les plateformes
	for (auto position : posPF1) {
		std::unique_ptr<Plateform> p = std::make_unique<Plateform>(textures, 1);
		p->setPosition(sf::Vector2f(position));
		sceneLayers[Front]->attachChild(std::move(p));
	}

	for (auto position : posPF2) {
		std::unique_ptr<Plateform> p = std::make_unique<Plateform>(textures, 2);
		p->setPosition(sf::Vector2f(position));
		sceneLayers[Front]->attachChild(std::move(p));
	}

	for (auto position : posPF3) {
		std::unique_ptr<Plateform> p = std::make_unique<Plateform>(textures, 3);
		p->setPosition(sf::Vector2f(position));
		sceneLayers[Front]->attachChild(std::move(p));
	}

	//Puis les lampes et les piques
	for (auto position : posLamps) {
		std::unique_ptr<Lamps> l = std::make_unique<Lamps>(textures);
		l->setPosition(sf::Vector2f(position));
		sceneLayers[Front]->attachChild(std::move(l));
	}

	sf::Texture& texture = textures.get(Textures::Spike);
	sf::IntRect textureRect(sf::IntRect(0,0,3000,76));
	texture.setRepeated(true);

	for (auto position : posSpikes) {
		std::unique_ptr<Spikes> s = std::make_unique<Spikes>(texture, textureRect);
		s->setPosition(sf::Vector2f(position));
		sceneLayers[Front]->attachChild(std::move(s));
	}


}
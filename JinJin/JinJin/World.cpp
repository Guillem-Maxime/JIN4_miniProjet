#include "World.h"

#include <iostream>


/* Initialisation */
<<<<<<< HEAD
World::World(sf::RenderWindow & window, EventHandler &handler) : window(window), worldView(window.getDefaultView()), worldBounds( 0.f,0.f,8000.f,2000.f)
, spawnPosition(240, 1570)
,player(nullptr), grounded(false), evHandler(handler)
=======

World::World(sf::RenderWindow & window, EventHandler &handler) : window(window), worldView(window.getDefaultView()), worldBounds( 0.f,0.f,8000.f,2000.f)
, evHandler(handler)
, spawnPosition(200, 400)
,player(nullptr), grounded(false)
>>>>>>> 6327010afd1e27ba76310f93763f6ce6d342f477
{
	loadTextures();
	buildScene();
	buildLevel();

	worldView.setCenter(spawnPosition);

	window.setFramerateLimit(60);
}

void World::update(sf::Time dt)
{
	//Gravité exercé sur le joueur
	//player->setVelocity(0.f, 400.f);

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
	const float borderDistance = 200.f;

	sf::Vector2f position = player->getPosition();
	position.x = std::max(position.x, worldBounds.left + borderDistance);
	position.x = std::min(position.x, worldBounds.left + worldBounds.width - borderDistance);
	position.y = std::max(position.y, worldBounds.top + borderDistance);
	position.y = std::min(position.y, worldBounds.top + worldBounds.height - borderDistance);

	player->setPosition(position);

	//Si le joueur tombe trop bas, il recommence
	if (player->getPosition().y > 1700)
	{
		evHandler.addDrawText("lol");
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
	textures.load(Textures::Player, "Media/Sprites/sheet.png");
	textures.load(Textures::Platform1, "Media/Sprites/Platform1.png");
	textures.load(Textures::Platform2, "Media/Sprites/Platform2.png");
	textures.load(Textures::Platform3, "Media/Sprites/Platform3.png");
	textures.load(Textures::Shadow1, "Media/Sprites/Shadow1.png");
	textures.load(Textures::Shadow1, "Media/Sprites/Shadow2.png");
	textures.load(Textures::Shadow1, "Media/Sprites/Shadow3.png");
	textures.load(Textures::Background, "Media/Tiles/background.png");

	textures.load(Textures::Floor, "Media/Sprites/Floor.png");
	textures.load(Textures::Wall, "Media/Sprites/Wall.png");
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
	/*
	std::vector<sf::Vector2f> pos;
	pos.push_back(sf::Vector2f(200, 845));
	pos.push_back(sf::Vector2f(350, 700));
	pos.push_back(sf::Vector2f(400, 400));
	pos.push_back(sf::Vector2f(500, 600));
	pos.push_back(sf::Vector2f(550, 550));
	pos.push_back(sf::Vector2f(600, 396));
	pos.push_back(sf::Vector2f(700, 400));
	pos.push_back(sf::Vector2f(800, 410));
	pos.push_back(sf::Vector2f(1000, 400));
	pos.push_back(sf::Vector2f(600, 600));
	pos.push_back(sf::Vector2f(700, 735));
	pos.push_back(sf::Vector2f(800, 835));
	pos.push_back(sf::Vector2f(900, 935));
	pos.push_back(sf::Vector2f(1000, 1035));
	pos.push_back(sf::Vector2f(1100, 1135));
	pos.push_back(sf::Vector2f(1200, 1235));
	pos.push_back(sf::Vector2f(1300, 1305));
	pos.push_back(sf::Vector2f(1433, 1433));
	*/

	//on crée les ombres puis la plateforme associée
	/*
	for (auto position : pos)
	{
		std::unique_ptr<Plateform> p = std::make_unique<Plateform>(textures, 1);
		/*float a = -30.f * 0.003*position.x;
		p->setPosition(sf::Vector2f(a, -20));*/
		
		/*std::unique_ptr<Shadow> s = std::make_unique<Shadow>(textures);
		s->setPosition(position);

		//s->attachChild(std::move(p));
		p->setPosition(position);
		sceneLayers[Front]->attachChild(std::move(p));
	}
	*/

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

	//Nos trois conteneur de plateforme : Plateforme1, 2 et 3 et Shadow1, 2 et 3
	std::vector<sf::Vector2f> posPF1;
	std::vector<sf::Vector2f> posPF2;
	std::vector<sf::Vector2f> posPF3;

	std::vector<sf::Vector2f> posSh1;
	std::vector<sf::Vector2f> posSh2;
	std::vector<sf::Vector2f> posSh3;

	//On dessine le bord du niveau
	//Le sol
	std::unique_ptr<Plateform> pFloor = std::make_unique<Plateform>(textures, 4);
	pFloor->setPosition(sf::Vector2f(3707.5, 1675));
	sceneLayers[Front]->attachChild(std::move(pFloor));
	//Le Plafond
	std::unique_ptr<Plateform> pRoof = std::make_unique<Plateform>(textures, 4);
	pRoof->setPosition(sf::Vector2f(3707.5, 905));
	sceneLayers[Front]->attachChild(std::move(pRoof));
	
	//Les murs
	std::unique_ptr<Plateform> pWall1 = std::make_unique<Plateform>(textures, 5);
	pWall1->setPosition(sf::Vector2f(142, 1290));
	sceneLayers[Front]->attachChild(std::move(pWall1));
	std::unique_ptr<Plateform> pWall2 = std::make_unique<Plateform>(textures, 5);
	pWall2->setPosition(sf::Vector2f(7050, 1290));
	sceneLayers[Front]->attachChild(std::move(pWall2));

	//D'abord le bas et le haut
	/*
	for (int i = 0; i < 30; ++i) {
		posPF1.push_back(sf::Vector2f(float(i * 240 + 215), 1675));
		posPF1.push_back(sf::Vector2f(float(i * 240 + 215), 905));
	}
	*/

	//Puis la gauche et la droite
	/*
	for (int i = 0; i < 5; ++i) {
		posPF2.push_back(sf::Vector2f(130, float(i * 140 + 1010)));
		posPF2.push_back(sf::Vector2f(7050, float(i * 140 + 1010)));
	}
	*/

	//Le premier module
	posPF2.push_back(sf::Vector2f(535, 1430));
	posPF2.push_back(sf::Vector2f(535, 1570));
	posPF3.push_back(sf::Vector2f(460, 1500));
	posPF1.push_back(sf::Vector2f(645, 1395));
	posPF1.push_back(sf::Vector2f(885, 1395));
	posPF2.push_back(sf::Vector2f(1005, 1430));
	posPF2.push_back(sf::Vector2f(1005, 1570));
	posPF3.push_back(sf::Vector2f(1075, 1500));

	//La longue plateforme seule
	posPF1.push_back(sf::Vector2f(1300, 1395));
	
	//Les trois petites plateformes seules
	posPF3.push_back(sf::Vector2f(1550, 1430));
	posPF3.push_back(sf::Vector2f(1790, 1480));
	posPF3.push_back(sf::Vector2f(2030, 1390));

	//Le deuxième module
	posPF2.push_back(sf::Vector2f(2255, 1570));
	posPF2.push_back(sf::Vector2f(2255, 1430));
	posPF1.push_back(sf::Vector2f(2340, 1325));
	posPF1.push_back(sf::Vector2f(2580, 1325));
	posPF2.push_back(sf::Vector2f(2665, 1570));
	posPF2.push_back(sf::Vector2f(2665, 1430));

	//a partir de là il a les ombres


	//On cree le level
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
}
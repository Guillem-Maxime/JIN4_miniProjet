#pragma once

#include "TextureHolder.h"
#include "SceneNode.h"
#include "Player.h"
#include "Plateform.h"
#include "Shadow.h"
#include "SpriteNode.h"
#include "CommandQueue.h"
#include "Command.h"
#include "Textbox.h"
#include "EventHandler.h"

#include <SFML\Graphics.hpp>

#include <array>
#include <memory>

/* Gère l'initialisation et la mise à jour du jeu */

class World : public sf::NonCopyable
{
public:
	explicit World(sf::RenderWindow &window, EventHandler &handler);
	void update(sf::Time dt);
	void draw();

	CommandQueue& getCommandQueue();

	void reset();


private:
	void loadTextures();
	void buildScene();

	void buildLevel();


	enum Layer
	{
		Back, 
		Front, 
		Text, 
		LayerCount
	};
	
	sf::RenderWindow& window;
	sf::View worldView;
	TextureHolder textures;
	SceneNode sceneGraph;
	std::array<SceneNode*, LayerCount> sceneLayers;

	sf::FloatRect worldBounds;
	sf::Vector2f spawnPosition;
	
	Player* player;
	TextBox* text;

	CommandQueue comQueue;

	bool grounded;

	EventHandler& evHandler;

};


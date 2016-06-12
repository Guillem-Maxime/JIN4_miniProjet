#pragma once

#include "TextureHolder.h"
#include "SceneNode.h"
#include "Player.h"
#include "Plateform.h"
#include "Shadow.h"
#include "SpriteNode.h"
#include "CommandQueue.h"
#include "Command.h"

#include <SFML\Graphics.hpp>

#include <array>
#include <memory>

class World : public sf::NonCopyable
{
public:
	explicit World(sf::RenderWindow &window);
	void update(sf::Time dt);
	void draw();

	CommandQueue& getCommandQueue();


private:
	void loadTextures();
	void buildScene();


	enum Layer
	{
		Back, 
		Front, 
		//Text, 
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

	CommandQueue comQueue;

	bool grounded;
	


};


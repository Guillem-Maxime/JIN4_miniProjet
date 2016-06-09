#pragma once
#include <SFML\Graphics.hpp>
#include "TextureHolder.h"
#include "SceneNode.h"
#include "Player.h"
#include "SpriteNode.h"

#include <array>
#include <memory>

class World : public sf::NonCopyable
{
public:
	explicit World(sf::RenderWindow &window);
	void update(sf::Time dt);
	void draw();

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


};


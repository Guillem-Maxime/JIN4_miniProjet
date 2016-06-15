#pragma once
#include <map>
#include <memory>

#include <SFML/Graphics.hpp>

/* Objet contenant toutes les textures */
namespace Textures
{
	enum ID
	{
		Background, Player, Platform1, Platform2, Platform3, Shadow, Lamp
	};
}

class TextureHolder
{
private:
	std::map<Textures::ID, std::unique_ptr<sf::Texture>> textureMap;

public:
	void load(Textures::ID id, const std::string& filename);
	sf::Texture& get(Textures::ID id);
	const sf::Texture& get(Textures::ID id) const;
	
	Textures::ID toTextureID(char c);
	//utiles ?
};


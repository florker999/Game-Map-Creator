#ifndef VAULT_H
#define VAULT_H

#include "SFML/Graphics.hpp"

#include "Variants.h"

class Vault
{

private:

	sf::Texture pusty;
	sf::Texture* textures;

public:

	sf::Texture& get ( floor_v );
	sf::Texture& get(wall_v);
    sf::Texture& get(chest_v);
	sf::Texture& get ( item_v );
	sf::Texture& get ( door_v );
	sf::Texture& get ( mixture_v );
	sf::Texture& get(character_v);
	sf::Texture& get(add_v);
	sf::Texture& get(bool);

	Vault();
	~Vault() { delete[] textures; };

};

#endif

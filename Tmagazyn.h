#ifndef TMAGAZYN_H
#define TMAGAZYN_H

#include <SFML/Graphics.hpp>

#include "typy.h"

class Tmagazyn
{

private:

	sf::Texture pusty;
	sf::Texture* magazyn;

public:

	sf::Texture& zwroc_t(typ_pod);
	sf::Texture& zwroc_t(typ_ob);
	sf::Texture& zwroc_t(typ_pos);
	sf::Texture& zwroc_t(typ_dod);
	sf::Texture& zwroc_t(typ_rz typ = typ_rz::pusty);
	sf::Texture& zwroc_t(bool);

	Tmagazyn();
	~Tmagazyn() { delete[] magazyn; };

};

#endif
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>

#include "Vault.h"
#include "Variants.h"

extern bool check;
int toolsCounter{ 12 };
int ilosc_t{ 20 };

Vault::Vault()
{
	srand(time(NULL));
	textures = new sf::Texture[ilosc_t];
	if (!textures[0].loadFromFile("textures/trawa_1.png")	||
		!textures[1].loadFromFile("textures/skrzynia.png")	||
		!textures[2].loadFromFile("textures/d_skrzynia.png")	||
		!textures[3].loadFromFile("textures/blokada.png")	||
		!textures[4].loadFromFile("textures/dostep.png")		||
		!textures[5].loadFromFile("textures/woda.png")		||
		!textures[6].loadFromFile("textures/cobel.png")		||
		!textures[7].loadFromFile("textures/Maciek_n.png")	||
		!textures[8].loadFromFile("textures/Maciek_p.png")	||
		!textures[9].loadFromFile("textures/Maciek_l.png")	||
		//!textures[10].loadFromFile("textures/Maciek_d.png")||
		!textures[11].loadFromFile("textures/Weronika.png")	||
		!textures[12].loadFromFile("textures/w_skrz.png")	||
		!textures[13].loadFromFile("textures/trawa_2.png")	||
		!textures[14].loadFromFile("textures/trawa_3.png")	||
		!textures[15].loadFromFile("textures/drzwi_drew.png")||
		!textures[16].loadFromFile("textures/mikstura_zycia.png")||
		!textures[17].loadFromFile("textures/witraz.png")	||
		!textures[18].loadFromFile("textures/podloze_drewniane.png")||
		!textures[19].loadFromFile("textures/pochodnia.png"))
			check = 1;

	pusty.create(39, 39);
}

sf::Texture& Vault::get(add_v type)
{
	switch (type)
	{
        case add_v::chest_wdw:
            return textures[12];

        case add_v::access:
            return textures[4];

        case add_v::blockade:
            return textures[3];

        default:
            return pusty;
	}
}

sf::Texture& Vault::get(chest_v type) {
    switch (type) {
        case chest_v::wooden:
            return  textures[1];
            
        default:
            return  textures[1];
    }
}

sf::Texture& Vault::get(item_v type)
{
	switch (type)
	{
        case item_v::stained_glass:
            return textures[17];

        case item_v::torch:
            return textures[19];

        default:
            return pusty;
	}
}

sf::Texture& Vault::get(character_v type)
{
	switch (type) {

	case character_v::maciek_n:
		return textures[7];

	case character_v::wera:
		return textures[11];

	case character_v::maciek_p:
		return textures[8];

	case character_v::maciek_l:
		return textures[9];

	default:
		return pusty;
	}
}

sf::Texture& Vault::get(bool a)
{
	if (a)
		return textures[3]; // blokada
	else
		return textures[4]; // dostep
}

sf::Texture& Vault::get(floor_v type)
{
    switch (type) {
    case floor_v::grass:
        return textures[0];

    case floor_v::water:
        return textures[5];

    default:
        return pusty;
    }
}
/*
sf::Texture& Vault::get(typ_pod typ)
{
	switch (typ) 
	{
	int k;
	case typ_pod::trawa:
		k = 1 + rand() % 3;
		if(k == 1)
			return textures[0];
		else if(k == 2)
			return textures[13];
		else if(k == 3)
			return textures[14];

	case typ_pod::cobel:
		return textures[6];

	case typ_pod::woda:
		return textures[5];

	default:
		return pusty;
	}
}


sf::Texture& Vault::get(typ_pod typ)
{
	switch (typ) {
	case typ_pod::trawa:
		return textures[0];

	case typ_pod::cobel:
		return textures[6];

	case typ_pod::woda:
		return textures[5];

	default:
		return pusty;
	}
}
*/

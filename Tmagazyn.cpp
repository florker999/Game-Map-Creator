#include <SFML\Graphics.hpp>
#include <iostream>
#include <cstdlib>

#include "Tmagazyn.h"
#include "typy.h"

extern bool check;
int toolsCounter{ 12 };
int ilosc_t{ 20 };

Tmagazyn::Tmagazyn()
{
	srand(time(NULL));
	magazyn = new sf::Texture[ilosc_t];
	if (!magazyn[0].loadFromFile("textures/trawa_1.png")	||
		!magazyn[1].loadFromFile("textures/skrzynia.png")	||
		!magazyn[2].loadFromFile("textures/d_skrzynia.png")	||
		!magazyn[3].loadFromFile("textures/blokada.png")	||
		!magazyn[4].loadFromFile("textures/dostep.png")		||
		!magazyn[5].loadFromFile("textures/woda.png")		||
		!magazyn[6].loadFromFile("textures/cobel.png")		||
		!magazyn[7].loadFromFile("textures/Maciek_n.png")	||
		!magazyn[8].loadFromFile("textures/Maciek_p.png")	||
		!magazyn[9].loadFromFile("textures/Maciek_l.png")	||
		//!magazyn[10].loadFromFile("textures/Maciek_d.png")||
		!magazyn[11].loadFromFile("textures/Weronika.png")	||
		!magazyn[12].loadFromFile("textures/w_skrz.png")	||
		!magazyn[13].loadFromFile("textures/trawa_2.png")	||
		!magazyn[14].loadFromFile("textures/trawa_3.png")	||
		!magazyn[15].loadFromFile("textures/drzwi_drew.png")||
		!magazyn[16].loadFromFile("textures/mikstura_zycia.png")||
		!magazyn[17].loadFromFile("textures/witraz.png")	||
		!magazyn[18].loadFromFile("textures/podloze_drewniane.png")||
		!magazyn[19].loadFromFile("textures/pochodnia.png"))
			check = 1;

	pusty.create(39, 39);
}

sf::Texture& Tmagazyn::zwroc_t(typ_dod typ)
{
	switch (typ)
	{
	case typ_dod::wSkrz:
		return magazyn[12];

	case typ_dod::dostep:
		return magazyn[4];

	case typ_dod::blokada:
		return magazyn[3];

	default:
		return pusty;
	}
}

sf::Texture& Tmagazyn::zwroc_t(typ_rz typ)
{
	switch (typ)
	{		
	case typ_rz::trawa:
		return magazyn[0];

	case typ_rz::skrzynia:
		return magazyn[1];

	case typ_rz::duza_skrzynia:
		return magazyn[2];

	case typ_rz::blokada:
		return magazyn[3];

	case typ_rz::dostep:
		return magazyn[4];

	case typ_rz::woda:
		return magazyn[5];

	case typ_rz::cobel:
		return magazyn[6];

	case typ_rz::wn_skrz:
		return magazyn[12];

	case typ_rz::drzwi_drew:
		return magazyn[15];

	case typ_rz::mikstura_zycia:
		return magazyn[16];

	case typ_rz::witraz:
		return magazyn[17];

	case typ_rz::podloze_drewniane:
		return magazyn[18];

	case typ_rz::pochodnia:
		return magazyn[19];

	case typ_rz::pusty:
	default:
		return pusty;
	}
}

sf::Texture& Tmagazyn::zwroc_t(typ_pos typ)
{
	switch (typ) {

	case typ_pos::maciek_n:
		return magazyn[7];

	case typ_pos::wera:
		return magazyn[11];

	case typ_pos::maciek_p:
		return magazyn[8];

	case typ_pos::maciek_l:
		return magazyn[9];

	default:
		return pusty;
	}
}

sf::Texture& Tmagazyn::zwroc_t(bool a)
{
	if (a)
		return magazyn[3]; // blokada
	else
		return magazyn[4]; // dostep
}

/*
sf::Texture& Tmagazyn::zwroc_t(typ_pod typ)
{
	switch (typ) 
	{
	int k;
	case typ_pod::trawa:
		k = 1 + rand() % 3;
		if(k == 1)
			return magazyn[0];
		else if(k == 2)
			return magazyn[13];
		else if(k == 3)
			return magazyn[14];

	case typ_pod::cobel:
		return magazyn[6];

	case typ_pod::woda:
		return magazyn[5];

	default:
		return pusty;
	}
}


sf::Texture& Tmagazyn::zwroc_t(typ_pod typ)
{
	switch (typ) {
	case typ_pod::trawa:
		return magazyn[0];

	case typ_pod::cobel:
		return magazyn[6];

	case typ_pod::woda:
		return magazyn[5];

	default:
		return pusty;
	}
}
*/

sf::Texture& Tmagazyn::zwroc_t(typ_ob typ)
{
	switch (typ) {
	case typ_ob::skrzynia:
		return magazyn[1];

	case typ_ob::dSkrzynia:
		return magazyn[2];

	case typ_ob::cobel:
		return magazyn[6];

	case typ_ob::drzwi_drew:
		return magazyn[15];

	default:
		return pusty;
	}
}
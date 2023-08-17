#include "Tile.h"
#include "typy.h"
#include "global.h"

void Tile::zmienRoz(typ_ob t)
{
	switch (t)
	{
	case typ_ob::dSkrzynia:
		wygladOb.setSize(sf::Vector2f(78, 39));
		break;

	case typ_ob::drzwi_drew:
		wygladOb.setSize(sf::Vector2f(39, 78));
		break;
		
	default:
		wygladOb.setSize(sf::Vector2f(39, 39));
		break;
	}
}

void Tile::zmienTeksture(typ_pod t)
{
	if (static_cast<bool>(t))
	{
		wygladPod.setTexture(&mag.zwroc_t(t));
		zmienBlok(t);
	}
	else
		wygladPod.setTexture(NULL);
	typPod = t;
}

void Tile::zmienTeksture(typ_ob t)
{
	zmienRoz(t);
	if (static_cast<bool>(t))
	{
		wygladOb.setTexture(&mag.zwroc_t(t));
		blokada = 1;
		wygladOb.setOrigin(0, wygladOb.getLocalBounds().height);

	}
	else
		wygladOb.setTexture(NULL);
	typOb = t;

}

void Tile::zmienBlok(typ_pod tP)
{
	switch (tP)
	{
	case typ_pod::trawa:
		blokada = 0;
		break;

	default:
		blokada = 1;
	}
}

bool Tile::czyMysz(sf::RenderWindow& w, sf::Vector2f p)
{
	if (wygladPod.getGlobalBounds().contains(p))
		return true;
	else
		return false;
}

void Tile::init(sf::Vector2f p, typ_pod tP, typ_ob tO)
{
	typPod = tP;
	typOb = tO;

	zmienBlok(tP);

	wygladPod.setSize(sf::Vector2f(39, 39));

	zmienRoz(tO);

	

	zmienPoz(p);

	if (static_cast<bool>(typPod))
		zmienTeksture(typPod);
	else
		wygladPod.setTexture(NULL);

	if (static_cast<bool>(typOb))
		zmienTeksture(typOb);
	else
		wygladOb.setTexture(NULL);
	
	wygladPod.setOrigin(0, wygladPod.getLocalBounds().height);
	//wygladOb.setOrigin(0, wygladOb.getLocalBounds().height);
}
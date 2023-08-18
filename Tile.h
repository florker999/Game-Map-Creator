#ifndef TILE_H
#define TILE_H

#include "SFML/Graphics.hpp"
#include "typy.h"
#include "Tmagazyn.h"

class Tile
{

private:

	typ_pod typPod;
	typ_ob typOb;

	bool blokada; // 0 - mozna przejsc; 1 - nie mozna przejsc

public:
	Tile ( );
	Tile ( sf::Vector2f position );

	sf::RectangleShape wygladPod;
	sf::RectangleShape wygladOb;

	void init(sf::Vector2f, typ_pod = typ_pod::pusty, typ_ob = typ_ob::pusty);

	void zmienTeksture(typ_pod);
	void zmienTeksture(typ_ob);
	void zmienTeksture(sf::Texture& t) { wygladPod.setTexture(&t); };

	void zmienPoz(sf::Vector2f p);;

	void zmienTypPod(typ_pod t = typ_pod::pusty) { typPod = t; };
	void zmienTypOb(typ_ob t = typ_ob::pusty) { typOb = t; };

	void zmienRoz(typ_ob);

	void zmienBlok(bool b) { blokada = b; };
	void zmienBlok(typ_pod);

	void resetT() { wygladOb.setTexture(NULL); typOb = typ_ob::pusty; wygladPod.setTexture(NULL); typPod = typ_pod::pusty; zmienBlok(1); };

	bool zwrocBlokade() { return blokada; };

	typ_pod zwrocTypPod() { return typPod; };
	typ_ob zwrocTypOb() { return typOb; };

	bool czyMysz(sf::RenderWindow&, sf::Vector2f);

	sf::Vector2f zwrocPoz() { return wygladPod.getPosition(); };
};

#endif
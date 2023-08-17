#ifndef ITEM_H
#define ITEM_H

#include "SFML/Graphics.hpp"
#include "typy.h"
#include <iostream>

class Item
{

private:

	sf::Sprite wyglad;
	typ_rz Trz;
	bool dostep;

public:
	Item() : dostep(0), Trz(typ_rz::pusty) {};

	Item(const Item& rz) = default;
	Item(Item&& rz) = default;

	// konstruktor, (pozycja != 0,0)
	Item(typ_rz typ, sf::Vector2f p, bool d = 0);

	// konstrukcja obiektu typu polimorficznego
	virtual Item* stworzWg() const { return nullptr; }// zmienic potem na fukncje 
														// czysto wirtualna
	virtual void operator<< (Item* rz);
	void operator= (const Item& rz);
	void operator= (Item&& rz);

	// jesli mozna wejsc - 1, jesli nie - 0
	bool czyDostep() const	 { return dostep; }
	bool czyIstnieje() const { return zwrocTex(); }
	bool czyMysz(sf::Vector2f p);

	void zmienTeksture(const sf::Texture& t)		{ wyglad.setTexture(t); }
	void zmienPolozenie(const sf::Vector2f& poz)	{ wyglad.setPosition(poz); }
	void zmienDostep(bool d)						{ dostep = d; }

	virtual typ_akc akcja() { return typ_akc::nic; }
	
	const sf::Vector2f zwrocPoz() const		{ return wyglad.getPosition(); }
	const sf::Sprite& zwrocSpr() const		{ return wyglad; }
	const sf::Texture* zwrocTex() const		{ return wyglad.getTexture(); }
	const typ_rz zwrocTyp() const			{ return Trz; }
};

#endif
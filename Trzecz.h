#ifndef TRZECZ_H
#define TRZECZ_H

#include "SFML/Graphics.hpp"
#include "typy.h"
#include <iostream>

class Trzecz
{

private:

	sf::Sprite wyglad;
	typ_rz Trz;
	bool dostep;

public:
	Trzecz() : dostep(0), Trz(typ_rz::pusty) {};

	Trzecz(const Trzecz& rz) = default;
	Trzecz(Trzecz&& rz) = default;

	// konstruktor, (pozycja != 0,0)
	Trzecz(typ_rz typ, sf::Vector2f p, bool d = 0);

	// konstrukcja obiektu typu polimorficznego
	virtual Trzecz* stworzWg() const { return nullptr; }// zmienic potem na fukncje 
														// czysto wirtualna
	virtual void operator<< (Trzecz* rz);
	void operator= (const Trzecz& rz);
	void operator= (Trzecz&& rz);

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
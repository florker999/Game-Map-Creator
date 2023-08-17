#include "Chest.h"
#include <iostream>

Chest::Chest(const Chest& inna) : Item(inna)
{
	zawartosc = new ChestWindow();
	material = inna.material;
	stan = inna.stan;
}

Chest::Chest(typ_rz typ, sf::Vector2f p, typ_mat m, int ilosc, Item* wyp) :
	Item(typ, p), material(m), stan(), zawartosc(new ChestWindow(wyp, ilosc))
{
}

Chest::~Chest()
{
	if (zawartosc)
		delete zawartosc;
}

Item* Chest::stworzWg() const
{
	return new Chest(*this);
}

Item* Chest::wyjmijRzecz(sf::Vector2f pM)
{
	return zawartosc->wyjmijRzecz(pM);
}

void Chest::dodajRzecz(const Item& nowa)
{
	if (!zawartosc)
		zawartosc = new ChestWindow();

	zawartosc->dodajRzecz(nowa);
}

void Chest::pokazWnetrze(sf::RenderWindow& okno)
{
	zawartosc->pokazWnetrze(okno);
}

typ_akc Chest::akcja()
{
	if (stan == 0)
	{
		otworz();
		return typ_akc::otw_skrz;
	}
	else if (stan == 1)
	{
		zamknij();
		return typ_akc::zamk_skrz;
	}
	else return typ_akc::nic;
}

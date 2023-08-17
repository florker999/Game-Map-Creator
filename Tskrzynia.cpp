#include "Tskrzynia.h"
#include <iostream>

Tskrzynia::Tskrzynia(const Tskrzynia& inna) : Trzecz(inna)
{
	zawartosc = new Tokno_skrzyni();
	material = inna.material;
	stan = inna.stan;
}

Tskrzynia::Tskrzynia(typ_rz typ, sf::Vector2f p, typ_mat m, int ilosc, Trzecz* wyp) :
	Trzecz(typ, p), material(m), stan(), zawartosc(new Tokno_skrzyni(wyp, ilosc))
{
}

Tskrzynia::~Tskrzynia()
{
	if (zawartosc)
		delete zawartosc;
}

Trzecz* Tskrzynia::stworzWg() const
{
	return new Tskrzynia(*this);
}

Trzecz* Tskrzynia::wyjmijRzecz(sf::Vector2f pM)
{
	return zawartosc->wyjmijRzecz(pM);
}

void Tskrzynia::dodajRzecz(const Trzecz& nowa)
{
	if (!zawartosc)
		zawartosc = new Tokno_skrzyni();

	zawartosc->dodajRzecz(nowa);
}

void Tskrzynia::pokazWnetrze(sf::RenderWindow& okno)
{
	zawartosc->pokazWnetrze(okno);
}

typ_akc Tskrzynia::akcja()
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

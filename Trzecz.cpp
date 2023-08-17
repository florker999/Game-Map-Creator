#include "Trzecz.h"
#include "global.h"

Trzecz::Trzecz(typ_rz typ, sf::Vector2f p, bool d) : dostep(d), Trz(typ)
{
	zmienTeksture(mag.zwroc_t(typ));
	wyglad.setOrigin(0, wyglad.getLocalBounds().height);
	wyglad.setPosition(p);
}

void Trzecz::operator=(const Trzecz& rz)
{
	wyglad = rz.zwrocSpr();
	dostep = rz.czyDostep();
	Trz = rz.zwrocTyp();
}

void Trzecz::operator<<(Trzecz* rz)
{
	*this = *rz;
}

void Trzecz::operator=(Trzecz&& rz)
{
	wyglad = rz.zwrocSpr();
	dostep = rz.czyDostep();
	Trz = rz.zwrocTyp();
}

bool Trzecz::czyMysz(sf::Vector2f p)
{
	if (wyglad.getGlobalBounds().contains(p) )
		return true;
	else
		return false;
}
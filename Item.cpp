#include "Item.h"
#include "global.h"

Item::Item(typ_rz typ, sf::Vector2f p, bool d) : dostep(d), Trz(typ)
{
	zmienTeksture(mag.zwroc_t(typ));
	wyglad.setOrigin(0, wyglad.getLocalBounds().height);
	wyglad.setPosition(p);
}

void Item::operator=(const Item& rz)
{
	wyglad = rz.zwrocSpr();
	dostep = rz.czyDostep();
	Trz = rz.zwrocTyp();
}

void Item::operator<<(Item* rz)
{
	*this = *rz;
}

void Item::operator=(Item&& rz)
{
	wyglad = rz.zwrocSpr();
	dostep = rz.czyDostep();
	Trz = rz.zwrocTyp();
}

bool Item::czyMysz(sf::Vector2f p)
{
	if (wyglad.getGlobalBounds().contains(p) )
		return true;
	else
		return false;
}
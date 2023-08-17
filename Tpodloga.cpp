#include "Tpodloga.h"
#include <iostream>

Tpodloga::Tpodloga(const Tpodloga& p) : Item(p), rzecz(nullptr)
{
    if (p.czyRzecz())
    {
        rzecz = new Item(p.zwrocRzecz());
    }
}

Tpodloga::Tpodloga(Tpodloga&& p) : Item(p), rzecz(nullptr)
{
    if (p.czyRzecz())
    {
        rzecz = &p.zwrocRzecz();
    }
}

Tpodloga::Tpodloga(typ_rz typ, sf::Vector2f p, bool d) : Item(typ, p, d), rzecz(nullptr)
{
    switch (typ)
    {
    case typ_rz::woda:
        zmienDostep(0);
        break;

    default:
        break;
    }
}

#if 0
Tpodloga::Tpodloga(typ_ob typ, sf::Vector2f p, bool d) : Item(typ_pod::pusty, p, d)
{
    switch (typ)
    {
    case typ_ob::cobel:
    case typ_ob::drzwi_drew:
    case typ_ob::dSkrzynia:
    case typ_ob::skrzynia:
        rzecz = new Tskrzynia(typ, p);
    }
}

#endif // 0

Tpodloga::~Tpodloga()
{
    delete rzecz;
    rzecz = nullptr;
}

bool Tpodloga::czyDostep() const
{
    bool d = Item::czyDostep();
    if ( d && rzecz->czyIstnieje())
    {
        return rzecz->czyDostep();
    }
    else return d;
}

void Tpodloga::reset()
{
    if (rzecz)
    {
        delete rzecz;
        rzecz = nullptr;
    }

    zmienTeksture(mag.zwroc_t(typ_pod::pusty));
    zmienDostep(0);
}

void Tpodloga::zmienPolozenie(sf::Vector2f poz)
{
    Item::zmienPolozenie(poz);
    if (czyRzecz())
        rzecz->zmienPolozenie(poz); // dorobic virtual zeby rekurencyjnie
}

void Tpodloga::zmienPrzedmiot(const Item& rz)
{
    delete rzecz;
    rzecz = rz.stworzWg(); // ciekawe czy tu nie bedzie problemow
}

void Tpodloga::operator<<(Item* rz)
{
    Tpodloga* wsk = dynamic_cast<Tpodloga*>(rz);
 
    if (wsk)
        zmienTeksture( *(wsk->zwrocTex()));
    else
    { 
        rzecz = rz->stworzWg(); 
    }
}

void Tpodloga::operator=(const Tpodloga& p)
{  
    if (this == &p)
        return;

    delete rzecz;
    rzecz = nullptr;

    if (p.czyRzecz())
        rzecz = new Item(p.zwrocRzecz());
 
    Item::operator=(p);
}

void Tpodloga::operator=(Tpodloga&& p)
{
    if (this == &p)
        return;

    delete rzecz;
    rzecz = nullptr;
    
    if(p.czyRzecz())
        rzecz = new Item(p.zwrocRzecz());
    Item::operator=(p);
}

Item* Tpodloga::stworzWg() const
{
    return new Tpodloga(*this);
}

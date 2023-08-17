#ifndef TPODLOGA_H
#define TPODLOGA_H

#include "Item.h"
#include "Tskrzynia.h"

class Tpodloga :
    public Item
{
    
private:
    Item* rzecz;
    //Tosoba* osoba;

public:
    Tpodloga() : rzecz(nullptr) {}
    Tpodloga(const Tpodloga& p);
    Tpodloga(Tpodloga&& p);
    Tpodloga(typ_rz typ, sf::Vector2f p, bool d = 1);
    //Tpodloga(typ_ob typ, sf::Vector2f p, bool d = 0);
    ~Tpodloga();

    bool czyRzecz() const { return static_cast<bool>(rzecz); }
    //bool czyOsoba() { return osoba; }
    bool czyDostep() const;

    void reset();
    void zmienPolozenie(sf::Vector2f poz);
    void zmienPrzedmiot(const Item& rz);

    void operator<< (Item* rz) override;
    void operator= (const Tpodloga& p);
    void operator= (Tpodloga&& p);

    Item& zwrocRzecz() const { return *rzecz; }
    Item* stworzWg() const override;
};

#endif
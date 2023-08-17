#ifndef TPODLOGA_H
#define TPODLOGA_H

#include "Trzecz.h"
#include "Tskrzynia.h"
class Tpodloga :
    public Trzecz
{
    
private:
    Trzecz* rzecz;
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
    void zmienPrzedmiot(const Trzecz& rz);

    void operator<< (Trzecz* rz) override;
    void operator= (const Tpodloga& p);
    void operator= (Tpodloga&& p);

    Trzecz& zwrocRzecz() const { return *rzecz; }
    Trzecz* stworzWg() const override;
};

#endif
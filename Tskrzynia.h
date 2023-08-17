#ifndef TSKRZYNIA_H
#define TSKRZYNIA_H

#include "Item.h"
#include "typy.h"
#include "global.h"
#include "Tokno_skrzyni.h"

class Tskrzynia : public Item
{

private:

    Tokno_skrzyni* zawartosc;
    typ_mat material;

    bool stan; // 0 - zamknieta, 1 - otwarta

public:
    
    Tskrzynia(const Tskrzynia& inna);
    Tskrzynia(typ_rz typ, sf::Vector2f p, typ_mat m = typ_mat::drewno, int ilosc = 0, Item* wyp = nullptr);
    ~Tskrzynia();

    Item* stworzWg() const override;
    Item* wyjmijRzecz(sf::Vector2f pM);

    void dodajRzecz(const Item& nowa);
    void zamknij() { stan = 0; }
    void otworz() { stan = 1; if(zawartosc) zawartosc->otwarcie(zwrocPoz()); }
    void pokazWnetrze(sf::RenderWindow& okno);

    bool czyMyszOkno(sf::Vector2f pM) { if (zawartosc) return zawartosc->czyMysz(pM); else return false; }

    typ_akc akcja() override;
};

#endif
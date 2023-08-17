#ifndef TOKNO_SKRZYNI_H
#define TOKNO_SKRZYNI_H

#include "Item.h"
#include "typy.h"
#include "global.h"
#include "SFML/Graphics.hpp"

class Tokno_skrzyni :
    public Item
{

private:
    Item** zawartosc;
    int ilosc_rzeczy;
    static sf::Sprite okienko;

public:

    Tokno_skrzyni() : zawartosc(nullptr), ilosc_rzeczy() {}

    Tokno_skrzyni(Item* nZaw, int ilosc); // argument pierwszy
    ~Tokno_skrzyni();

    int zwrocIloscRz() const { return ilosc_rzeczy; }

    void dodajRzecz(const Item& nowa);
    void otwarcie(sf::Vector2f start);
    void pokazWnetrze(sf::RenderWindow& okno);

    bool czyMysz(sf::Vector2f pM);

    Item* wyjmijRzecz(sf::Vector2f pM);
};

#endif
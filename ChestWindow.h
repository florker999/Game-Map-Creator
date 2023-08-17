#ifndef CHEST_WINDOW_H
#define CHEST_WINDOW_H

#include "Item.h"
#include "typy.h"
#include "global.h"
#include "SFML/Graphics.hpp"

class ChestWindow :
    public Item
{

private:
    Item** zawartosc;
    int ilosc_rzeczy;
    static sf::Sprite okienko;

public:

    ChestWindow() : zawartosc(nullptr), ilosc_rzeczy() {}

    ChestWindow(Item* nZaw, int ilosc); // argument pierwszy
    ~ChestWindow();

    int zwrocIloscRz() const { return ilosc_rzeczy; }

    void dodajRzecz(const Item& nowa);
    void otwarcie(sf::Vector2f start);
    void pokazWnetrze(sf::RenderWindow& okno);

    bool czyMysz(sf::Vector2f pM);

    Item* wyjmijRzecz(sf::Vector2f pM);
};

#endif
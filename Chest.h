#ifndef CHEST_H
#define CHEST_H

#include "Variants.h"
#include "global.h"
#include "ChestWindow.h"

class Chest :
    public Item
{

private:

    ChestWindow* content;

    bool isOpen; // 0 - zamknieta, 1 - otwarta
    int capacity;

public:
    
    Chest(const Chest& targetChest);
    Chest(chest_v type);
    Chest( sf::Vector2f coordinates, chest_v m = chest_v::wooden, bool big = false, Item* newContent = nullptr);
    ~Chest();

    Chest* getChest ( );

    Item* takeOut(sf::Vector2f mouseCoordinates);

    void store(const Item& nowa);
    void close() { stan = 0; }
    void open() { stan = 1; if(zawartosc) zawartosc->otwarcie(getPosition()); }
    void showWindow(sf::RenderWindow& okno);

    bool containsChestWindow(sf::Vector2f mouseCoordinates);

    typ_akc use() override;
};

#endif

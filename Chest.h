#ifndef CHEST_H
#define CHEST_H

#include "Variants.h"
#include "global.h"
#include "ChestWindow.h"

class Chest :
    public Item
{

private:

    ChestWindow window;

    bool isOpen; // 0 - zamknieta, 1 - otwarta
    int capacity;

public:
    
    Chest(const Chest& targetChest);
    Chest(chest_v type);
    Chest( chest_v type, sf::Vector2f coordinates, bool big = false, Item* newContent = nullptr);

    Chest* getChest ( );

    Item* takeOut(sf::Vector2f mouseCoordinates);
    Item* clickedAt ( const sf::Vector2f& coordinates, Item* item = nullptr );

    void close() { isOpen = false; }
    void open() { isOpen = true; window.setPosition(getPosition()); }
    void showWindow(sf::RenderWindow& okno);

    bool containsChestWindow(sf::Vector2f mouseCoordinates);

    action_v use() override;

    Chest* createCopy ( );
};

#endif

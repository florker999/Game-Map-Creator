#ifndef CHEST_WINDOW_H
#define CHEST_WINDOW_H

#include "Variants.h"
#include "global.h"
#include "SFML/Graphics.hpp"
#include "Placeable.h"
#include "Item.h"

class ChestWindow
{
    class Slot {
        Item* item = nullptr;
        int counter = 0;
        sf::RectangleShape square;

    public:
        Slot ( ) { square.setSize ( sf::Vector2f{ 39, 39 } ); square.setOrigin ( 0, 39 ); }
        void setPosition ( sf::Vector2f coordinates ) {
            square.setPosition ( coordinates );
            if ( item ) item->setPosition ( coordinates );
        }

        void setItem ( Item* newItem ) { item = newItem; }
        void drawOn ( sf::RenderWindow& window ) { if ( item ) item->drawOn ( window ); }
        Item* popItem ( ) { Item* tempItem = item; item = nullptr; return tempItem; }
        bool hasItem ( ) { return item == nullptr ? false : true; };
        bool contains ( sf::Vector2f coordinates ) { return square.getGlobalBounds ( ).contains ( coordinates ); }
        sf::Vector2f getPosition ( ) { return square.getPosition ( ); }
    };

private:
    Slot* slots;
    static sf::Sprite window;
    int slotsNumber;
    
    void setSlotsPosition ();
    void drawSlotsOn(sf::RenderWindow& window);
    Slot* findSlot ( sf::Vector2f coordinates );
    bool isItemInSlot(int index);

public:

    ChestWindow(int slotsNumber);
    ChestWindow(int slotsNumber, Item* newContent);
    ~ChestWindow();

    void position(sf::Vector2f start);
    void drawOn(sf::RenderWindow& okno);
    void setPosition ( sf::Vector2f position );
    
    bool contains(sf::Vector2f coordinates);

    Item* store(Item& nowa);
    Item* takeOut(sf::Vector2f coordinates);
};

#endif

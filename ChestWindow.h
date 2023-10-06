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
    private:
        Item* item = nullptr;
        int counter = 0;
        sf::RectangleShape square;
        sf::Text counterText;

        char* numToString ( int num );

    public:
        Slot ( );
        void setPosition ( sf::Vector2f coordinates );
        void setCounterPosition ( sf::Vector2f coordinates );

        void drawOn ( sf::RenderWindow& window );
        Item* setItem ( Item& newItem );
        Item* popItem ( );
        bool hasItem ( );
        bool contains ( sf::Vector2f coordinates );
        sf::Vector2f getPosition ( );
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

    Item* store(Item& nowa, sf::Vector2f);
    Item* takeOut(sf::Vector2f coordinates);
};

#endif

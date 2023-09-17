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
        sf::Text counterText;

    public:
        Slot ( ) { square.setSize ( sf::Vector2f{ 39, 39 } ); square.setOrigin ( 0, 39 ); counterText.setFont ( vault.getFont ( ) ); counterText.setCharacterSize ( 15 ); counterText.setFillColor ( sf::Color::White ); }
        void setPosition ( sf::Vector2f coordinates ) {
            square.setPosition ( coordinates );
            if ( item ) 
            {
                item->setPosition ( coordinates );
                coordinates.y -= 39;
                counterText.setPosition ( coordinates );
                counterText.setString ( char(49+counter) );
            }
        }

        void drawOn ( sf::RenderWindow& window ) 
        { 
            if ( item ) 
            {
                item->drawOn ( window );
                window.draw ( counterText );
            }
        }
        Item* setItem ( Item& newItem );
        Item* popItem ( ) { Item* tempItem = item; item = nullptr; counter--; return tempItem; }
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

    Item* store(Item& nowa, sf::Vector2f);
    Item* takeOut(sf::Vector2f coordinates);
};

#endif

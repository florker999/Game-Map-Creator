#include "ChestWindow.h"
#include "SFML/Graphics.hpp"
#include <iostream>
 
sf::Sprite ChestWindow::window = sf::Sprite(vault.get(add_v::chest_wdw));

ChestWindow::ChestWindow (int slotsNumber) {
    slots = new Slot[9];
    this->slotsNumber = slotsNumber;
}

ChestWindow::ChestWindow(int slotsNumber, Item* newContent)
{
    this->slotsNumber = slotsNumber;
    for (int i = 0; i < slotsNumber; i++) {
        slots[i].setItem(newContent[i ] );
    }
}

ChestWindow::~ChestWindow()
{
	if (slots)
		delete[] slots;
}

void ChestWindow::setSlotsPosition() {
    sf::Vector2f coordinates = window.getPosition();
    coordinates.y += 39;
    for (int i = 0; i < 9; i++) {
        Slot* slot = slots+i;
        if (slot) {
            slot->setPosition(coordinates);
        }
        coordinates.x += 39;
        if (i % 3 == 2)
        {
            coordinates.x -= 117;
            coordinates.y += 39;
        }
    }
}

void ChestWindow::drawSlotsOn(sf::RenderWindow &window) {
    for (int i = 0; i < slotsNumber; i++) {
        slots[i].drawOn(window);
    }
}

ChestWindow::Slot* ChestWindow::findSlot(sf::Vector2f coordinates) {
    std::cout << "item x: " << coordinates.x << " y: " << coordinates.y << std::endl;
    for (int i = 0; i < slotsNumber; i++) {
        std::cout << "slot x: " << slots[ i ].getPosition ( ).x << " y: " << slots[ i ].getPosition ( ).y << std::endl;
        if (slots[i].contains(coordinates)) return slots+i;
    }
    return nullptr;
}

bool ChestWindow::isItemInSlot(int index) {
    return slots[index].hasItem();
}

Item* ChestWindow::store( Item& newItem, sf::Vector2f coord )
{
    Item* returnItem = &newItem;
    Slot* selectedSlot = findSlot ( coord );
    if (selectedSlot) {
        returnItem = selectedSlot->setItem(newItem);
    }
    return returnItem;
}

void ChestWindow::position(sf::Vector2f start)
{
	window.setPosition(start);
    setSlotsPosition();
}

void ChestWindow::drawOn(sf::RenderWindow& window)
{
    position(sf::Vector2f(this->window.getPosition()));
	window.draw(this->window);
    drawSlotsOn(window);
}

void ChestWindow::setPosition(sf::Vector2f position)
{
    window.setPosition(position);
    setSlotsPosition();
}

bool ChestWindow::contains(sf::Vector2f coordinates)
{
    return window.getGlobalBounds().contains(coordinates);
}

Item* ChestWindow::takeOut(sf::Vector2f coordinates)
{
    Slot* selectedSlot = findSlot(coordinates);
    if (selectedSlot) {
        return selectedSlot->popItem();
    } else {
        return nullptr;
    }
}

inline ChestWindow::Slot::Slot ( ) { square.setSize ( sf::Vector2f{ 39, 39 } ); square.setOrigin ( 0, 39 ); counterText.setFont ( vault.getFont ( ) ); counterText.setCharacterSize ( 15 ); counterText.setFillColor ( sf::Color::White ); }

inline void ChestWindow::Slot::setPosition ( sf::Vector2f coordinates ) {
    square.setPosition ( coordinates );
    if ( item )
    {
        item->setPosition ( coordinates );
        coordinates.y -= 39;
        counterText.setPosition ( coordinates );
        counterText.setString ( char ( 50 + counter ) );
    }
}

inline void ChestWindow::Slot::drawOn ( sf::RenderWindow& window )
{
    if ( item )
    {
        item->drawOn ( window );
        window.draw ( counterText );
    }
}

inline Item* ChestWindow::Slot::setItem ( Item& newItem )
{
    if ( item && *item == newItem )
    {
        counter++;
        return &newItem;
    }
    else
    {
        Item* returnItem = popItem ( );
        item = newItem.createCopy ( );
        if ( returnItem ) delete& newItem;
        else returnItem = &newItem;
        return returnItem;
    }
}

inline Item* ChestWindow::Slot::popItem ( ) { Item* tempItem = item; item = nullptr; counter--; return tempItem; }

inline bool ChestWindow::Slot::hasItem ( ) { return item == nullptr ? false : true; }

inline bool ChestWindow::Slot::contains ( sf::Vector2f coordinates ) { return square.getGlobalBounds ( ).contains ( coordinates ); }

inline sf::Vector2f ChestWindow::Slot::getPosition ( ) { return square.getPosition ( ); }


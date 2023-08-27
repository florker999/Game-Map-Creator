#ifndef TPODLOGA_H
#define TPODLOGA_H

#include "Item.h"
#include "Chest.h"
#include "Tile.h"
#include "Variants.h"
#include "Vault.h"

class Floor :
    public Tile
{
    
private:
    //Tosoba* osoba;
    bool walkability;

public:
    Floor() : Tile() {}
    Floor(floor_v type, sf::Vector2f position);
    //Tpodloga(typ_ob typ, sf::Vector2f p, bool d = 0);
    void putInto ( Chest* container ) {}
    bool isWalkable();
    //bool czyOsoba() { return osoba; }
};

#endif

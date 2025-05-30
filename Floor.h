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
    floor_v type;

public:
    Floor ( ) : Tile ( ), walkability{ false }, type{ floor_v::empty } {}
    Floor ( const Floor& target );
    Floor ( floor_v type, sf::Vector2f position = sf::Vector2f{ 39, 39 } );

    Placeable* createCopy (  ) override;
    //Tpodloga(typ_ob typ, sf::Vector2f p, bool d = 0);
    void putInto ( Chest* container ) {}
    bool isWalkable();
    //bool czyOsoba() { return osoba; }

    floor_v getType ( ) { return type; }
};

#endif

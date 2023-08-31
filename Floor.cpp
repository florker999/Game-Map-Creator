#include "Floor.h"
#include <iostream>

Floor::Floor ( const Floor& target ) : Tile ( vault.get ( target.type ), target.getPosition ( ) )
{
    type = target.type;
    walkability = target.walkability;
}

Floor::Floor ( floor_v type, sf::Vector2f position ) : Tile ( vault.get ( type ), position ), type ( type )
{
    switch (type)
    {
        case floor_v::water:
            walkability = false;
        break;
            
        case floor_v::grass:
            walkability = true;
            break;

        default:
            break;
    }
}

Placeable* Floor::createCopy ( )
{
    return new Floor ( *this );
}

bool Floor::isWalkable() {
    return walkability;
}
#if 0
Floor::Floor(typ_ob typ, sf::Vector2f p, bool d) : Item(typ_pod::pusty, p, d)
{
    switch (typ)
    {
    case typ_ob::cobel:
    case typ_ob::drzwi_drew:
    case typ_ob::dSkrzynia:
    case typ_ob::skrzynia:
        rzecz = new Tskrzynia(typ, p);
    }
}

#endif // 0

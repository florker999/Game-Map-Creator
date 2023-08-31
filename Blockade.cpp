#include "Blockade.h"

Blockade::Blockade ( add_v type, sf::Vector2f position ) : Placeable ( vault.get ( type ), position )
{
    if ( type == add_v::access ) blockability = false;
    else blockability = true;
}

bool Blockade::isBlocking ( )
{
    return blockability;
}

Placeable* Blockade::createCopy()
{
    return new Blockade( *this );
}

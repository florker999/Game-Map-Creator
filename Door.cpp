#include "Door.h"

Door::Door ( door_v type, sf::Vector2f position ) : Item ( vault.get ( type ), position )
{
}

Door* Door::createCopy()
{
    return new Door ( *this );
}

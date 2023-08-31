#include "Mixture.h"

Placeable* Mixture::createCopy()
{
    return new Mixture ( *this );
}

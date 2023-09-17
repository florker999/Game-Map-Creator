#include "Mixture.h"

bool Mixture::operator==(const Item& compareItem)
{
    const Mixture* compareMixture = dynamic_cast<const Mixture*>(&compareItem);
    if (compareMixture && health == compareMixture->health) return true;
    return false;
}

Mixture* Mixture::createCopy()
{
    return new Mixture ( *this );
}

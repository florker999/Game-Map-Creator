#include "Mixture.h"

Item* Mixture::stworzWg() const
{
    return new Mixture(*this);
}

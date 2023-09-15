#include "Mixture.h"

Mixture* Mixture::createCopy()
{
    return new Mixture ( *this );
}

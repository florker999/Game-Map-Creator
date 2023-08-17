#include "Tmikstura.h"

Item* Tmikstura::stworzWg() const
{
    return new Tmikstura(*this);
}

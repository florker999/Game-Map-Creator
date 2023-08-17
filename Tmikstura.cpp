#include "Tmikstura.h"

Trzecz* Tmikstura::stworzWg() const
{
    return new Tmikstura(*this);
}

#pragma once

#include "Trzecz.h"

class Tmikstura :
    public Trzecz
{
private:

public:
    Tmikstura() : Trzecz(typ_rz::mikstura_zycia, sf::Vector2f(0, 0), 0) {}
    Tmikstura(typ_rz typ, sf::Vector2f poz, bool d) : Trzecz(typ, poz, d) {}

    Trzecz* stworzWg() const override;
    typ_akc akcja() override { return typ_akc::nic; }
};


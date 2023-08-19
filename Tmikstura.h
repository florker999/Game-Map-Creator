#pragma once

#include "Item.h"

class Tmikstura :
    public Item
{
private:

public:
    Tmikstura() : Item(typ_rz::mikstura_zycia, sf::Vector2f(0, 0), 0) {}
    Tmikstura(typ_rz typ, sf::Vector2f poz, bool d) : Item(typ, poz, d) {}

    Item* stworzWg() const override;
    typ_akc use() override { return typ_akc::nic; }
};


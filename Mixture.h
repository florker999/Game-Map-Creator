#pragma once

#include "Item.h"
#include "typy.h"
#include "global.h"

class Mixture :
    public Item
{
private:

public:
    Mixture() : Item() {}
    Mixture( sf::Vector2f poz ) : Item( poz ) { setTexture(vault.get(typ_rz::mikstura_zycia)); }

    Item* stworzWg() const override;
    typ_akc use() override { return typ_akc::nic; }
};


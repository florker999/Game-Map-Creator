#include "Placeable.h"

Placeable::Placeable ( ) : entity{ sf::Vector2f{39, 39} }
{
    entity.setOrigin(0, 39);
    entity.setTexture ( NULL );
}

Placeable::Placeable( sf::Texture& texture, sf::Vector2f coordinates ) : Placeable() {
    setTexture(texture);
    setPosition(coordinates);
}


void Placeable::drawOn(sf::RenderWindow &window) const {
    window.draw(entity);
}

void Placeable::setTexture(const sf::Texture &t) { 
    entity.setTexture(&t);
}

void Placeable::setPosition(const sf::Vector2f &p) { 
    entity.setPosition(p);
}

 sf::Vector2f Placeable::getPosition ( ) const {
    return entity.getPosition();
}

bool Placeable::contains(sf::Vector2f p) const {
    return entity.getGlobalBounds().contains(p);
}

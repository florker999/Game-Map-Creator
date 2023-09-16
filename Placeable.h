#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class Chest;

class Placeable
{
protected:
    sf::RectangleShape entity;

public:
    Placeable( );
    Placeable ( sf::Texture& texture, sf::Vector2f coordinates = sf::Vector2f ( 0, 0 ) );

    virtual Placeable* createCopy (  ) = 0;
    
    void drawOn (sf::RenderWindow& window) const;
	void setTexture ( const sf::Texture& t );
	void setPosition ( const sf::Vector2f& p );
    
    sf::Vector2f getPosition( ) const;
    
    bool contains ( sf::Vector2f p ) const;
};


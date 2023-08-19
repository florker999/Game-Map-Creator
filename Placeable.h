#pragma once
#include "SFML/Graphics.hpp"

class Placeable
{
public:
	virtual void setTexture ( sf::Texture& t ) = 0;
	virtual void setPosition ( sf::Vector2f p ) = 0;
};


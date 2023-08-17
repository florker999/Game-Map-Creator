#ifndef FPORTAL_H
#define FPORTAL_H

#include "Tile.h"

struct Fportal
{
	// zapis mapy
	void operator<< (Tile[]);
	// wczytanie mapy
	void operator>> (Tile[]);

	// zapis blokad
	void operator() (Tile*, int);
	// wczytanie blokad
	int operator() (Tile*);

};

#endif
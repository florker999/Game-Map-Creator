#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <fstream>
#include <iostream>
#include <vector>

#include "typy.h"
#include "Tmagazyn.h"
#include "Chest.h"
#include "Tpodloga.h"
#include "Tmikstura.h"
#include "global.h"
#include "Fportal.h"
#include "Tile.h"
#include "Board.h"

extern int toolsCounter;
constexpr int tilesCounter{ 416 };
bool check{ 0 };


sf::Texture& Tmagazyn::zwroc_t(typ_pod type)
{
	switch (type) {
	case typ_pod::trawa:
		return magazyn[0];

	case typ_pod::woda:
		return magazyn[5];

	default:
		return pusty;
	}
}


/////////////////////////////////////

class Creator
{
public:
	// main window
	sf::RenderWindow window;

	// a strip separating the tool bar
	sf::RectangleShape wall;
	
	// tools container
	std::vector<Item*> tools;

	// chosen tool pointer
	Item* currentTool;

	// chosen chest pointer
	Chest* currentChest;

	// tiles
	Board* currentBoard;
	Tpodloga tiles[tilesCounter];	

	// blockades container
	Tile* blockades;				

	void run();
	Creator();

private:

	void update ( );
	void render ( );
	void process ( );

	void rubTile ( );
	void fillTile ( );
	void useObject ( );
	void setBlockade ( );
	void setMousePos ( );
	void chooseTool ( sf::Vector2f );
	void useChest ( const sf::Vector2f& mouseCoordinates );

	int findBlockadeIndex ( int tile );

	bool isLpm;			// lewy przycisk myszy
	bool isPpm;			// prawy przycisk myszy
	bool isRubber;		// gumka
	bool isDestroyer;	// niszczyciel
	bool isBlockade;	// blokada
	bool blockadeType;	// rodzaj blokady
	bool key;

	typ_akc action;

	int mouseTilePos;
	int blockadesCounter;
	int boardsCounter;

#if 0 
	void zapisz();
	void wczytaj();
	void zapiszBlok();
	void wczytajBlok();
#endif
};

Creator::Creator ( ) :
	window ( sf::VideoMode ( 1094, 624, 32 ), "Map creator", sf::Style::Close ),
	isLpm ( 0 ), isPpm ( 0 ), mouseTilePos ( 0 ), isRubber ( 0 ), isDestroyer ( 0 ), key ( 0 ), isBlockade ( 0 ),
	blockades ( nullptr ), blockadesCounter ( 0 ), blockadeType ( 0 ), currentTool ( nullptr ), currentChest ( nullptr ),
	action ( typ_akc::nic ), boardsCounter ( 1 ), currentBoard ( new Board ( tilesCounter ) )
{

	// setting the tools/floors/objects to take
	std::vector<Item*> tymW =
	{
		{ new Tpodloga(typ_rz::trawa, sf::Vector2f(1016, 39), 0) },		// blockade
		{ new Tpodloga(typ_rz::trawa, sf::Vector2f(1055, 39), 1) },		// access
		{ new Tpodloga(typ_rz::trawa, sf::Vector2f(1016, 78), 1) },		// grass
		{ new Chest(typ_rz::skrzynia, sf::Vector2f(1055, 78)) },	// chest
		{ new Chest(typ_rz::duza_skrzynia, sf::Vector2f(1016, 117)) },// big chest
		{ new Tpodloga(typ_rz::woda, sf::Vector2f(1016, 156), 0) },		// water
		{ new Tpodloga(typ_rz::cobel, sf::Vector2f(1055, 156)) },		// cobbelstone
		{ new Chest(typ_rz::drzwi_drew, sf::Vector2f(1016, 234)) },	// wooden door
		{ new Tmikstura(typ_rz::mikstura_zycia, sf::Vector2f(1055, 195), 1)}, // life mixture
		{ new Tpodloga(typ_rz::podloze_drewniane, sf::Vector2f(1055, 234))}, // wooden floor
		{ new Chest(typ_rz::witraz, sf::Vector2f(1016, 273)) },		// stained glass
		{ new Chest(typ_rz::pochodnia, sf::Vector2f(1055, 273))}	// fire torch
	};
	tools = tymW;

	tools[0]->zmienTeksture(mag.zwroc_t(typ_rz::blokada));
	tools[1]->zmienTeksture(mag.zwroc_t(typ_rz::dostep));

	// building the this.wall strip
	wall.setFillColor(sf::Color::Blue);
	wall.setSize(sf::Vector2f(2, 624));
	wall.setPosition(1014, 0);

	// position of a new tile
	sf::Vector2f position(0, 39);
	sf::Vector2f mouseCoordinates(sf::Mouse::getPosition(window));

	setMousePos ( );

	// dividing the window into tiles
	for (int i = 0; i < tilesCounter; i++)
	{
		tiles[i] = Tpodloga(typ_rz::pusty, position, 0 );
		position.x += 39;

		// iterating to next tile
		if (position.x > 975) {
			position.x = 0;
			position.y += 39;
		}

		// determining the beginning position of the mouse
		if (tiles[i].czyMysz(mouseCoordinates))
			mouseTilePos = i;
	}
	/*
	wczytaj();
	wczytajBlok();
	*/
}

void Creator::run()
{
	while (window.isOpen())
	{
		process();
		update();
		render();
	}
}

void Creator::process()
{
	sf::Event e;
	if (window.pollEvent(e)) // Should it not be changed to a loop!?
	{
		switch (e.type)
		{
			// close app
		case sf::Event::Closed:
			/*
			zapiszBlok();
			zapisz();
			*/

			delete[] blockades;
			delete currentTool;

			currentTool = nullptr;
			blockades = nullptr;

			window.close();
			break;

			// pressed mouse
		case sf::Event::MouseButtonPressed:
			if		(sf::Mouse::isButtonPressed(sf::Mouse::Left))
				isLpm = 1;
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
				isPpm = 1;
			break;

			// released mouse
		case sf::Event::MouseButtonReleased:
			isLpm = 0;
			isPpm = 0;
			break;

			// moved mouse
		case sf::Event::MouseMoved:
		{
			setMousePos ( );
		}
		break;

			// pressed key
		case sf::Event::KeyPressed:
			key = 1;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
			{
				if (!isRubber)
					isRubber = 1;
				else
					isRubber = 0;
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
				isDestroyer = 1;
			break;

			// released key
		case sf::Event::KeyReleased:
			key = 0;
			break;
		}
	}
}

void Creator::setMousePos ( )
{
	sf::Vector2f mouseCoordinates ( sf::Mouse::getPosition ( window ) );
	if ( tiles[ mouseTilePos ].czyMysz ( mouseCoordinates ) == false )
	{
		for ( int b = 0; b < tilesCounter; b++ )
		{
			if ( tiles[ b ].czyMysz ( mouseCoordinates ) )
			{
				mouseTilePos = b;
				break;
			}
		}
	}
}

void Creator::update()
{
	sf::Vector2f mouseCoordinates(sf::Mouse::getPosition(window));

	// turning off the tool, rubber replaces the tools
	if (isPpm || (isRubber && currentTool))
	{
		delete currentTool;
		currentTool = nullptr;
		if (isPpm)
			isRubber = 0;
		isPpm = 0;
		isBlockade = 0;
	}

	if (isLpm)
	{
		// actions on the board
		if ( mouseCoordinates.x < 1014 )
		{
			// filling a tile
			if (currentTool && !isBlockade && ((currentChest && !currentChest->czyMyszOkno(mouseCoordinates)) || !currentChest ))
			{
				fillTile();
			}

			// setting up a blockade
			else if ( isBlockade == true)
			{
				setBlockade();
			}

			// rubbing a tile
			else if (isRubber)
			{
				rubTile();
			}

			// using an object
			else if (!currentTool && tiles[mouseTilePos].czyRzecz())
			{
				useObject ( );
			}

			// add or remove an item from a chest
			else if (currentChest && currentChest->czyMyszOkno(mouseCoordinates)) // jesli skrzynia jest otwarta
			{
				useChest ( mouseCoordinates );
			}
		}
		else
		{
			// choosing a tool
			if (sf::FloatRect(1016, 0, 78, 624).contains(mouseCoordinates))
			{
				chooseTool(mouseCoordinates);
			}
		}
	}

	// destroy all the tiles
	if (isDestroyer)
	{
		for (int a = 0; a < tilesCounter; a++)
			tiles[a].reset();

		isDestroyer = 0;

		delete[] blockades;
		blockades = nullptr;
		blockadesCounter = 0;

		currentChest = nullptr;
	}

	// move the tool
	if (currentTool)
	{
		currentTool->zmienPolozenie(tiles[mouseTilePos].zwrocPoz());
	}
}

void Creator::useChest ( const sf::Vector2f& mouseCoordinates )
{
	if ( currentTool )	// if a tool is chosen, it will be added to the chest
	{
		currentChest->dodajRzecz ( *currentTool );
	}
	else				// otherwise a tool will be removed from the chest
	{
		if ( Item* wsk = currentChest->wyjmijRzecz ( mouseCoordinates ) )
		{
			delete currentTool;
			currentTool = wsk;
		}
	}
	isLpm = 0;
}

int Creator::findBlockadeIndex ( int tileNumber )
{
	const sf::Vector2f tileCoordinates = tiles[ tileNumber ].zwrocPoz ( );
	for (int a = 0; a < blockadesCounter; a++ )
	{
		if ( tileCoordinates == blockades[ a ].zwrocPoz ( ) )
			return a;
	}
	return -1;
}

void Creator::useObject ( )
{
	action = tiles[ mouseTilePos ].zwrocRzecz ( ).akcja ( );

	switch ( action )
	{
	case typ_akc::otw_skrz:
		currentChest = dynamic_cast<Chest*>( &tiles[ mouseTilePos ].zwrocRzecz ( ) );
		break;

	case typ_akc::zamk_skrz:
		currentChest = nullptr;
		break;

	default:
		break;
	}
	isLpm = 0;
	action = typ_akc::nic;
}

void Creator::render()
{
	// board window
	window.clear();
	window.draw(wall);

	for (auto w : tools)
	{
		window.draw(w->zwrocSpr());
	}

	// drawing the tiles
	for (int a = 0; a < tilesCounter; a++)
	{
			window.draw(tiles[a].zwrocSpr());
	}

	for (int a = 0; a < tilesCounter ; a++)
	{
		if ( tiles[a].czyRzecz() )
			window.draw(tiles[a].zwrocRzecz().zwrocSpr());
	}

	if (blockades)
	{
		for (int a = 0; a < blockadesCounter; a++)
			window.draw(blockades[a].wygladPod);
	}
	
	// drawing the chest window if open
	if (currentChest)
	{
		currentChest->pokazWnetrze(window);
	}

	// drawing the tool
	if (currentTool && sf::Mouse::getPosition(window).x < 1092)
	{
		window.draw(currentTool->zwrocSpr());
	}


	window.display();
	std::cout << check << " " << mouseTilePos << std::endl;
}

#if 0
void Creator::zapisz()
{
	std::ofstream mapa("mapa.txt");
	int b = 0;

	// zapis typu podloza
	for (int a = 0; a < 16; a++)
	{
		for (int a = 0; a < 26; a++)
			mapa << static_cast<int>(tiles[b++].zwrocTypPod()) << " ";
		mapa << '\n';
	}

	b = 0;
	mapa << '\n';

	// zapis typu obiektu
	for (int a = 0; a < 16; a++)
	{
		for (int a = 0; a < 26; a++)
			mapa << static_cast<int>(tiles[b++].zwrocTypOb()) << " ";
		mapa << '\n';
	}

	b = 0;
	mapa << '\n';

	// zapis blokady
	for (int a = 0; a < 16; a++)
	{
		for (int a = 0; a < 26; a++)
			mapa << tiles[b++].zwrocBlokade() << " ";
		mapa << '\n';
	}

	mapa.close();
}

void Creator::wczytaj()
{
	std::ifstream mapa("mapa.txt");

	typ_pod tp;
	typ_ob to;

	int b;
	int i = 0;
	bool blok;

	//wczytanie typu podloza
	for (int a = 0; a < 26; a++)
	{
		for (int a = 0; a < 16; a++)
		{
			if (mapa.good())
				mapa >> b;
			else
				b = 0;

			switch (b)
			{
			case 1:
				tp = typ_pod::trawa;
				break;

			case 2:
				tp = typ_pod::woda;
				break;

			default:
				tp = typ_pod::pusty;
			}
			tiles[i++].zmienTeksture(tp);
		}
	}

	i = 0;

	//wczytanie typu obiektu
	for (int a = 0; a < 26; a++)
	{
		for (int a = 0; a < 16; a++)
		{
			if (mapa.good())
				mapa >> b;
			else
				b = 0;

			switch (b)
			{
			case 1:
				to = typ_ob::skrzynia;
				break;

			case 2:
				to = typ_ob::dSkrzynia;
				break;

			case 3:
				to = typ_ob::cobel;
				break;

			case 4:
				to = typ_ob::drzwi_drew;
				break;

			default:
				to = typ_ob::pusty;
			}
			tiles[i++].zmienTeksture(to);
		}
	}

	i = 0;
	//wczytanie blokady
	if (!mapa.good())
	{
		for (int a = 0; a < 416; a++)
			tiles[a].zmienBlok(1);
	}
	else
	{
		for (int a = 0; a < 26; a++)
		{
			for (int a = 0; a < 16; a++)
			{
				mapa >> blok;
				tiles[i++].zmienBlok(blok);

			}
		}
	}

	mapa.close();
}

void Creator::zapiszBlok()
{
	if (blockadesCounter)
	{
		std::ofstream pB("specBlok.txt");
		pB << blockadesCounter << '\n';
		for (int a = 0; a < blockadesCounter; a++)
			pB << blockades[a].zwrocPoz().x << " " << blockades[a].zwrocPoz().y << " " << blockades[a].zwrocBlokade() << '\n';
		pB.close();
	}
}

void Creator::wczytajBlok()
{
	std::ifstream pB;
	pB.open("specBlok.txt");
	if (pB.good())
	{
		pB >> blockadesCounter;
		blockades = new Tile[blockadesCounter];
		for (int a = 0; a < blockadesCounter; a++)
		{
			sf::Vector2f pozB;
			bool z;
			pB >> pozB.x >> pozB.y >> z;
			blockades[a].init(pozB);
			blockades[a].zmienBlok(z);
			blockades[a].zmienTeksture(mag.zwroc_t(z));
		}
		pB.close();
	}
}




#endif // 0
/////////////////////////////////////
void Creator::fillTile()
{
	if (currentChest)
	{
		currentChest->zamknij();
		currentChest = nullptr;
	}

	tiles[ mouseTilePos ] << currentTool;

	if (blockadesCounter)
	{
		// looking up if a tile had a blockade
		int blockadeIndex = findBlockadeIndex ( mouseTilePos );
		if ( blockadeIndex > -1 )
		{
			blockadesCounter--;
			Tile* prevBlockades = blockades;
			if (blockadesCounter > 0)
			{
				// copying all the blockades but the found one
				Tile* n_blok = new Tile[blockadesCounter];
				int i = 0;
				for (int b = 0; b < blockadesCounter; b++)
				{
					if (b != blockadeIndex)
						n_blok[b] = blockades[i];
					i++;
				}
				blockades = n_blok;
			}
			else
			{
				blockades = nullptr;
			}
			delete[] prevBlockades;
		}
	}
}

void Creator::setBlockade()
{
	if (blockades == nullptr)
	{
		blockades = new Tile[++blockadesCounter];
		blockades->init(tiles[mouseTilePos].zwrocPoz());
		blockades->zmienTeksture(mag.zwroc_t(blockadeType));
	}
	else
	{
		int blockadeIndex = findBlockadeIndex ( mouseTilePos );
		if ( blockadeIndex == -1 )
		{
			Tile* newBlockades = new Tile[++blockadesCounter];
			for (int a = 0; a < blockadesCounter - 1; a++)
				newBlockades[a] = blockades[a];
			newBlockades[blockadesCounter - 1].init(tiles[mouseTilePos].zwrocPoz());
			newBlockades[blockadesCounter - 1].zmienTeksture(mag.zwroc_t(blockadeType));

			delete[] blockades;
			blockades = newBlockades;
		}
		else
		{
			blockades[blockadeIndex].zmienBlok(blockadeType);
			blockades[blockadeIndex].zmienTeksture(mag.zwroc_t(blockadeType));
		}
	}
	tiles[mouseTilePos].zmienDostep(blockadeType);
}

void Creator::chooseTool(sf::Vector2f mouseCoordinates)
{
	for (int a = 0; a < toolsCounter; a++)
	{
		if (tools[a]->czyMysz(mouseCoordinates))
		{
			/*
			if (currentChest)
			{
				currentChest->zamknij();
				currentChest = nullptr;
			}
			*/
			delete currentTool;
			currentTool = tools[a]->stworzWg();
			isBlockade = 0;
			if (a <= 1) // wybranie blokady
			{
				isBlockade = 1;
				if (a == 1) blockadeType = false;
				else blockadeType = true;
			}

			isRubber = 0;
			isLpm = 0;
			break;
		}
	}
}

void Creator::rubTile()
{
	if (currentChest)
	{
		currentChest->zamknij();
		currentChest = nullptr;
	}
	tiles[mouseTilePos].reset();

	if (blockadesCounter)
	{
		bool foundBlockade = 0;
		int a;
		for (a = 0; a < blockadesCounter; a++)
		{
			if (tiles[mouseTilePos].zwrocPoz() == blockades[a].zwrocPoz())
			{
				foundBlockade = 1;
				break;
			}
		}
		if (foundBlockade)
		{
			if (--blockadesCounter)
			{
				Tile* n_blok = new Tile[blockadesCounter];
				int b;
				int i = 0;
				for (b = 0; b < blockadesCounter; b++)
				{
					if (b != a)
						n_blok[b] = blockades[i];
					else
						n_blok[b] = blockades[++i];
					i++;
				}
				delete[] blockades;
				blockades = n_blok;
			}
			else
			{
				delete[] blockades;
				blockades = nullptr;
			}
		}
	}
	// isLpm = 0;
}

int main()
{
	Creator Creator;
	Creator.run();
	return check;
}
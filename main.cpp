#include <fstream>
#include <iostream>
#include <vector>

#include "Variants.h"
#include "Vault.h"
#include "Chest.h"
#include "Floor.h"
#include "Mixture.h"
#include "global.h"
#include "Tile.h"
#include "Board.h"
#include "Blockade.h"
#include "Door.h"
#include "Wall.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

extern int toolsCounter;
constexpr int tilesCounter{ 416 };
bool check{ 0 };


/////////////////////////////////////

class Creator
{
public:
	// main window
	sf::RenderWindow window;

	// a strip separating the tool bar
	sf::RectangleShape wall;
	
	// tools container
	std::vector<Placeable*> tools;

	// chosen tool pointer
	Placeable* currentTool;

	// chosen chest pointer
	Chest* currentChest;

	// tiles
	Board* currentBoard;
    
	// blockades container
	Tile* blockades;				

	void run();
	Creator();

private:

	void update ( );
	void render ( );
	void process ( );

	void fillTile ( );
	void rubSquare ( );
	void useObject ( );
	void setMousePos ( );
	void chooseTool ( sf::Vector2f& mouseCoordinates );
	void useChest ( const sf::Vector2f& mouseCoordinates );
	void setAddAccess ( );

	int findBlockadeIndex ( int tile );

	bool isLpm;			// lewy przycisk myszy
	bool isPpm;			// prawy przycisk myszy
	bool isRubber;		// gumka
	bool isDestroyer;	// niszczyciel
	bool isBlockade;	// blokada
	bool blockadeType;	// rodzaj blokady
	bool key;

	action_v action;

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
	action ( action_v::nothing ), boardsCounter ( 1 ), currentBoard ( new Board ( tilesCounter ) )
{
	// setting the tools/floors/objects to take
	std::vector<Placeable*> tymW =
	{
		new Blockade ( add_v::blockade, sf::Vector2f ( 1016, 39 ) ) ,		// blockade
		new Blockade ( add_v::access, sf::Vector2f ( 1055, 39 ) ) ,		// access
		new Floor(floor_v::grass, sf::Vector2f(1016, 78)) ,		// grass
		new Chest(chest_v::wooden, sf::Vector2f(1055, 78)) ,	        // chest
		new Chest(chest_v::wooden, sf::Vector2f(1016, 117), true) ,     // big chest
		new Floor(floor_v::water, sf::Vector2f(1016, 156)) ,		// water
		new Wall(wall_v::cobelstone, sf::Vector2f(1055, 156)) ,		    // cobbelstone wall
		new Door(door_v::wooden, sf::Vector2f(1016, 234)) ,	    // wooden door
		new Mixture( sf::Vector2f(1055, 195) ),                         // life mixture
		new Wall(wall_v::wood, sf::Vector2f(1055, 234)), // wooden wall
        //new Item(item_v::stained_glass, sf::Vector2f(1016, 273)) ,		    // stained glass
        //new Item(item_v::torch, sf::Vector2f(1055, 273))	        // fire torch
	};
	tools = tymW;

	tools[ 0 ]->setTexture ( vault.get ( add_v::blockade ) );
	tools[ 1 ]->setTexture ( vault.get ( add_v::access ) );

	// building the this.wall strip
	wall.setFillColor ( sf::Color::Blue );
	wall.setSize ( sf::Vector2f ( 2, 624 ) );
	wall.setPosition ( 1014, 0 );

	// position of a new tile
	sf::Vector2f position(0, 39);
	sf::Vector2f mouseCoordinates(sf::Mouse::getPosition(window));

	setMousePos ( );
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
	if ( mouseCoordinates.x < 1014 )
	{
		mouseTilePos = currentBoard->findMousePos ( mouseCoordinates );
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
			if ( currentTool && !isBlockade && ( ( currentChest && !currentChest->containsChestWindow ( mouseCoordinates ) ) || !currentChest ) )
			{
				fillTile ( );
			}

			// setting up a blockade
			else if ( isBlockade )
			{
				setAddAccess ( );
			}

			// rubbing a tile
			else if ( isRubber )
			{
				rubSquare ( );
			}

			// using an object
			else if ( !currentTool && currentBoard->hasItemOnSquare(mouseTilePos) )
			{
				useObject ( );
			}

			// add or remove an item from a chest
			else if ( currentChest && currentChest->containsChestWindow ( mouseCoordinates ) )
			{
				useChest ( mouseCoordinates );
			}
		}
		else
		{
			// choosing a tool
			if ( sf::FloatRect ( 1016, 0, 78, 624 ).contains ( mouseCoordinates ) )
			{
				chooseTool ( mouseCoordinates );
			}
		}
	}

	// destroy all the tiles
	if ( isDestroyer )
	{
		for (int a = 0; a < tilesCounter; a++)
            currentBoard->resetSquare(mouseTilePos);
		isDestroyer = 0;

		delete[] blockades;
		blockades = nullptr;
		blockadesCounter = 0;

		currentChest = nullptr;
	}

	// move the tool
	if ( currentTool )
	{
		currentTool->setPosition ( currentBoard->getCoordinatesOnSquare ( mouseTilePos ) );
	}
}

void Creator::useChest ( const sf::Vector2f& mouseCoordinates )
{
	currentTool = currentChest->clickedAt ( mouseCoordinates, dynamic_cast< Item* >( currentTool ) );
	isLpm = 0;
}

int Creator::findBlockadeIndex ( int tileNumber )
{
	const sf::Vector2f tileCoordinates = currentBoard->getCoordinatesOnSquare ( tileNumber );
	for (int a = 0; a < blockadesCounter; a++ )
	{
		if ( tileCoordinates == blockades[ a ].getPosition ( ) )
			return a;
	}
	return -1;
}

void Creator::useObject ( )
{
	action = currentBoard->useItemOnSquare ( mouseTilePos );

	switch ( action )
	{
	case action_v::open_ch:
		currentChest = dynamic_cast< Chest* >( currentBoard->getItemOnSquare ( mouseTilePos ) );
		break;

	case action_v::close_ch:
		currentChest = nullptr;
		break;

	default:
		break;
	}
	isLpm = 0;
	action = action_v::nothing;
}

void Creator::render()
{
	// board window
	window.clear ( sf::Color::Black );
	window.draw(wall);

	for (auto tool : tools)
	{
        tool->drawOn(window);
	}

	// drawing the tiles
	currentBoard->drawOn ( window );
	
	// drawing the chest window if open
	if (currentChest)
	{
		currentChest->showWindow(window);
	}

	// drawing the tool
	if (currentTool && sf::Mouse::getPosition(window).x < 1092)
	{
        currentTool->drawOn(window);
	}


	window.display();
	//std::cout << check << " " << mouseTilePos << std::endl;
}

void Creator::fillTile()
{
	if (currentChest)
	{
		currentChest->close();
		currentChest = nullptr;
	}

	currentBoard->setSquare ( mouseTilePos, currentTool );
}

void Creator::setAddAccess ( )
{
	currentBoard->setAddAccessOnSquare ( mouseTilePos, blockadeType );
}

void Creator::chooseTool ( sf::Vector2f& mouseCoordinates )
{
	for (int i = 0; i < toolsCounter; i++)
	{
		if ( tools[ i ]->contains ( mouseCoordinates ) )
		{
			/*
			if (currentChest)
			{
				currentChest->zamknij();
				currentChest = nullptr;
			}
			*/
			if (currentTool != nullptr ) delete currentTool;
			currentTool = tools[i]->createCopy();
			isBlockade = 0;
			if (i <= 1) // wybranie blokady
			{
				isBlockade = 1;
				if (i == 1) blockadeType = false;
				else blockadeType = true;
			}

			isRubber = 0;
			isLpm = 0;
			break;
		}
	}
}

void Creator::rubSquare ()
{
	if (currentChest)
	{
		currentChest->close();
		currentChest = nullptr;
	}
	currentBoard->resetSquare ( mouseTilePos );
}

int main()
{
	Creator Creator;
	Creator.run();
	return check;
}

#if 0
void Creator::zapisz ( )
{
	std::ofstream mapa ( "mapa.txt" );
	int b = 0;

	// zapis typu podloza
	for ( int a = 0; a < 16; a++ )
	{
		for ( int a = 0; a < 26; a++ )
			mapa << static_cast< int >( tiles[ b++ ].zwrocTypPod ( ) ) << " ";
		mapa << '\n';
	}

	b = 0;
	mapa << '\n';

	// zapis typu obiektu
	for ( int a = 0; a < 16; a++ )
	{
		for ( int a = 0; a < 26; a++ )
			mapa << static_cast< int >( tiles[ b++ ].zwrocTypOb ( ) ) << " ";
		mapa << '\n';
	}

	b = 0;
	mapa << '\n';

	// zapis blokady
	for ( int a = 0; a < 16; a++ )
	{
		for ( int a = 0; a < 26; a++ )
			mapa << tiles[ b++ ].zwrocBlokade ( ) << " ";
		mapa << '\n';
	}

	mapa.close ( );
}

void Creator::wczytaj ( )
{
	std::ifstream mapa ( "mapa.txt" );

	typ_pod tp;
	typ_ob to;

	int b;
	int i = 0;
	bool blok;

	//wczytanie typu podloza
	for ( int a = 0; a < 26; a++ )
	{
		for ( int a = 0; a < 16; a++ )
		{
			if ( mapa.good ( ) )
				mapa >> b;
			else
				b = 0;

			switch ( b )
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
			tiles[ i++ ].zmienTeksture ( tp );
		}
	}

	i = 0;

	//wczytanie typu obiektu
	for ( int a = 0; a < 26; a++ )
	{
		for ( int a = 0; a < 16; a++ )
		{
			if ( mapa.good ( ) )
				mapa >> b;
			else
				b = 0;

			switch ( b )
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
			tiles[ i++ ].zmienTeksture ( to );
		}
	}

	i = 0;
	//wczytanie blokady
	if ( !mapa.good ( ) )
	{
		for ( int a = 0; a < 416; a++ )
			tiles[ a ].zmienBlok ( 1 );
	}
	else
	{
		for ( int a = 0; a < 26; a++ )
		{
			for ( int a = 0; a < 16; a++ )
			{
				mapa >> blok;
				tiles[ i++ ].zmienBlok ( blok );

			}
		}
	}

	mapa.close ( );
}

void Creator::zapiszBlok ( )
{
	if ( blockadesCounter )
	{
		std::ofstream pB ( "specBlok.txt" );
		pB << blockadesCounter << '\n';
		for ( int a = 0; a < blockadesCounter; a++ )
			pB << blockades[ a ].zwrocPoz ( ).x << " " << blockades[ a ].zwrocPoz ( ).y << " " << blockades[ a ].zwrocBlokade ( ) << '\n';
		pB.close ( );
	}
}

void Creator::wczytajBlok ( )
{
	std::ifstream pB;
	pB.open ( "specBlok.txt" );
	if ( pB.good ( ) )
	{
		pB >> blockadesCounter;
		blockades = new Tile[ blockadesCounter ];
		for ( int a = 0; a < blockadesCounter; a++ )
		{
			sf::Vector2f pozB;
			bool z;
			pB >> pozB.x >> pozB.y >> z;
			blockades[ a ].init ( pozB );
			blockades[ a ].zmienBlok ( z );
			blockades[ a ].zmienTeksture ( mag.get ( z ) );
		}
		pB.close ( );
	}
}




#endif // 0
/////////////////////////////////////
#include <fstream>

#include "Fportal.h"
#include "Tmagazyn.h"
#include "typy.h"
#include "global.h"
#include "Tile.h"

void Fportal::operator<< (Tile kafelek[])
{
	std::ofstream mapa("mapa.txt");
	int b = 0;

	// zapis typu podloza
	for (int a = 0; a < 16; a++)
	{
		for (int a = 0; a < 26; a++)
			mapa << static_cast<int>(kafelek[b++].zwrocTypPod()) << " ";
		mapa << '\n';
	}

	b = 0;
	mapa << '\n';

	// zapis typu obiektu
	for (int a = 0; a < 16; a++)
	{
		for (int a = 0; a < 26; a++)
			mapa << static_cast<int>(kafelek[b++].zwrocTypOb()) << " ";
		mapa << '\n';
	}

	b = 0;
	mapa << '\n';

	// zapis blokady
	for (int a = 0; a < 16; a++)
	{
		for (int a = 0; a < 26; a++)
			mapa << kafelek[b++].zwrocBlokade() << " ";
		mapa << '\n';
	}

	mapa.close();
}

void Fportal::operator>>(Tile kafelek[])
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
			kafelek[i++].zmienTeksture(tp);
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

			default:
				to = typ_ob::pusty;
			}
			kafelek[i++].zmienTeksture(to);
		}
	}

	i = 0;
	//wczytanie blokady
	if (!mapa.good())
	{
		for (int a = 0; a < 416; a++)
			kafelek[a].zmienBlok(1);
	}
	else
	{
		for (int a = 0; a < 26; a++)
		{
			for (int a = 0; a < 16; a++)
			{
				mapa >> blok;
				kafelek[i++].zmienBlok(blok);

			}
		}
	}

	mapa.close();
}

void Fportal::operator() (Tile* blokady, int ilosc_blok)
{
	if (ilosc_blok)
	{
		std::ofstream pB("specBlok.txt");
		pB << ilosc_blok << '\n';
		for (int a = 0; a < ilosc_blok; a++)
			pB << blokady[a].zwrocPoz().x << " " << blokady[a].zwrocPoz().y << " " << blokady[a].zwrocBlokade() << '\n';
		pB.close();
	}
}

int Fportal::operator() (Tile* blokady)
{
	std::ifstream pB;
	int ilosc_blok{};
	pB.open("specBlok.txt");
	if (pB.good())
	{
		pB >> ilosc_blok;
		blokady = new Tile[ilosc_blok];
		for (int a = 0; a < ilosc_blok; a++)
		{
			sf::Vector2f pozB;
			bool z;
			pB >> pozB.x >> pozB.y >> z;
			blokady[a].init(pozB);
			blokady[a].zmienBlok(z);
			blokady[a].zmienTeksture(mag.zwroc_t(z));
		}
		pB.close();
	}
	return ilosc_blok;
}
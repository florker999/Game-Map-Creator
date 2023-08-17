#include "Tokno_skrzyni.h"
#include "SFML/Graphics.hpp"

sf::Sprite Tokno_skrzyni::okienko = sf::Sprite(mag.zwroc_t(typ_dod::wSkrz));

Tokno_skrzyni::Tokno_skrzyni(Item* nZaw, int ilosc)
{
	if (ilosc == 0)
	{
		ilosc_rzeczy = 0;
		zawartosc = nullptr;
	}
	else
	{
		ilosc_rzeczy = ilosc;

		zawartosc = new Item * [9]{};
		for (int a = 0; a < 9; a++, nZaw++)
			zawartosc[a] = nZaw;
	}
}

Tokno_skrzyni::~Tokno_skrzyni()
{
	if (zawartosc)
		delete[] zawartosc;
}

void Tokno_skrzyni::dodajRzecz(const Item& nowa)
{
	if (zawartosc == nullptr)
		zawartosc = new Item * [9]{};

	sf::Vector2f mscRz = okienko.getPosition();
	mscRz.y += 39;		

	int ktr;
	for (ktr = 0; ktr < 9; ktr++)
	{
		if (zawartosc[ktr] && zawartosc[ktr]->zwrocPoz() == nowa.zwrocPoz())
			break;
		else if (zawartosc[ktr] == nullptr && mscRz == nowa.zwrocPoz())
			break;

		mscRz.x += 39;
		if ((ktr % 3) == 2)
		{
			mscRz.x -= 117;
			mscRz.y += 39;
		}
	}
		
	if (zawartosc[ktr])
	{
		delete zawartosc[ktr];
		ilosc_rzeczy--;
	}

	zawartosc[ktr] = nowa.stworzWg();
	ilosc_rzeczy++;

}

void Tokno_skrzyni::otwarcie(sf::Vector2f start)
{
	okienko.setPosition(start);
	if (ilosc_rzeczy)
	{
		start.y += 39;
		for (int a = 0; a < 9; a++)
		{
			if (zawartosc[a])
				zawartosc[a]->zmienPolozenie(start);
			start.x += 39;
			
			if ((a % 3) == 2)
			{
				start.x -= 117;
				start.y += 39;
			}
		}
	}
}

void Tokno_skrzyni::pokazWnetrze(sf::RenderWindow& okno)
{
	okno.draw(okienko);

	if (zawartosc)
	{
		for (int a = 0; a < 9; a++)
		{
			if (zawartosc[a])
				okno.draw(zawartosc[a]->zwrocSpr());
		}
	}
}

bool Tokno_skrzyni::czyMysz(sf::Vector2f pM)
{
	if (okienko.getGlobalBounds().contains(pM))
		 return true;
	else return false;
}

Item* Tokno_skrzyni::wyjmijRzecz(sf::Vector2f pM)
{
	if (ilosc_rzeczy == 0)
		return nullptr;

	Item* wyjeta = nullptr;
	for (int a = 0; a < 9; a++)
	{
		if (zawartosc[a] && zawartosc[a]->czyMysz(pM))
		{
			wyjeta = zawartosc[a];
			zawartosc[a] = nullptr;
			ilosc_rzeczy--;
			break;
		}
	}

	return wyjeta;
}

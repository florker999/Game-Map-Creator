#ifndef TYPY_H
#define TYPY_H

enum class typ_pod	{ pusty, trawa, woda };
enum class typ_ob	{ pusty, skrzynia, dSkrzynia, cobel, drzwi_drew };
enum class typ_pos	{ maciek_n, maciek_p, maciek_l, wera };
enum class typ_dod	{ wSkrz, dostep, blokada };
enum class typ_mat	{ drewno, szklo, kamien };
enum class typ_rz	{ pusty, trawa, woda, skrzynia, duza_skrzynia, cobel, drzwi_drew,
					  wn_skrz, dostep, blokada, mikstura_zycia, mikstura_trucizna,
					  podloze_drewniane, witraz, beczka, miecz_treningowy, pochodnia };
enum class typ_akc	{ nic, otw_skrz, zamk_skrz };

#endif
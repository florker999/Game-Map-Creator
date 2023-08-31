#ifndef VARIANTS_H
#define VARIANTS_H

enum class floor_v	{ empty, grass, water };
enum class wall_v   { empty, wood, cobelstone };
enum class door_v   { wooden };
enum class chest_v  { wooden };
enum class mixture_v { health, poison };
enum class character_v	{ maciek_n, maciek_p, maciek_l, wera };
enum class add_v	{ chest_wdw, access, blockade };
enum class mat_v	{ wood, glass, stone };
enum class item_v	{ stained_glass, barrel, training_sword, torch };
enum class action_v	{ nothing, open_ch, close_ch };

#endif

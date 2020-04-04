// Reveni (c) 2020 Baltasar MIT License <baltasarq@gmail.com>

/* Rooms */

#include "locs.h"

#include <string.h>


Loc locs[NumLocs];

void init_locs()
{
	int i = 0;

	// Init exits for all locs
    memset( locs, NumLocs, sizeof( Loc ) * NumLocs );

    // Alunizaje
    locs[ 0 ].desc = "El lugar del alunizaje. La vaina abierta y sin "
    				 "contenido parece una triste parodia de ella misma. "
    				 "Un valle natural conduce al sur.";
    locs[ 0 ].exits[ ExitSouth ] = 1;

	// Valle de agujas
    locs[ 1 ].desc = "Un valle se extiende de norte a sur. Dos llamativas "
    				 "agujas son visibles a ambos lados.";
	locs[ 1 ].exits[ ExitNorth ] = 0;
	locs[ 1 ].exits[ ExitSouth ] = 4;

	// Lado oeste del lago de amoniaco
    locs[ 2 ].desc = "El extremo de un reducido pero impacticable lago de "
    			   "amoniaco se extiende hacia el este. Se puede ir "
    			   "hacia el sur.";
	locs[ 2 ].exits[ ExitSouth ] = 8;

	// Lado este del lago de amoniaco
	locs[ 3 ].desc = "Un lago de amoníaco se extiende hacia el oeste. "
				     "Es posible volver al oeste por encima de la aguja.";
	locs[ 3 ].exits[ ExitWest ] = 2;
}

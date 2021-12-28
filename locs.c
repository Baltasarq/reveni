// Reveni (c) 2020 Baltasar MIT License <baltasarq@gmail.com>

/* Rooms */

#include "locs.h"
#include "ctrl.h"

#include <string.h>
#include <stdlib.h>

// Loc descs array
Loc locs[NumLocs];


// Pic's data
// Alunizaje
static unsigned char pic_data0[] = {
    DCMD_Circle, 50, 10, 10,
    DCMD_Fill, 50, 10,
    DCMD_Circle, 100, 15, 25,
    DCMD_Line, 0, 56, 255, 50,
    DCMD_EOD
};


void init_locs()
{
	byte i = 0;

	// Init exits for all locs
    memset( locs, NumLocs, sizeof( Loc ) * NumLocs );

    locs[ 0 ].desc = "El lugar del alunizaje. La vaina abierta y sin "
    				 "contenido parece una triste parodia de ella misma. "
    				 "Un valle natural conduce al sur.";
    locs[ 0 ].exits[ ExitSouth ] = 1;
    locs[ 0 ].pic_data = pic_data0;

	// Valle de agujas
    locs[ 1 ].desc = "Un estrecho valle se extiende de norte a sur, "
                     "aunque dos llamativas agujas impiden el paso "
                     "hacia el sur.";
	locs[ 1 ].exits[ ExitNorth ] = 0;

	// Lado oeste del lago de amoniaco
    locs[ 2 ].desc = "El extremo de un reducido pero impacticable lago de "
    			   "amoniaco se extiende hacia el este. Se puede ir "
    			   "hacia el sur.";
	locs[ 2 ].exits[ ExitSouth ] = 8;

	// Lado este del lago de amoniaco
	locs[ 3 ].desc = "Un lago de amoníaco se extiende hacia el oeste. "
				     "Es posible volver al oeste por encima "
                     "de la aguja.";
	locs[ 3 ].exits[ ExitWest ] = 2;
    
    // Valle norte-este: primer cryo-geiser
	locs[ 4 ].desc = "Un valle sigue de norte a este. "
				     "Ves un raro agujero en el suelo hacia el sur, "
                     "notando un gran aumento de temperatura "
                     "a medida que te acercas.";
	locs[ 4 ].exits[ ExitNorth ] = 1;
    locs[ 4 ].exits[ ExitEast ] = 5;
    
    // Valle oeste-sur (colina al este)
	locs[ 5 ].desc = "Un llano permite avanzar de oeste a sur. Hacia "
                     "el este puedes ver una colina.";
	locs[ 5 ].exits[ ExitWest ] = 4;
    locs[ 5 ].exits[ ExitSouth ] = 11;
    
    // Desfiladero hacia el norte
	locs[ 6 ].desc = "Un desfiladero se extiende hacia el norte. La "
                     "pared oeste es una colina practicable, "
                     "mientras que al este ves una pared rocosa. La "
                     "luz se reduce mucho por zonas en este lugar "
                     "casi cavernoso.";
	locs[ 6 ].exits[ ExitWest ] = 5;
    locs[ 6 ].exits[ ExitNorth ] = 7;
    
    // Entrada a la gruta
	locs[ 7 ].desc = "El desfiladero termina en una pared al norte, "
                     "en la que se abre la entrada de una gruta. Es "
                     "posible volver al sur.";
	locs[ 7 ].exits[ ExitNorth ] = 14;
    locs[ 7 ].exits[ ExitSouth ] = 6;
    
    // Llano norte-este
	locs[ 8 ].desc = "Una zona llana entre grandes rocas permite "
                     "moverse de norte a este.";
	locs[ 8 ].exits[ ExitNorth ] = 2;
    locs[ 8 ].exits[ ExitEast ] = 9;
    
    // Llano norte-este
	locs[ 9 ].desc = "Una llanura se extiende de este a oeste, "
                     "con elevaciones al norte y sur.";
	locs[ 9 ].exits[ ExitWest ] = 8;
    locs[ 9 ].exits[ ExitEast ] = 10;
    
    // Cryo-geiser, lado sur
	locs[ 10 ].desc = "Un zona baja alberga un agujero al norte y "
                      "sendas colinas pedregosas al este y al oeste. "
                      "Te das cuenta de que el agujero no es sino "
                      "el geiser que encontraste antes: te has "
                      "desplazado hacia el sur del mismo dando un "
                      "amplio rodeo.";
	locs[ 10 ].exits[ ExitWest ] = 9;
    locs[ 10 ].exits[ ExitEast ] = 14;
    
    // Bajo el arco
	locs[ 11 ].desc = "Esta zona es realmente extraordinaria; un "
                      "arco por encima de tu cabeza, inalcanzable, "
                      "une dos paredes al este y oeste, mientras "
                      "solo puedes moverte de norte a sur por un "
                      "paso abovedado.";
	locs[ 11 ].exits[ ExitNorth ] = 5;
    locs[ 11 ].exits[ ExitSouth ] = 13;
    
    // Valle norte a oeste
	locs[ 12 ].desc = "Un suave valle con dos salidas, al norte y "
                      "al oeste, se extiende por delante. El suelo "
                      "pedregoso da paso en este punto a suave "
                      "tierra arenosa.";
	locs[ 12 ].exits[ ExitNorth ] = 6;
    locs[ 12 ].exits[ ExitWest ] = 14;
    
    // Cresta sobre grieta
	locs[ 13 ].desc = "El paisaje se vuelve pedregoso en derredor de "
                      "forma que solo se puede ir al norte. "
                      "Una cresta se asoma sobre una grieta que se "
                      "se extiende de este a oeste hasta donde "
                      "alcanza la vista.";
	locs[ 13 ].exits[ ExitNorth ] = 6;
    
    // Sobre el arco
	locs[ 14 ].desc = "Un arco a tu altura se extiende de este a "
                      "oeste, mientras puedes ver un pasaje "
                      "norte a sur por debajo.";
	locs[ 14 ].exits[ ExitEast ] = 12;
    locs[ 14 ].exits[ ExitWest ] = 10;
}


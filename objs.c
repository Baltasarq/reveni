// Reveni (c) 2020 Baltasar MIT License <baltasarq@gmail.com>

/* objs */

#include "objs.h"
#include "ctrl.h"

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>


const int PLAYER_NUM_LOC = -128;
const int LIMBO = -129;

Obj objs[NumObjs];
static Obj * objs_found[NumObjs + 1];

void init_objs()
{
    // Initialize objects' status
    memset( &objs, 0, sizeof( Obj ) * NumObjs );

	// Sitio del accidente
	objs[ 0 ].id = "traje";
	objs[ 0 ].num_loc = PLAYER_NUM_LOC;
	objs[ 0 ].atr = Clothing;
	objs[ 0 ].words = " traje espac ";
	objs[ 0 ].desc = "Fino pero resistente y protector.";

	objs[ 1 ].id = "vaina";
	objs[ 1 ].num_loc = 0;
	objs[ 1 ].atr = Static;
	objs[ 1 ].words = " vaina capsu nave ";
	objs[ 1 ].desc = "Yace destrozada contra el suelo de Ceres.";

	// Valle norte-sur con agujas
	objs[ 2 ].id = "agujas";
	objs[ 2 ].num_loc = 1;
	objs[ 2 ].atr = Static;
	objs[ 2 ].words = " aguja ";
	objs[ 2 ].worn = true;
	objs[ 2 ].desc = "Se levantan imponentes desde el suelo.";
    
	// Borde oeste del lago de amoniaco
	objs[ 3 ].id = "aguja";
	objs[ 3 ].num_loc = 2;
	objs[ 3 ].atr = Static;
	objs[ 3 ].words = " aguja obeli ";
	objs[ 3 ].desc = "Cual obelisco, situada justo al borde del lago.";
    
    // Primer cryo-geiser
	objs[ 4 ].id = "agujero";
	objs[ 4 ].num_loc = 4;
	objs[ 4 ].atr = Static;
	objs[ 4 ].words = " geise cryo- cryog aguje chime ";
	objs[ 4 ].desc = "Ves un fondo licuoso.";
    
    // Colina
	objs[ 5 ].id = "colina";
	objs[ 5 ].num_loc = 5;
	objs[ 5 ].atr = Static;
	objs[ 5 ].words = " colin eleva ";
	objs[ 5 ].desc = "Se eleva hacia el este. Te das cuenta de "
                     "que es superable.";
    
    // Pared
	objs[ 6 ].id = "pared";
	objs[ 6 ].num_loc = 6;
	objs[ 6 ].atr = Static;
	objs[ 6 ].words = " pared ";
	objs[ 6 ].desc = "Aunque es una pared casi vertical, puedes ver "
                     "que es aterrazada, de manera que entre "
                     "las rocas se puede avanzar hacia el este.";
                     
    // Pared
	objs[ 7 ].id = "entrada de la gruta";
	objs[ 7 ].num_loc = 7;
	objs[ 7 ].atr = Static;
	objs[ 7 ].words = " gruta entra ";
	objs[ 7 ].desc = "Apenas se aprecia nada desde fuera.";
    
    // Suelo - casi todas las locs
	objs[ 8 ].id = "suelo";
	objs[ 8 ].num_loc = 0;
	objs[ 8 ].atr = Static;
	objs[ 8 ].words = " suelo ";
	objs[ 8 ].desc = "El suelo es pedregoso y arenoso. Grandes rocas "
                     "se esparcen en derredor.";
    
    // Rocas - casi todas las locs
	objs[ 9 ].id = "rocas";
	objs[ 9 ].num_loc = 0;
	objs[ 9 ].atr = Static;
	objs[ 9 ].words = " rocas ";
	objs[ 9 ].desc = "Grandes rocas se elevan en ciertos lugares.";
    
    // Rocas
	objs[ 10 ].id = "suelo";
	objs[ 10 ].num_loc = 12;
	objs[ 10 ].atr = Static;
	objs[ 10 ].words = " suelo ";
	objs[ 10 ].desc = "El suelo es de fina arena gris.";
    
    // Grieta
	objs[ 11 ].id = "grieta";
	objs[ 11 ].num_loc = 13;
	objs[ 11 ].atr = Static;
	objs[ 11 ].words = " griet ";
	objs[ 11 ].desc = "Descarnadamente profunda, aunque "
                      "relativamente estrecha.";
    
    // Arco
	objs[ 12 ].id = "arco";
	objs[ 12 ].num_loc = 14;
	objs[ 12 ].atr = Static;
	objs[ 12 ].words = " arco ";
	objs[ 12 ].desc = "Irregular, se asienta sobre dos pilares, "
                      "uno estrecho y otro grueso.";
    
    // Pasaje
	objs[ 13 ].id = "pasaje";
	objs[ 13 ].num_loc = 14;
	objs[ 13 ].atr = Static;
	objs[ 13 ].words = " pasaj ";
	objs[ 13 ].desc = "Atraviesa el arco por su parte inferior, "
                      "de manera que este es su techo abovedado.";
    
    // Caucho
	objs[ 14 ].id = "caucho";
	objs[ 14 ].num_loc = 1;
	objs[ 14 ].atr = Portable;
	objs[ 14 ].words = " cauch ";
	objs[ 14 ].desc = "Restos de caucho del exterior de la vaina.";
}

int how_many_objs_in(int num_loc)
{
	int toret = 0;
	int i = 0;

	for(; i < NumObjs; ++i) {
		Obj * obj = &objs[ i ];

		if ( obj->atr != Static
		  && obj->num_loc == num_loc )
		{
			++toret;
		}
	}

	return toret;
}

int list_objs_in(int num_loc)
{
	int toret = 0;
	int i = 0;

	for(; i < NumObjs; ++i) {
		Obj * obj = &objs[ i ];

		if ( obj->atr != Static
		  && obj->num_loc == num_loc )
		{
            lf();
            print( obj->id );
            
            if ( num_loc == PLAYER_NUM_LOC
              && obj->worn == true )
            {
                print( " (puesto)" );
            }

			++toret;
		}
	}

	return toret;
}

const Obj ** get_objs_in(int num_loc)
{
	int pos = 0;

	for(int i = 0; i < NumObjs; ++i) {
		Obj * obj = &objs[ i ];

		if ( obj->num_loc == num_loc ) {
			objs_found[ pos ] = obj;
			++pos;
		}
	}

	objs_found[ pos ] = NULL;
	return objs_found;
}

const Obj ** get_objs_in_player_and(int num_loc)
{
	int pos = 0;

	for(int i = 0; i < NumObjs; ++i) {
		Obj * obj = &objs[ i ];

		if ( obj->num_loc == num_loc
		  || obj->num_loc == PLAYER_NUM_LOC )
		{
			objs_found[ pos ] = obj;
			++pos;
		}
	}

	objs_found[ pos ] = NULL;
	return objs_found;
}

Obj * locate_obj_by_id(const char * id)
{
    Obj * toret = NULL;
    int i = 0;

	for(; i < NumObjs; ++i) {
        if ( !strcmp( objs[ i ].id, id ) ) {
            toret = &objs[ i ];
            break;
        }
    }

    if ( toret == NULL ) {
        print( "*** ERROR: Unable to find: '" );
        print( id );
        fputc_cons( '\'' );
        lf();
        exit( EXIT_FAILURE );
    }

    return toret;
}

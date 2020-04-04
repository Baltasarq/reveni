// Reveni (c) 2020 Baltasar MIT License <baltasarq@gmail.com>

/* objs */

#include "objs.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


const int PLAYER_NUM_LOC = -128;
const int LIMBO = -129;

Obj objs[NumObjs];
static Obj * objs_found[NumObjs + 1];

void init_objs()
{
    int i = 0;

    for(; i < NumObjs; ++i) {
        objs[ i ].id = NULL;
        objs[ i ].num_loc = 0;
        objs[ i ].atr = Static;
        objs[ i ].words = NULL;
        objs[ i ].desc = NULL;
        objs[ i ].worn = false;
    }

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
            if ( num_loc == PLAYER_NUM_LOC
              && obj->worn == true )
            {
			    printf( "\n- %s (puesto)", obj->id );
            } else {
			    printf( "\n- %s", obj->id );
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
        fprintf( stderr, "*** ERROR: Unable to find: '%s'\n", id );
        exit( EXIT_FAILURE );
    }

    return toret;
}

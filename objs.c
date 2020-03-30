// Reveni (c) 2020 Baltasar MIT License <baltasarq@gmail.com>

/* objs */

#include "objs.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


const int PLAYER_NUM_LOC = -128;
const int LIMBO = -129;

Obj objs[NumObjs];

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

	// Loc 0, inicio
	objs[ 0 ].id = "mar";
	objs[ 0 ].num_loc = 0;
	objs[ 0 ].atr = Static;
	objs[ 0 ].words = " mar agua oceano ";
	objs[ 0 ].desc = "Agua fresca y cristalina.";

	objs[ 1 ].id = "coral";
	objs[ 1 ].num_loc = 0;
	objs[ 1 ].atr = Static;
	objs[ 1 ].words = " coral arrec rocas roca fondo pared fauna pez peces ";
	objs[ 1 ].desc = "El coral se distribuye por el fondo y las paredes de roca, "
				 "de forma caprichosa y salvaje. Los peces y otra fauna orbitan "
				 "a tu alrededor, ajenos a tu presencia.";

	objs[ 2 ].id = "traje";
	objs[ 2 ].num_loc = PLAYER_NUM_LOC;
	objs[ 2 ].atr = Clothing;
	objs[ 2 ].words = " traje neopr ";
	objs[ 2 ].worn = true;
	objs[ 2 ].desc = "Pedazo de negro y grueso caucho.";

	objs[ 3 ].id = "escalerilla";
	objs[ 3 ].num_loc = 2;
	objs[ 3 ].atr = Static;
	objs[ 3 ].words = " escal ";
	objs[ 3 ].desc = "Incrustada en el cemento.";

	objs[ 4 ].id = "aletas";
	objs[ 4 ].num_loc = PLAYER_NUM_LOC;
	objs[ 4 ].atr = Clothing;
    objs[ 4 ].worn = true;
	objs[ 4 ].words = " aleta ";
	objs[ 4 ].desc = "Para el buceo.";

	// Loc 3, amarre D1
	objs[ 5 ].id = "submarino";
	objs[ 5 ].num_loc = 3;
	objs[ 5 ].atr = Static;
	objs[ 5 ].words = " subma sumer buque navio barco torre escal pasar ";
	objs[ 5 ].desc = "Por una escalerilla al este, es perfectamente posible "
						"subir a la torre del sumergible.";

    // Loc 5, ascendiendo a la planta superior
    objs[ 6 ].id = "cristales";
	objs[ 6 ].num_loc = 5;
	objs[ 6 ].atr = Static;
	objs[ 6 ].words = " crist luz luces panta techo suelo ";
	objs[ 6 ].desc = "De las luces del techo solo quedan cristales rotos, "
                     "esparcidos por el suelo.";

    // La lancha del submarino
    objs[ 7 ].id = "lancha";
	objs[ 7 ].num_loc = LIMBO;
	objs[ 7 ].atr = Portable;
	objs[ 7 ].words = " lanch bote esqui barca ";
	objs[ 7 ].desc = "Una barca de salvamento.";

    // La escotilla del submarino
    objs[ 8 ].id = "escotilla";
	objs[ 8 ].num_loc = 7;
	objs[ 8 ].atr = Static;
	objs[ 8 ].words = " escot porti pane subma torre barco navio ";
	objs[ 8 ].desc = "Una escotilla de la torre del submarino.";

    // Documentos en la mesa del comandante
    objs[ 9 ].id = "documentos";
	objs[ 9 ].num_loc = 16;
	objs[ 9 ].atr = Static;
	objs[ 9 ].words = " docum comun ";
	objs[ 9 ].desc = "Parece un comunicado oficial. Se trata de un tipo de "
                        "trabajo... fechado para hoy mismo. No puede ser. "
                        "Es... imposible.\n"
                        "\"Operation Phoenix\n"
                        " -----------------\n"
                        "In april 2016 the U-530 submarine will arrive to the base "
                        "with the most important guest on board. "
                        "LORAM base will support the startings of the WCM mission, "
                        "and provide assistance when needed.\"\n\n"
                        "Un submarino... va a llegar... este mes.\n"
                        "Interesante, cuando menos...";

    // La mesa
    objs[ 10 ].id = "mesa";
	objs[ 10 ].num_loc = 16;
	objs[ 10 ].atr = Static;
	objs[ 10 ].words = " mesa escri ";
	objs[ 10 ].desc = "Una mesa de madera funcional. Polvorienta, como todo alrededor.";

    // Instrumentos de la sala de control
    objs[ 11 ].id = "instrumentos";
	objs[ 11 ].num_loc = 15;
	objs[ 11 ].atr = Static;
	objs[ 11 ].words = " instr contr ";
	objs[ 11 ].desc = "Desconoces su uso.";

    // Ventanal en la sala de control
    objs[ 12 ].id = "ventanal";
	objs[ 12 ].num_loc = 15;
	objs[ 12 ].atr = Static;
	objs[ 12 ].words = " venta ";
	objs[ 12 ].desc = "Puedes ver la parte delantera de los muelles, por donde entraste.";

    // Bandera
    objs[ 13 ].id = "bandera";
	objs[ 13 ].num_loc = 16;
	objs[ 13 ].atr = Static;
	objs[ 13 ].words = " bande ";
	objs[ 13 ].desc = "Un tanto descolorida, la verdad.";

    // Bandera
    objs[ 14 ].id = "silla";
	objs[ 14 ].num_loc = 16;
	objs[ 14 ].atr = Static;
	objs[ 14 ].words = " silla sillo ";
	objs[ 14 ].desc = "Polvorienta y combada por el paso del tiempo.";

    // Archivador
    objs[ 15 ].id = "archivador";
	objs[ 15 ].num_loc = 16;
	objs[ 15 ].atr = Static;
	objs[ 15 ].words = " archi perch colga ";
	objs[ 15 ].desc = "Polvoriento y sin nada llamativo.";

    // Polvo
    objs[ 16 ].id = "polvo";
	objs[ 16 ].num_loc = 16;
	objs[ 16 ].atr = Static;
	objs[ 16 ].words = " polvo sucie ";
	objs[ 16 ].desc = "Polvoriento.";

    // Polvo
    objs[ 17 ].id = "llave";
	objs[ 17 ].num_loc = LIMBO;
	objs[ 17 ].atr = Portable;
	objs[ 17 ].words = " llave ";
	objs[ 17 ].desc = "Reducida.";

    // Martillo
    objs[ 18 ].id = "martillo";
	objs[ 18 ].num_loc = LIMBO;
	objs[ 18 ].atr = Portable;
	objs[ 18 ].words = " marti ";
	objs[ 18 ].desc = "Recio y fuerte.";

    // Baldas, legajos
    objs[ 19 ].id = "baldas";
	objs[ 19 ].num_loc = 19;
	objs[ 19 ].atr = Static;
	objs[ 19 ].words = " balda estan legaj papel archi ";
	objs[ 19 ].desc = "Todo polvoriento.";

    // Caja de madera
    objs[ 20 ].id = "caja";
	objs[ 20 ].num_loc = 18;
	objs[ 20 ].atr = Static;
	objs[ 20 ].words = " caja mader conte ";
	objs[ 20 ].desc = "Una caja de madera. "
                      "Hay una etiqueta de destino, fechada, ha llegado... hoy.";

    // Tarjeta
    objs[ 21 ].id = "tarjeta";
	objs[ 21 ].num_loc = LIMBO;
	objs[ 21 ].atr = Portable;
	objs[ 21 ].words = " tarje ";
	objs[ 21 ].desc = "Una especie de tarjeta de acero.";

     // Botonera
    objs[ 22 ].id = "botonera";
	objs[ 22 ].num_loc = 10;
	objs[ 22 ].atr = Static;
	objs[ 22 ].words = " boton pulsa ranur ";
	objs[ 22 ].desc = "El pulsador tiene una fina ranura debajo.";

     // Maquinaria
    objs[ 23 ].id = "maquinaria";
	objs[ 23 ].num_loc = 9;
	objs[ 23 ].atr = Static;
	objs[ 23 ].words = " maqui motor palan engra ";
	objs[ 23 ].desc = "Maquinaria oxidada y polvorienta.";

     // Vista de los muelles
    objs[ 24 ].id = "muelles";
	objs[ 24 ].num_loc = 15;
	objs[ 24 ].atr = Static;
	objs[ 24 ].words = " muell subma navio barco vista ";
	objs[ 24 ].desc = "Se aprecia muy bien el submarino desde este punto.";

     // Suelo, techos y paredes de cemento
    // (debe estar al final, para tener menos prioridad)
    objs[ 25 ].id = "muros";
	objs[ 25 ].num_loc = 2;
	objs[ 25 ].atr = Static;
	objs[ 25 ].words = " muell cemen suelo techo pared muro muros ";
	objs[ 25 ].desc = "Todo ha sido fabricado en gris cemento.";

    objs[ 26 ].id = "puertas";
	objs[ 26 ].num_loc = 8;
	objs[ 26 ].atr = Static;
	objs[ 26 ].words = " puert ";
	objs[ 26 ].desc = "Funcionales puertas de acero.";
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

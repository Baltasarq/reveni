// Reveni (c) 2020 Baltasar MIT License <baltasarq@gmail.com>

/* player.c */

#include "player.h"
#include "objs.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


const int MAX_INV_OBJS = 4;

/** Inits the game
  * @param player The player structure
  */
void init_game(Player * player)
{
	init_cmds();
	init_locs();
	init_objs();

	player->num_loc = 0;
	player->num_turns = 0;
}

/** Ends the game */
void end_game(Player * player)
{
    print( "Introduces la tarjeta en su ranura, y el ascensor se pone en "
           "marcha con un gran estruendo. Es asombroso que la maquinaria siga "
           "funcionando.\n" );
    print( "Tras unos instantes, que se han hecho eternos, llegas arriba." );
    print( "Caminas por entre las ruinas de la base, con innumerables preguntas "
           "sobre lo que has descubierto en sus muelles secretos.\n" );
    input( PROMPT_WAIT );
    print( "\nA punto de salir de las ruinas del edificio principal, descubres que se "
           "acercan varias furgonetas negras.\n" );
    input( PROMPT_WAIT );
    print( "\nDecides tomar un rodeo. No sabes lo que ha pasado, pero desde luego no te "
           "vas a quedar a hacer preguntas.\n" );
    print( "Fin.\n" );

    if ( !ask_yes_no( "Volver a jugar (s/n): " ) ) {
        cls();
        exit( 0 );
    } else {
        restart( player );
    }
}

/** Asks yes o no to the user, given a message
    @param msg The message to show to the user.
    @return true if the first letter of the user's reply is 's' or 'y'
*/
bool ask_yes_no(const char * msg)
{
    char answer = 'n';
    static char buffer[3];

    printf( msg );
    fgets( buffer, 2, stdin );
    answer = tolower( buffer[ 0 ] );

    return ( answer == 's' || answer == 'y' );
}

/** Executed just after describing the current loc
  * @param player The player structure
  */
void proc1(Player * player)
{
    const Obj * ObjMar = locate_obj_by_id( "mar" );
    const Obj * ObjWalls = locate_obj_by_id( "muros" );
    const Obj * ObjAletas = locate_obj_by_id( "aletas" );
    const Obj * ObjTarjeta = locate_obj_by_id( "tarjeta" );
    const Obj * ObjEscalerilla = locate_obj_by_id( "escalerilla" );
    const Obj * ObjSilla = locate_obj_by_id( "silla" );
    const Obj * ObjMesa = locate_obj_by_id( "mesa" );
    const Obj * ObjArchivador = locate_obj_by_id( "archivador" );
    const Obj * ObjPolvo = locate_obj_by_id( "polvo" );
    const Obj * ObjBaldas = locate_obj_by_id( "baldas" );
    const Obj * ObjPuertas = locate_obj_by_id( "puertas" );

    static bool isSubDesc = false;

    // You take the concrete walls, ceiling and floor wherever you go.
    ObjWalls->num_loc = LIMBO;
    if ( player->num_loc > 0 ) {
        ObjWalls->num_loc = player->num_loc;
    }

	// Take the sea with you (yeah, baby!), while in the sea & docks
	if ( player->num_loc <= 7 ) {
		ObjMar->num_loc = player->num_loc;
	}

	// The stairs are found in loc #5 (dock D-3) and loc #2 (first dock)
	if ( player->num_loc == 2
      || player->num_loc == 5
      || player->num_loc == 14 )
    {
        ObjEscalerilla->num_loc = player->num_loc;
    }

	// Initial message about the submarine
	if ( !isSubDesc
	  && player->num_loc == 7 )
	{
		print( "Efectivamente, se trata de un submarino de mediados del "
					"siglo pasado.\n" );
		isSubDesc = true;
	}

	// You leave your equipment in the first loc of the base
	if ( player->num_loc == 2
	  && ObjAletas->num_loc == PLAYER_NUM_LOC )
	{
		print( "Incapaz de utilizarlas caminando, dejas las aletas en el suelo." );
		ObjAletas->num_loc = 2;
	}

    // Move office furniture when needed.
    if ( player->num_loc == 16
      || player->num_loc == 17 )
    {
        ObjSilla->num_loc = player->num_loc;
        ObjMesa->num_loc = player->num_loc;
        ObjArchivador->num_loc = player->num_loc;
    }

    // Move dust around
    if ( player->num_loc >= 9 ) {
        ObjPolvo->num_loc = player->num_loc;
    }

    // Move shelves
    if ( player->num_loc == 18
      || player->num_loc == 19 )
    {
        ObjBaldas->num_loc = player->num_loc;
    }

    // Move the doors with you
    if ( player->num_loc >= 8 ) {
        ObjPuertas->num_loc = player->num_loc;
    }

    // End of game?
    if ( player->num_loc == 10
      && ObjTarjeta->num_loc == PLAYER_NUM_LOC )
    {
        end_game( player );
    }
}

/** Executed after a successful command
  * @param player The player structure
  */
void proc2(Player * player)
{
	if ( player->num_turns == 3 ) {
		printf( "\n" );
		print(
			"Repentinamente, notas una irrefrenable fuerza que te succiona... "
			"El agua te arrastra hacia las rocas... pero en lugar de rocas, "
			"encuentras algo raro: una apertura, una compuerta que se ha "
			"abierto a un lugar escondido en las profundidades."
		);
		printf( "\n" );
		input( PROMPT_WAIT );
		cls();
		print(
			"Tras unos interminables minutos, has acabado dentro de una gigante "
			"estructura. Como si fuera un hangar para aviones, pero con agua. "
			"Algo parecido a un muelle se encuentra frente a ti, y "
			"decides abandonar el agua usando una escalerilla."
		);
		printf( "\n" );
		player->num_loc = 2;
	}

	return;
}

void resp(Player * player, Order * order)
{
    const Obj * ObjTraje = locate_obj_by_id( "traje" );
    const Obj * ObjLancha = locate_obj_by_id( "lancha" );
    const Obj * ObjAletas = locate_obj_by_id( "aletas" );
    const Obj * ObjEscotilla = locate_obj_by_id( "escotilla" );
    const Obj * ObjMesa = locate_obj_by_id( "mesa" );
    const Obj * ObjDocs = locate_obj_by_id( "documentos" );
    const Obj * ObjArchivador = locate_obj_by_id( "archivador" );
    const Obj * ObjLlave = locate_obj_by_id( "llave" );
    const Obj * ObjMartillo = locate_obj_by_id( "martillo" );
    const Obj * ObjBaldas = locate_obj_by_id( "baldas" );
    const Obj * ObjCaja = locate_obj_by_id( "caja" );
    const Obj * ObjBotonera = locate_obj_by_id( "botonera" );

    static bool caja_abierta = false;
    bool intercepted = false;

    // Quitate el traje
    if ( order->cmd->cmdId == CmdDisrobe
      && order->obj1 == ObjTraje )
    {
        intercepted = true;
        print( "No es buena idea, teniendo en cuenta las bajas temperaturas." );
        return;
    }


    // Deja o quitate las aletas
    if ( order->cmd->cmdId == CmdDisrobe
      && order->obj1 == ObjAletas
      && ObjAletas->num_loc == PLAYER_NUM_LOC )
    {
        intercepted = true;
        print( "No, las necesitas para nadar." );
        return;
    }

    // Coge las aletas
    if ( order->cmd->cmdId == CmdTake
      && order->obj1 == ObjAletas
      && order->obj1->num_loc == 2 )
    {
        intercepted = true;
        print( "Ahora ya son inservibles: no puedes usarlas caminando." );
        return;
    }

    // Intenta subir
    if ( order->cmd->cmdId == CmdUp
      && player->num_loc == 5 )
    {
        if ( ObjLancha->num_loc != 5 ) {
            intercepted = true;
            print( "No, no, te vas a cortar los pies." );
            return;
        } else {
            print( "Trepando por encima de la lancha, "
                   "consigues ascender por la escalerilla." );
        }
    }

    // Deja la lancha
    if ( order->cmd->cmdId == CmdDrop
      && player->num_loc == 5
      && order->obj1 == ObjLancha )
    {
        print( "Tratas de colocar la lancha tapando los cristales..." );
    }

    // Examinas la escotilla del submarino
    if ( order->cmd->cmdId == CmdExamine
      && player->num_loc == 7
      && order->obj1 == ObjEscotilla
      && ObjLancha->num_loc == LIMBO )
    {
        intercepted = true;
        print( "Repasas todas las escotillas de la torre, y abres la "
               "que es practicable. Resulta ser un panel, y de su "
               "interior extraes una reducida lancha de salvamento." );
        ObjLancha->num_loc = 7;
        return;
    }

    // Examinar la mesa del despacho del general
    if ( player->num_loc == 16
      && order->cmd->cmdId == CmdExamine
      && order->obj1 == ObjMesa )
    {
        print( "Sobre ella, hay unos documentos." );
        intercepted = true;
    }

    // Intentar coger los papeles
    if ( player->num_loc == 16
      && order->cmd->cmdId == CmdTake
      && order->obj1 == ObjDocs )
    {
        print( "Prefiero no cogerlos, parecen demasiado importantes." );
        intercepted = true;
    }

    // Hacer aparecer la llave en el despacho del secre
    if ( player->num_loc == 17
      && order->cmd->cmdId == CmdExamine
      && order->obj1 == ObjArchivador
      && ObjLlave->num_loc == LIMBO )
    {
        print( "Encima del archivador, encuentras una llave." );
        ObjLlave->num_loc = 17;
        intercepted = true;
    }

    if ( player->num_loc == 23
      && order->cmd->cmdId == CmdWest )
    {
        if ( ObjLlave->num_loc != PLAYER_NUM_LOC ) {
            print( "Cerrada. Necesitas una llave." );
            intercepted = true;
        } else {
            print( "Abres la puerta..." );
        }
    }

    // Hacer aparecer el martillo en el archivo
    if ( player->num_loc == 19
      && order->cmd->cmdId == CmdExamine
      && order->obj1 == ObjBaldas
      && ObjMartillo->num_loc == LIMBO )
    {
        intercepted = true;
        ObjMartillo->num_loc = 19;
        print( "Has encontrado un martillo encima de una balda." );
    }

    // Pulsa en el ascensor
    if ( player->num_loc == 10
      && order->cmd->cmdId == CmdPush
      && order->obj1 == ObjBotonera )
    {
        intercepted = true;
        print( "No sucede nada. Hay una ranura debajo... es necesario meter algo." );
    }

    // Rompe la caja
    if ( player->num_loc == 18
      && order->cmd->cmdId == CmdBreak
      && order->obj1 == ObjCaja )
    {
        intercepted = true;

        if ( !caja_abierta ) {
            if ( ObjMartillo->num_loc != PLAYER_NUM_LOC ) {
                print( "No puedes hacerlo con las manos desnudas." );
            } else {
                caja_abierta = true;
                print( "Rompes la caja a golpes, desparramando su contenido." );
            }
        } else {
            print( "Ya hay bastante estropicio..." );
        }
    }

    // Examina la caja
    if ( player->num_loc == 18
      && order->cmd->cmdId == CmdExamine
      && order->obj1 == ObjCaja )
    {
        Obj * ObjTarjeta = locate_obj_by_id( "tarjeta" );


        if ( caja_abierta ) {
            intercepted = true;
            print( ObjCaja->desc );
            print( "Su contenido se desparrama en derredor." );

            if ( ObjTarjeta->num_loc == LIMBO ) {
                print( "Hay muchos papeles, y piezas, pero no ves nada de "
                        "utilidad real... excepto una tarjeta." );
                ObjTarjeta->num_loc = 18;
            }
        }
    }


    if ( !intercepted ) {
        order->cmd->doIt( player, order );
    }
}


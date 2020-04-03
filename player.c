// Reveni (c) 2020 Baltasar MIT License <baltasarq@gmail.com>

/* player.c */

#include "player.h"
#include "objs.h"
#include "locs.h"
#include "ctrl.h"

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
    printf( PROMPT_WAIT );
    read_key();
    print( "\nA punto de salir de las ruinas del edificio principal, descubres que se "
           "acercan varias furgonetas negras.\n" );
    printf( PROMPT_WAIT );
    read_key();
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
	/*const Obj * ObjMar = locate_obj_by_id( "mar" );

	// Take the sea with you (yeah, baby!), while in the sea & docks
	if ( player->num_loc <= 7 ) {
		ObjMar->num_loc = player->num_loc;
	}
*/

    // End of game?
    if ( player->num_loc == 10 ) {
        end_game( player );
    }
}

/** Executed after a successful command
  * @param player The player structure
  */
void proc2(Player * player)
{

}

void resp(Player * player, Order * order)
{
	bool intercepted = false;

    //const Obj * ObjTraje = locate_obj_by_id( "traje" );

    if ( !intercepted ) {
        order->cmd->doIt( player, order );
    }
}


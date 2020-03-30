// Reveni (c) 2020 Baltasar MIT License <baltasarq@gmail.com>

/* cmds.c */
#include "player.h"
#include "cmds.h"
#include "locs.h"
#include "objs.h"

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define RELEASE 1


const char * MSG_DONE = "Hecho.";
const char * MSG_CANT_DO = "No puedes hacer eso.";
const char * MSG_CANT_SEE = "No ves eso en derredor.";
const char * MSG_ALREADY_DONE = "Eso ya lo has hecho antes.";
const char * MSG_IMPOSSIBLE = "Es imposible.";
const char * MSG_ALREADY_CARRIED = "Pero si ya lo tienes...";
const char * MSG_DONT_CARRIED = "No llevas eso contigo.";
const char * MSG_SPECIFY_CLOTHING = "Debes especificar una prenda.";
const char * MSG_HELP = "\"Bares\" es un juego basado en texto.\n"
            "Los comandos que se pueden utilizar son:\n"
            "\t\"fin\":            termina el juego.\n"
            "\t\"ayuda\":          muestra esta ayuda.\n"
            "\t\"nada\":           nada o bucea.\n"
            "\t\"n, norte\":       el jugador avanza al norte (adelante).\n"
            "\t\"s, sur\":         el jugador avanza al sur (retrocede).\n"
            "\t\"e, este\":        el jugador avanza al este (derecha).\n"
            "\t\"o, oeste\":       el jugador avanza al oeste (izquierda).\n"
            "\t\"x, salidas\":     muestra las salidas obvias visibles.\n"
            "\t\"z, espera\":      espera durante un turno.\n"
            "\t\"i, inventario\":  muestra los objetos llevados.\n"
            "\t\"ex, examina x\":  describe un objeto 'x' presente.\n"
            "\t\"coge x\":         coge un objeto 'x' de la localidad.\n"
            "\t\"ponte x\":        ponerse un objeto 'x' en el inventario.\n"
            "\t\"deja x\":         deja un objeto 'x' del inventario.\n"
            "\t\"quitate x\":      quitarse un objeto 'x' ya puesto.\n"
            "\t\"rompe x\":        rompe un objeto 'x'.\n"
            "\t\"empuja x\":       empuja un objeto 'x'.\n"
            "\t\"ataca x\":        ataca a 'x'.\n\n";

void cmdGo_doIt(Player * player, Order * order);
void cmdHelp_doIt(Player * player, Order * order);
void cmdEnd_doIt(Player * player, Order * order);
void cmdInv_doIt(Player * player, Order * order);
void cmdNop_doIt(Player * player, Order * order);
void cmdEx_doIt(Player * player, Order * order);
void cmdTake_doIt(Player * player, Order * order);
void cmdDrop_doIt(Player * player, Order * order);
void cmdSwim_doIt(Player * player, Order * order);
void cmdExits_doIt(Player * player, Order * order);
void cmdWear_doIt(Player * player, Order * order);
void cmdDisrobe_doIt(Player * player, Order * order);
void cmdWait_doIt(Player * player, Order * order);
void cmdBreak_doIt(Player * player, Order * order);
void cmdPush_doIt(Player * player, Order * order);
void cmdDbg_doIt(Player * player, Order * order);

Cmd cmds[NumCmds];
Cmd * cmdNop;

void init_cmds()
{
    // North
    cmds[0].cmdId = CmdNorth;
    cmds[0].doIt = cmdGo_doIt;
    cmds[0].words = " n norte ";

    // South
    cmds[1].cmdId = CmdSouth;
    cmds[1].doIt = cmdGo_doIt;
    cmds[1].words = " s sur ";

    // East
    cmds[2].cmdId = CmdEast;
    cmds[2].doIt = cmdGo_doIt;
    cmds[2].words = " e este ";

    // West
    cmds[3].cmdId = CmdWest;
    cmds[3].doIt = cmdGo_doIt;
    cmds[3].words = " o oeste ";

    // Up
    cmds[4].cmdId = CmdUp;
    cmds[4].doIt = cmdGo_doIt;
    cmds[4].words = " subir sube subo arrib ";

    // Down
    cmds[5].cmdId = CmdDown;
    cmds[5].doIt = cmdGo_doIt;
    cmds[5].words = " bajar baja bajo abajo ";


    // End
    cmds[6].cmdId = CmdEnd;
    cmds[6].doIt = cmdEnd_doIt;
    cmds[6].words = " fin termi end quit sal salir ";

    // Help
    cmds[7].cmdId = CmdHelp;
    cmds[7].doIt = cmdHelp_doIt;
    cmds[7].words = " ayuda help ";

    // Inventory
    cmds[8].cmdId = CmdInventory;
    cmds[8].doIt = cmdInv_doIt;
    cmds[8].words = " i inv inven ";

    // Examine
    cmds[9].cmdId = CmdExamine;
    cmds[9].doIt = cmdEx_doIt;
    cmds[9].words = " ex exami ";

    // Exits
    cmds[10].cmdId = CmdExits;
    cmds[10].doIt = cmdExits_doIt;
    cmds[10].words = " x salid ";

    // Take
    cmds[11].cmdId = CmdTake;
    cmds[11].doIt = cmdTake_doIt;
    cmds[11].words = " coger coge cojo ";

    // Drop
    cmds[12].cmdId = CmdDrop;
    cmds[12].doIt = cmdDrop_doIt;
    cmds[12].words = " dejar deja dejo tira tiro ";

    // Swim
    cmds[13].cmdId = CmdSwim;
    cmds[13].doIt = cmdSwim_doIt;
    cmds[13].words = " nadar nada nado bucear bucea buceo ";

    // Wear
    cmds[14].cmdId = CmdWear;
    cmds[14].doIt = cmdWear_doIt;
    cmds[14].words = " poner pon ponte pongo vesti visto ";

    // Disrobe
    cmds[15].cmdId = CmdDisrobe;
    cmds[15].doIt = cmdDisrobe_doIt;
    cmds[15].words = " quita quito desve desvi ";

    // Wait
    cmds[16].cmdId = CmdWait;
    cmds[16].doIt = cmdWait_doIt;
    cmds[16].words = " esper z ";

    // Break
    cmds[17].cmdId = CmdBreak;
    cmds[17].doIt = cmdBreak_doIt;
    cmds[17].words = " rompe rompo patea pateo golpe mata mato pega pego"
                     " ataca ataco ";

    // Push, move
    cmds[18].cmdId = CmdPush;
    cmds[18].doIt = cmdPush_doIt;
    cmds[18].words = " empuj pulsa pulso mueve muevo ";

    // Debug
    cmds[19].cmdId = CmdDbg;
    cmds[19].doIt = cmdDbg_doIt;
    cmds[19].words = " _dbg ";

    // Nop
    cmdNop = &cmds[NumCmds - 1];
    cmds[NumCmds - 1].cmdId = Cmd_Nop;
    cmds[NumCmds - 1].doIt = cmdNop_doIt;
    cmds[NumCmds - 1].words = "nop";
}

void cmdGo_doIt(Player * player, Order * order)
{
	int dest_loc = locs[ player->num_loc ].exits[ order->cmd->cmdId ];

	if ( dest_loc < NumLocs ) {
		player->num_loc = dest_loc;
	} else {
		printf( "No se puede tomar ese rumbo." );
	}

	return;
}

void cmdHelp_doIt(Player * player, Order * order)
{
    printf( MSG_HELP );
    input( PROMPT_WAIT );
}

void cmdEnd_doIt(Player * player, Order * order)
{
    if ( ask_yes_no( "Confirma que deseas terminar (s/n): " ) ) {
        cls();
        exit( 0 );
    } else {
        printf( "\n" );
    }
}

void cmdInv_doIt(Player * player, Order * order)
{
	int num = 0;
	int i = 0;

	printf( "Llevas contigo: " );

	num = list_objs_in( PLAYER_NUM_LOC );

	if ( num == 0 ) {
		printf( "Nada." );
	}

	printf( "\n" );
	return;
}

void cmdEx_doIt(Player * player, Order * order)
{
	char * msg = "No ves eso en derredor. O no te parece importante.";

//	printf("NumLoc: %d, Object: %d, Object's NumLoc: %d\n",
//				player->num_loc, order->obj1, order->obj1->num_loc );

	if ( order->obj1 != NULL
	  && ( order->obj1->num_loc == PLAYER_NUM_LOC
	    || player->num_loc == order->obj1->num_loc ) )
	{
		msg = order->obj1->desc;
	}

	print( msg );
	printf( "\n" );
}

void cmdExits_doIt(Player * player, Order * order)
{
    static const char * salidas[] = {
        "norte", "sur", "este", "oeste",
        "arriba", "abajo"
    };

    bool hay_salidas = false;
    int i = 0;
    Loc * loc = &locs[ player->num_loc ];

    printf( "Salidas visibles: " );
    for(; i < NumExits; ++i) {
        if ( loc->exits[ i ] < NumLocs ) {
          hay_salidas = true;
          printf( "%s ", salidas[ i ] );
        }
    }

    if ( !hay_salidas ) {
        printf( "ninguna." );
    }

    return;
}

void cmdTake_doIt(Player * player, Order * order)
{
	Obj * obj = order->obj1;
	const char * msg = MSG_CANT_SEE;

	if ( obj != NULL ) {
		if ( obj->num_loc == player->num_loc ) {
			if ( obj->atr != Static ) {
				msg = MSG_DONE;
				obj->num_loc = PLAYER_NUM_LOC;
			} else {
				msg = MSG_IMPOSSIBLE;
			}
		}
		else
		if ( obj->num_loc == PLAYER_NUM_LOC ) {
			msg = MSG_ALREADY_CARRIED;
		}
	}

	printf( "%s\n", msg );
}

void cmdDrop_doIt(Player * player, Order * order)
{
	char * msg = MSG_DONT_CARRIED;

	if ( order->obj1 != NULL ) {
		if ( order->obj1->num_loc == PLAYER_NUM_LOC ) {
            if ( !order->obj1->worn ) {
    			msg = MSG_DONE;
    			order->obj1->num_loc = player->num_loc;
            } else {
                msg = "No puedes, lo llevas puesto.";
            }
		}
	}

	printf( "%s\n", msg );
}

void cmdSwim_doIt(Player * player, Order * order)
{
	char * msg = "No tiene sentido nadar.";
	int num_loc = player->num_loc;

	if ( num_loc == 0 ) {
		msg = "Buceas y buceas, apreciando el coral.";
	}
	else
	if ( num_loc <= 7 ) {
		msg = "No quiero meterme en ese agua, a saber lo que oculta...";
	}

	printf( "%s\n", msg );
}

void cmdWear_doIt(Player * player, Order * order)
{
    char * msg;
    Obj * obj = order->obj1;

	if ( obj != NULL
	  && obj->atr == Clothing )
	{
		if ( obj->num_loc == PLAYER_NUM_LOC ) {
			if ( !obj->worn ) {
				msg = MSG_DONE;
				obj->worn = true;
			} else {
				msg = MSG_ALREADY_DONE;
			}
		} else {
			msg = MSG_DONT_CARRIED;
		}
	} else {
		msg = MSG_SPECIFY_CLOTHING;
	}

    printf( "%s\n", msg );
}

void cmdDisrobe_doIt(Player * player, Order * order)
{
    char * msg;
    Obj * obj = order->obj1;

	if ( obj != NULL ) {
		if ( obj->num_loc == PLAYER_NUM_LOC ) {
			if ( obj->worn ) {
				msg = MSG_DONE;
				obj->worn = false;
			} else {
				msg = MSG_ALREADY_DONE;
			}
		} else {
			msg = MSG_DONT_CARRIED;
		}
	} else {
		msg = MSG_SPECIFY_CLOTHING;
	}

    printf( "%s\n", msg );
}

void cmdWait_doIt(Player * player, Order * order)
{
    print( "Pasa el tiempo..." );
}

void cmdBreak_doIt(Player * player, Order * order)
{
    print( "La violencia no soluciona nada." );
}

void cmdPush_doIt(Player * player, Order * order)
{
    print( "No tiene sentido." );
}

void cmdDbg_doIt(Player * player, Order * order)
{
#ifndef RELEASE
    static char buffer[30];
    int i;

    printf( "Dbg Info\n" );

    // Num loc
    strcpy( buffer, "Player loc: " );
    itoa( player->num_loc, buffer + strlen( buffer ), 10 );
    printf( "%s\n", buffer );

    // Objects
    for(i = 0; i < NumObjs; ++i) {
        itoa( i, buffer, 10 );
        strcpy( buffer + strlen( buffer ), " " );
        strcpy( buffer + strlen( buffer ), objs[ i ].id );
        strcpy( buffer + strlen( buffer ), " @" );
        itoa( objs[ i ].num_loc, buffer + strlen( buffer ), 10 );

        if ( i % 5 == 0 ) {
            input( "ENTER..." );
        }

        printf( "%s\n", buffer );
    }
#else
    print( MSG_CANT_DO );
#endif

    return;
}

void cmdNop_doIt(Player * player, Order * order)
{
    printf( MSG_CANT_DO );
}


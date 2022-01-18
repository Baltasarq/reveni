// Reveni (c) 2020 Baltasar MIT License <baltasarq@gmail.com>

/* cmds.c */
#include "player.h"
#include "cmds.h"
#include "locs.h"
#include "objs.h"
#include "ctrl.h"

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>


extern byte read_key();


const char * MSG_DONE = "Hecho.";
const char * MSG_CANT_DO = "No puedes hacer eso.";
const char * MSG_CANT_SEE = "No ves eso en derredor.";
const char * MSG_ALREADY_DONE = "Eso ya lo has hecho antes.";
const char * MSG_IMPOSSIBLE = "Es imposible.";
const char * MSG_ALREADY_CARRIED = "Pero si ya lo tienes...";
const char * MSG_DONT_CARRIED = "No llevas eso contigo.";
const char * MSG_SPECIFY_CLOTHING = "Debes especificar una prenda.";


void cmdGo_doIt(const Player * player, const Order * order);
void cmdHelp_doIt(const Player * player, const Order * order);
void cmdEnd_doIt(const Player * player, const Order * order);
void cmdInv_doIt(const Player * player, const Order * order);
void cmdNop_doIt(const Player * player, const Order * order);
void cmdEx_doIt(const Player * player, const Order * order);
void cmdTake_doIt(const Player * player, const Order * order);
void cmdDrop_doIt(const Player * player, const Order * order);
void cmdSwim_doIt(const Player * player, const Order * order);
void cmdExits_doIt(const Player * player, const Order * order);
void cmdWear_doIt(const Player * player, const Order * order);
void cmdDisrobe_doIt(const Player * player, const Order * order);
void cmdWait_doIt(const Player * player, const Order * order);
void cmdBreak_doIt(const Player * player, const Order * order);
void cmdPush_doIt(const Player * player, const Order * order);
void cmdPull_doIt(const Player * player, const Order * order);
void cmdLookAround_doIt(const Player * player, const Order * order);

Cmd cmds[NumCmds];
const Cmd * cmdNop;

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

    // Pull
    cmds[19].cmdId = CmdPull;
    cmds[19].doIt = cmdPull_doIt;
    cmds[19].words = " tira tiro ";

    // Look around
    cmds[20].cmdId = CmdLookAround;
    cmds[20].doIt = cmdLookAround_doIt;
    cmds[20].words = " m mira mirar ";

    // Nop
    cmdNop = &cmds[NumCmds - 1];
    cmds[NumCmds - 1].cmdId = Cmd_Nop;
    cmds[NumCmds - 1].doIt = cmdNop_doIt;
    cmds[NumCmds - 1].words = "nop";
}

void cmdGo_doIt(const Player * player, const Order * order)
{
	int dest_loc = locs[ player->num_loc ].exits[ order->cmd->cmdId ];

	if ( dest_loc < NumLocs ) {
		player->num_loc = dest_loc;
		do_loc_desc( player );
	} else {
		println( "No se puede tomar ese rumbo." );
	}

	return;
}

void cmdHelp_doIt(const Player * player, const Order * order)
{
    // Not used with this game engine.
}

void cmdEnd_doIt(const Player * player, const Order * order)
{
    if ( ask_yes_no( "Confirma que deseas terminar (s/n): " ) ) {
        cls();
        exit( 0 );
    } else {
        lf();
    }
}

void cmdLookAround_doIt(const Player * player, const Order * order)
{
	do_loc_desc( player );
}

void cmdInv_doIt(const Player * player, const Order * order)
{
	int num = 0;
	int i = 0;

	println( "Llevas contigo: " );

	num = list_objs_in( PLAYER_NUM_LOC );

	if ( num == 0 ) {
		println( "Nada." );
	}

	lf();
	return;
}

void cmdEx_doIt(const Player * player, const Order * order)
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

	println( msg );
}

void cmdExits_doIt(const Player * player, const Order * order)
{
    static const char * salidas[] = {
        "norte", "sur", "este", "oeste",
        "arriba", "abajo"
    };

    bool hay_salidas = false;
    int i = 0;
    Loc * loc = &locs[ player->num_loc ];

    print( "Salidas visibles: " );
    for(; i < NumExits; ++i) {
        if ( loc->exits[ i ] < NumLocs ) {
          hay_salidas = true;
          print( salidas[ i ] );
          fputc_cons( ' ' );
        }
    }

    if ( !hay_salidas ) {
        print( "ninguna." );
    }

    lf();
}

void cmdTake_doIt(const Player * player, const Order * order)
{
	const Obj * obj = order->obj1;
	const char * msg = MSG_CANT_SEE;

	if ( obj != NULL ) {
		if ( obj->num_loc == player->num_loc ) {
			if ( obj->atr != Static ) {
				msg = MSG_DONE;
				obj->num_loc = PLAYER_NUM_LOC;
                
				do_loc_desc( player );                
                zx_movecursorto( SCR_FIRST_LINE_ANSWER, 0 );
                set_highlighted_colors();
			} else {
				msg = MSG_IMPOSSIBLE;
			}
		}
		else
		if ( obj->num_loc == PLAYER_NUM_LOC ) {
			msg = MSG_ALREADY_CARRIED;
		}
	}

	println( msg );
}

void cmdDrop_doIt(const Player * player, const Order * order)
{
	const char * msg = MSG_DONT_CARRIED;

	if ( order->obj1 != NULL ) {
		if ( order->obj1->num_loc == PLAYER_NUM_LOC ) {
            if ( !order->obj1->worn ) {
    			msg = MSG_DONE;
    			order->obj1->num_loc = player->num_loc;
                
    			do_loc_desc( player );
                zx_movecursorto( SCR_FIRST_LINE_ANSWER, 0 );
                set_highlighted_colors();
            } else {
                msg = "No puedes, lo llevas puesto.";
            }
		}
	}

	println( msg );
}

void cmdSwim_doIt(const Player * player, const Order * order)
{
	// Not used with this game.
}

void cmdWear_doIt(const Player * player, const Order * order)
{
    const char * msg;
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

    println( msg );
}

void cmdDisrobe_doIt(const Player * player, const Order * order)
{
    const char * msg;
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

    println( msg );
}

void cmdWait_doIt(const Player * player, const Order * order)
{
    println( "Pasa el tiempo..." );
}

void cmdBreak_doIt(const Player * player, const Order * order)
{
    println( "La simple violencia no soluciona nada en este caso." );
}

void cmdPush_doIt(const Player * player, const Order * order)
{
    println( "No tiene sentido." );
}

void cmdPull_doIt(const Player * player, const Order * order)
{
    println( "No tiene sentido." );
}

void cmdNop_doIt(const Player * player, const Order * order)
{
    println( MSG_CANT_DO );
}

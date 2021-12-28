// Reveni (c) 2020 Baltasar MIT License <baltasarq@gmail.com>

/* player.c */

#include "player.h"
#include "objs.h"
#include "locs.h"
#include "ctrl.h"

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>


const byte MAX_INV_OBJS = 4;


/** Inits the game
  * @param player The player structure
  */
void init_game(const Player * player)
{
	init_cmds();
	init_locs();
	init_objs();

    memset( player, 0, sizeof( Player ) );
	player->num_loc = 0;
	player->num_turns = 0;
    player->o2 = 42;
    player->energy = 0;
    player->timer = 21;
}

/** Ends the game */
void end_game(const Player * player, const char * msg)
{
    set_highlighted_colors();
    zx_movecursorto( SCR_FIRST_LINE_ANSWER, 0 );
	println( msg );
    
    set_default_colors();
    wait_for_key();

    clear_cmds_answer();
    zx_movecursorto( SCR_FIRST_LINE_CMDS, 0 );
    if ( !ask_yes_no( "Volver a jugar: " ) ) {
        cls();
        exit( 0 );
    } else {
        restart( player );
    }
}

void show_hud(const Player * player)
{
    byte o2_ink = INK_GREEN;
    byte energy_ink = INK_GREEN;
    byte timer_ink = INK_GREEN;
    
    if ( player->o2 < 15 ) {
        o2_ink = INK_RED;
    }
    
    if ( player->energy < 15 ) {
        energy_ink = INK_RED;
    }
    
    if ( player->timer < 15 ) {
        timer_ink = INK_RED;
    }
    
    zx_movecursorto( 2, 55 );
    set_colors( o2_ink, PAPER_BLACK );
    printk( "O2 : %02d", player->o2 );
    
    zx_movecursorto( 3, 55 );
    set_colors( energy_ink, PAPER_BLACK );
    printk( "ENG: %02d", player->energy );
    
    zx_movecursorto( 4, 55 );
    set_colors( timer_ink, PAPER_BLACK );
    printk( "TIM: %02d", player->timer / 2 );
    
    set_default_colors();
}

void proc1(const Player * player)
{
	const Obj * obj_cryo_geiser = locate_obj_by_id( "agujero" );
    const Obj * obj_floor = locate_obj_by_id( "suelo" );
    const Obj * obj_rocks = locate_obj_by_id( "rocas" );
    const Obj * obj_arc = locate_obj_by_id( "arco" );
    const Obj * obj_tunnel = locate_obj_by_id( "pasaje" );
    
    if ( player->num_loc != 12 ) {
        // Take the floor with you
        obj_floor->num_loc = player->num_loc;
        
        // Take the rocks with you
        obj_rocks->num_loc = player->num_loc;
    }
    
    if ( player->num_loc == 11
      || player->num_loc == 14 )
    {
        obj_tunnel->num_loc = player->num_loc;
        obj_arc->num_loc = player->num_loc;
    }

	// Take the geiser with you where appropriate
	if ( player->num_loc == 4
      || player->num_loc == 10 )
    {
		obj_cryo_geiser->num_loc = player->num_loc;
	}
	
	// Warning del cryo-geiser
    if ( ( player->num_loc == 4
       ||  player->num_loc == 10 )
      && player->num_turns % 3 == 0 )
    {
        zx_movecursorto( SCR_FIRST_LINE_ANSWER, 0 );
        set_highlighted_colors();
        println( "Un repentino temblor parece surgir del agujero, "
                 "de forma que se extiende por todo el suelo." );
        set_default_colors();
    }

    // Cryo-geiser
    if ( ( player->num_loc == 4
       ||  player->num_loc == 10 )
      && player->num_turns % 4 == 0 )
    {
        zx_movecursorto( SCR_FIRST_LINE_ANSWER, 0 );
        set_highlighted_colors();
        println( "El geiser estalla en una columna furiosa de vapor "
               "de agua... Notas el calor atravesando tu traje." );
        
        if ( player->num_loc == 4 ) {
            println( "Afortunadamente, la chimenea se asienta bastante "
                   "al sur, por lo que solo es una mera molestia." );
        } else {
            end_game( player, "Notas el calor abrasando tu cuerpo, "
                              "hasta el punto de dejar tu traje "
                              "reducido a una amalgama "
                              "derretida que produce graves "
                              "quemaduras en tu piel. Tus pulmones "
                              "pronto arden y notas la certeza de "
                              "la muerte." );
        }
        
        set_default_colors();
    }

    // End of game?
    if ( player->num_loc == 99 ) {
        end_game( player, "Lo has conseguido. Te introduces en el "
                          "complejo de rescate con todo lo necesario "
                          "para poder aguantar hasta que llegue el "
                          "rescate. Activas la radio-baliza para que "
                          "sepan el sitio en el que te encuentras... "
                          "Ahora solo resta esperar." );
    }
    
    return;
}

void proc2(const Player * player)
{
    // Breathing
    player->o2 -= ( player->o2 == 0 ? 0 : 1 );
    if ( player->o2 < 1 ) {
        end_game( player, "Al principio, te parece que no pasa nada, "
                          "que aunque el contador de o2 haya llegado "
                          "a cero puedes seguir respirando "
                          "sin problema. Pero entonces te das cuenta "
                          "de que inspirar se complica por momentos, "
                          "inhalando como un sabor rancio que hace "
                          "que te marees y caigas al suelo. Cansado."
                          "Solo un rato... un ratito..." );
    }
    
    // Timer
    player->timer -= ( player->timer == 0 ? 0 : 1 );
    if ( player->timer < 1 ) {
        end_game( player, "Notas como a tu alrededor, todo empieza a "
                          "arder. La tierra parece convertirse en "
                          "vapor que se eleva en grandes columnas "
                          "para dejar entrever un magma "
                          "blanco y rojo. Pronto caes en uno de "
                          "tantos agujeros mientras tu carne se "
                          "derrite." );
    }
    
    // Energy
    player->energy -= ( player->energy == 0 ? 0 : 1 );
    if ( player->energy == 1 ) {
        println( "Los potentes focos en los laterales de tu casco "
                    "parpadean y finalmente se apagan." );
    }
    if ( player->energy == 5 ) {
        println( "Los focos en los laterales de tu casco "
                    "parpadean brevemente... se agotan lentamente..." );
    }
    
    show_hud( player );
}

void resp(const Player * player, const Order * order)
{
    const Obj * obj_vaina = locate_obj_by_id( "vaina" );
    const Obj * obj_hill = locate_obj_by_id( "colina" );
    const Obj * obj_wall = locate_obj_by_id( "pared" );
    const Obj * obj_suit = locate_obj_by_id( "traje" );
    const Obj * obj_rubber = locate_obj_by_id( "caucho" );
    const Obj * obj_agujas = locate_obj_by_id( "agujas" );

    bool intercepted = false;
    
    if ( order->cmd->cmdId == CmdBreak
      && order->obj1 == obj_vaina )
    {
        intercepted = true;
        println( "El alunizaje ya la ha roto..." );
    }
    else
    if ( order->cmd->cmdId == CmdDrop
      && order->obj1 == obj_rubber
      && player->num_loc == 4 )
    {
        intercepted = true;
        println( "Dejas el caucho tan cerca como te es posible "
                 "del geiser, en un punto en el que apenas soportas "
                 "el calor. " );
        println( "Cuando vuelves, te das cuenta de "
                 "que se ha derretido y sin querer lo has pisado, "
                 "dejando tus botas envueltas en una capa de goma." );
    }
    else
    if ( ( order->cmd->cmdId == CmdBreak
        || order->cmd->cmdId == CmdDrop )
      && order->obj1 == obj_suit )
    {
        intercepted = true;
        end_game( player,
                  "Frustrado, rasgas el traje con la primera roca "
                  "afilada que encuentras. Notas como el precioso "
                  "aire sale silbando por la fisura, y como poco a "
                  "poco, te cuesta respirar y te sientes ahogado.\n"
                  "Incluso antes de perder el conocimiento, "
                  "te das cuenta de que vas a morir." );
    }
    else
    if ( ( order->cmd->cmdId == CmdPush
       || order->cmd->cmdId == CmdBreak
       || order->cmd->cmdId == CmdPull )
      && order->obj1 == obj_agujas )
    {
    	intercepted = true;

    	if ( locs[ 1 ].exits[ ExitSouth ] >= NumLocs ) {
    		obj_agujas->desc = "Rotas. Docenas de piedras "
    						   "yacen por todo el suelo.";
            
    		println( "Mueves las agujas, cuyas piedras, "
    			   "crujen, ceden y caen. "
    		   	   "Ha sido sorprendentemente sencillo, pese a su fuerte "
    		   	   "apariencia." );
            set_default_colors();
            wait_for_key();
            
            locs[ 1 ].desc = "Un valle se extiende de norte a sur. "
                     "Reducidos montones de piedras se desperdigan "
                     "en derredor.";
            locs[ 1 ].exits[ ExitSouth ] = 4;
            do_loc_desc( player );
    	} else {
    		println( "No tiene sentido seguir destruyendo." );
    	}
    }
    else
    if ( order->cmd->cmdId == CmdExamine
      && order->obj1 == obj_hill )
    {
        locs[ 5 ].exits[ ExitEast ] = 6;
    }
    else
    if ( order->cmd->cmdId == CmdExamine
      && order->obj1 == obj_wall )
    {
        locs[ 6 ].exits[ ExitEast ] = 12;
    }
    else
    if ( order->cmd->cmdId == CmdEast
      && player->num_loc == 6
      && locs[ 6 ].exits[ ExitEast ] < NumLocs )
    {
        intercepted = true;
        
        println( "Escalas las rocas de terraza en terraza, de manera "
               "que acabas por desplazarte hacia el sur siguiendo "
               "una de ellas, al no encontrar ninguna otra salida "
               "practicable." );
        set_default_colors();
        wait_for_key();
        
        player->num_loc = 12;
		do_loc_desc( player );
    }
    else
    if ( order->cmd->cmdId == CmdNorth
      && player->num_loc == 12 )
    {
        intercepted = true;
        
        println( "Sorteas las rocas para descender por las "
               "terrazas hasta el fondo de la profunda grieta." );
        set_default_colors();
        wait_for_key();
        
        player->num_loc = 6;
		do_loc_desc( player );
    }

    if ( !intercepted ) {
        order->cmd->doIt( player, order );
    }
}

void do_loc_desc(const Player * player)
{
    const byte num_loc = player->num_loc;
    const Loc * loc = &locs[ num_loc ];
	byte num_objs = how_many_objs_in( num_loc );

	// Show loc desc
	cls();
    draw_pic( loc->pic_data );
	zx_movecursorto( SCR_FIRST_LINE_TEXT, 0 );
    println( loc->desc );

	// Show objects here
	if ( num_objs > 0 ) {
		print( "\nPuedes ver:" );
		num_objs = list_objs_in( num_loc );
	}

	lf();
    lf();
}

bool ask_yes_no(const char * msg)
{
    char toret = 'n';

	zx_movecursorto( SCR_FIRST_LINE_CMDS, 0 );
    print( msg );

	print_word_marked_initial( "Positivo " );
	print_word_marked_initial( "Negativo " );
    toret = read_cmd_key();

    return ( toret != 'n' );
}

void restart(const Player * player)
{
    init_game( player );
    play_intro();
    do_loc_desc( player );
}

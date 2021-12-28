// Reveni (c) 2020 Baltasar MIT License <baltasarq@gmail.com>


#include "ctrl.h"
#include "locs.h"
#include "cmds.h"
#include "objs.h"
#include "player.h"

#include <input.h>
#include <graphics.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <spectrum.h>
#include <sound.h>


const char * PROMPT_WAIT = "<...>";


void cls()
{
	zx_cls();
	zx_border( INK_BLACK );
	zx_colour( INK_WHITE | PAPER_BLACK );
}

void set_colors(byte ink, byte paper)
{
	zx_setink( ink );
	zx_setpaper( paper );
}

void set_default_colors()
{
	zx_setink( INK_WHITE );
}

void set_highlighted_colors()
{
	zx_setink( INK_CYAN );
}

byte read_key()
{
	byte key = in_Inkey();

    // Read from keyboard
	while ( key == 0 ) {
		key = in_Inkey();
	}

    in_WaitForNoKey();
	return key;
}

void wait_for_key()
{
    print( PROMPT_WAIT );
    read_key();
}

/** Clears the input commands & answer section */
void clear_cmds_answer()
{
	clga( 0,
		  8 * SCR_FIRST_LINE_ANSWER,
		  32 * 8,
		  ( SCR_MAX_LINES - SCR_FIRST_LINE_ANSWER ) * 8 );
}

void print_word_marked_initial(const char * word)
{
	char initial_ch = *word;

	zx_setattrinverse( true );
	fputc_cons( initial_ch );
	zx_setattrinverse( false );
	print( word + 1 );
}

void print_marked_initial_objs_ids_in_vector(const Obj **v)
{
	const Obj ** obj = v;

	set_highlighted_colors();
	zx_movecursorto( SCR_FIRST_LINE_CMD_OBJS, 0 );

	while( *obj != NULL ) {
		print_word_marked_initial( ( *obj )->id );
		fputc_cons( ' ' );
		++obj;
	}

	set_default_colors();
}

byte read_cmd_key()
{
	byte key = read_key();

	while ( !isalpha( key ) ) {
		key = tolower( read_key() );
	}

	return key;
}

void print_cmds()
{
	// Print basic options
	zx_movecursorto( SCR_FIRST_LINE_CMDS, 0 );
	print_word_marked_initial( "Inv " );
	print_word_marked_initial( "Mira alrededor " );
	fputc_cons( 'E' ); print_word_marked_initial( "xamina... " );
	print_word_marked_initial( "Norte " );
	print_word_marked_initial( "Sur " );
	print_word_marked_initial( "Este " );
	print_word_marked_initial( "Oeste " );
	print_word_marked_initial( "Arriba " );
	fputc_cons( 'A' ); print_word_marked_initial( "bajo\n" );

	// Print object manipulation options
	print_word_marked_initial( "Coge... " );
	print_word_marked_initial( "Deja... " );
	print( "Em" ); print_word_marked_initial( "puja... " );
	print_word_marked_initial( "Tira de... " );
	print_word_marked_initial( "Rompe... " );
}

const Order * input_cmd(const Player * player)
{
	static const char * ExitCmds = "nseoab";
	static Order toret;

	// Prepare order
	memset( &toret, 0, sizeof( Order ) );

	// Ask cmd
	print_cmds();
	byte key = read_cmd_key();

	// Play sound
	bit_fx( 6 );

	if ( key == 'x'
	  || key == 'c'
	  || key == 'd'
	  || key == 'p'
	  || key == 't'
	  || key == 'r' )
	{
		// Infer command
		byte cmd_index = CmdExamine;

		switch( key ) {
			case 'c':	cmd_index = CmdTake; break;
			case 'd':	cmd_index = CmdDrop; break;
			case 'p':	cmd_index = CmdPush; break;
			case 't':	cmd_index = CmdPull; break;
			case 'r':	cmd_index = CmdBreak; break;
		}

		toret.cmd = &cmds[ cmd_index ];


		// Show objects
		const Obj ** present = get_objs_in_player_and( player->num_loc );
		const Obj ** obj = present;

		print_marked_initial_objs_ids_in_vector( present );

		// Which one?
		key = read_cmd_key();

		// Which object?
		while( obj != NULL ) {
			const char * obj_id = ( *obj )->id;

			if ( *obj_id == key ) {
				toret.obj1 = *obj;
				break;
			}

			++obj;
		}

		// Play sound
		bit_fx( 6 );
	}
	else
	if ( key == 'i' ) {
		toret.cmd = &cmds[ CmdInventory ];
	}
	else
	if ( key == 'm' ) {
		toret.cmd = &cmds[ CmdLookAround ];
	}
	else
	if ( key == 'n'
	  || key == 's'
	  || key == 'e'
	  || key == 'o'
	  || key == 'a'
	  || key == 'b' )
	{
		byte pos = strchr( ExitCmds, key ) - ExitCmds;

		toret.cmd = &cmds[ pos ];
	}

	clear_cmds_answer();
	return &toret;
}

void print(const char * txt)
{
    byte pos = SCR_MAX_COLS - 1;

    while( pos < strlen( txt ) ) {
        while( pos > 2
            && !isspace( txt[ pos ] ) )
        {
            --pos;
        }

        txt[ pos ] = '\n';
        pos += SCR_MAX_COLS - 1;
    }

    printk( txt );
}

void draw_pic(const byte * ddata)
{
	if ( ddata != NULL ) {
		byte pos = 0;
		
		for(;ddata[ pos ] != DCMD_EOD; ++pos) {
			switch( ddata[ pos ] ) {
				case DCMD_Line:
					++pos;
					draw( ddata[ pos ], ddata[ pos + 1 ],
						ddata[ pos + 2 ], ddata[ pos + 3 ] );
					pos += 3;
					break;
				case DCMD_Circle:
					++pos;
					circle( ddata[ pos ], ddata[ pos + 1 ],
							ddata[ pos + 2 ], 1 );
					pos += 2;
					break;
				case DCMD_Fill:
					++pos;
					fill( ddata[ pos ], ddata[ pos + 1 ] );
					++pos;
					break;
			}
		}
	}
    
    return;
}

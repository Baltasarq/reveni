// Reveni (c) 2020 Baltasar MIT License <baltasarq@gmail.com>


#include "ctrl.h"
#include "locs.h"
#include "cmds.h"
#include "objs.h"
#include "player.h"

#include <input.h>
#include <spectrum.h>
#include <graphics.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>


const char * PROMPT = ":> ";
const char * PROMPT_WAIT = "<...>";


void cls()
{
	fputc_cons( 12 );
	zx_border( INK_BLACK );
	zx_colour( INK_WHITE | PAPER_BLACK );
}

void set_colors(int ink, int paper)
{
    fputc_cons( 16 );
    fputc_cons( 32 + ink );
    
    fputc_cons( 17 );
    fputc_cons( 32 + paper );
}

void set_default_colors()
{
	fputc_cons( 16 );
    fputc_cons( 32 + INK_WHITE );
}

void set_highlighted_colors()
{
	fputc_cons( 16 );
    fputc_cons( 48 + INK_CYAN );
}

void set_inverse_colors(bool is_inverse)
{
	int inverse = 48;							// 48 == off, 49 == on

	if ( is_inverse ) {
		inverse = 49;
	}

	fputc_cons(20); fputc_cons( inverse );
}

void set_cursor_pos(int row, int col)
{
	fputc_cons( 22 );
	fputc_cons( row + 32 );
	fputc_cons( col + 32 );
}

int read_key()
{
	int key = in_Inkey();

    // Read from keyboard
	while ( key == 0 ) {
		key = in_Inkey();
	}

    // Wait until key is released
	while( in_Inkey() != 0 );

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
		  8 * FIRST_LINE_ANSWER,
		  32 * 8,
		  ( MAX_LINES - FIRST_LINE_ANSWER ) * 8 );
}

void print_word_marked_initial(const char * word)
{
	char initial_ch = *word;

	set_inverse_colors( true );
	print_char( initial_ch );
	set_inverse_colors( false );
	print( word + 1 );
}

void print_marked_initial_objs_ids_in_vector(Obj **v)
{
	Obj ** obj = v;

	set_highlighted_colors();
	set_cursor_pos( FIRST_LINE_CMD_OBJS, 0 );

	while( *obj != NULL ) {
		print_word_marked_initial( ( *obj )->id );
		print_char( ' ' );
		++obj;
	}

	set_default_colors();
}

int read_cmd_key()
{
	int key = read_key();

	while ( !isalpha( key ) ) {
		key = tolower( read_key() );
	}

	return key;
}

void print_cmds()
{
	// Print basic options
	set_cursor_pos( FIRST_LINE_CMDS, 0 );
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

Order * input_cmd(Player * player)
{
	static const char * ExitCmds = "nseoab";
	static Order toret;

	// Prepare order
	memset( &toret, 0, sizeof( Order ) );

	// Ask cmd
	print_cmds();
	int key = read_cmd_key();

	if ( key == 'x'
	  || key == 'c'
	  || key == 'd'
	  || key == 'p'
	  || key == 't'
	  || key == 'r' )
	{
		// Get the present objects
		const Obj ** present = get_objs_in_player_and( player->num_loc );
		Obj ** obj = present;

		// Infer command
		int cmd_index = CmdExamine;

		switch( key ) {
			case 'c':	cmd_index = CmdTake; break;
			case 'd':	cmd_index = CmdDrop; break;
			case 'p':	cmd_index = CmdPush; break;
			case 't':	cmd_index = CmdPull; break;
			case 'r':	cmd_index = CmdBreak; break;
		}

		toret.cmd = &cmds[ cmd_index ];

		// Show them
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
		int pos = strchr( ExitCmds, key ) - ExitCmds;

		toret.cmd = &cmds[ pos ];
	}

	clear_cmds_answer();
	return &toret;
}

void print_char(int ch)
{
    fputc_cons( ch );
}

void print(const char * txt)
{
    int pos = MAX_COLS - 1;

    while( pos < strlen( txt ) ) {
        while( pos > 2
            && !isspace( txt[ pos ] ) )
        {
            --pos;
        }

        txt[ pos ] = '\n';
        pos += MAX_COLS - 1;
    }

    printk( txt );
}

void draw_pic(int * ddata)
{
    int pos = 0;
    
    for(;ddata[ pos ] != 0; ++pos) {
        switch( ddata[ pos ] ) {
            case 1:
                ++pos;
                draw( ddata[ pos ], ddata[ pos + 1 ],
                      ddata[ pos + 2 ], ddata[ pos + 3 ] );
                pos += 3;
                break;
            case 2:
                ++pos;
                circle( ddata[ pos ], ddata[ pos + 1 ],
                        ddata[ pos + 2 ], 1 );
                pos += 2;
                break;
            case 3:
                ++pos;
                fill( ddata[ pos ], ddata[ pos + 1 ] );
                ++pos;
                break;
        }
    }
    
    return;
}

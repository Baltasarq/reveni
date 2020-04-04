// Reveni (c) 2020 Baltasar MIT License <baltasarq@gmail.com>


#include "ctrl.h"
#include "locs.h"
#include "cmds.h"
#include "objs.h"

#include <input.h>
#include <spectrum.h>
#include <graphics.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>


const char * PROMPT = ":> ";
const char * PROMPT_WAIT = "<...>";


void cls()
{
	fputc_cons( 12 );
	zx_border( INK_BLACK );
	zx_colour( INK_WHITE | PAPER_BLACK );
}

void set_default_colors()
{
	fputc_cons( 16 );
    fputc_cons( 32 + INK_WHITE );
}

void set_highlighted_colors()
{
	fputc_cons( 16 );
    fputc_cons( 32 + INK_YELLOW );
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

	while ( key == 0 ) {
		key = in_Inkey();
	}

	while( in_Inkey() != 0 );

	return key;
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
	printf( "%c", initial_ch );
	set_inverse_colors( false );
	printf( "%s", word + 1 );
}

void print_marked_initial_objs_ids_in_vector(Obj **v)
{
	Obj ** obj = v;

	set_highlighted_colors();
	set_cursor_pos( FIRST_LINE_CMD_OBJS, 0 );

	while( *obj != NULL ) {
		print_word_marked_initial( (*obj)->id );
		printf( " " );
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
	fputc_cons( 'E' ); print_word_marked_initial( "mpuja... " );
	print_word_marked_initial( "Tira de... " );
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
	  || key == 'm'
	  || key == 't' )
	{
		const Obj ** present = get_objs_in_player_and( player->num_loc );
		Obj ** obj = present;

		print_marked_initial_objs_ids_in_vector( present );

		key = read_cmd_key();

		toret.cmd = &cmds[ CmdExamine ];

		while( obj != NULL ) {
			const char * obj_id = ( *obj )->id;

			if ( *obj_id == key ) {
				toret.obj1 = *obj;
				toret.obj2 = NULL;
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

    printf( "%s\n", txt );
}

void do_loc_desc(int num_loc)
{
	int num_objs = how_many_objs_in( num_loc );

	// Show loc desc
	cls();
	set_cursor_pos( FIRST_LINE_TEXT, 0 );
    print( locs[ num_loc ].desc );

	// Show objects here
	if ( num_objs > 0 ) {
		printf( "\nPuedes ver:" );
		num_objs = list_objs_in( num_loc );
	}

	printf( "\n\n" );
}

void restart(Player * player)
{
    init_game( player );
    play_intro();
    cls();
}

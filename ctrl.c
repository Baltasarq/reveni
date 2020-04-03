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


const int MAX_COLS = 64;
const int FIRST_LINE_TEXT = 8;
const int FIRST_LINE_ANSWER = 15;
const int FIRST_LINE_CMDS = 20;
const int MAX_LINES = 24;
const char * PROMPT = ":> ";
const char * PROMPT_WAIT = "Pulsa ENTER...";


void cls()
{
	fputc_cons(12);
	zx_border( INK_BLACK );
	zx_colour( INK_WHITE | PAPER_BLACK );
}

void set_default_colors()
{
	fputc_cons( 16 );
    fputc_cons( 32 + INK_WHITE );
}

void set_answer_colors()
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

	return key;
}

/** Clears the input commands & answer section */
void clear_cmds_answer()
{
	clga( 0, 8 * FIRST_LINE_ANSWER,
		  32 * 8, ( MAX_LINES - FIRST_LINE_ANSWER ) * 8 );
}

void print_word_marked_initial(const char * word)
{
	char initial_ch = *word;

	set_inverse_colors( true );
	printf( "%c", initial_ch );
	set_inverse_colors( false );
	printf( "%s", word + 1 );
}

char * input_cmd()
{
	static char buffer[32];

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

	int key = read_key();

	while ( !isalpha( key ) ) {
		key = read_key();
	}

	*buffer = 0;

	if ( key == 'i'
	  || key == 'n'
	  || key == 's'
	  || key == 'e'
	  || key == 'o'
	  || key == 'm' )
	{
		*buffer = key;
		*( buffer + 1 ) = 0;
	}

	clear_cmds_answer();
	set_cursor_pos( FIRST_LINE_ANSWER, 0 );
	return buffer;
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

bool is_word_in_syns(char * word, char * syns)
{
  static char search_word[LengthWord + 3];
  int word_length = strlen( word );

  // Build search word
  *search_word = ' ';
  strcpy( search_word + 1, word );
  *( search_word + word_length + 1 ) = ' ';
  *( search_word + word_length + 2 ) = 0;

  // Determine if included
  // printf( "'%s' in '%s'%c", search_word, syns, 13 );
  return ( strstr( syns, search_word ) != NULL );
}

bool is_word_ignorable(char * word)
{
  static const char * ignorable_words =
      " un una unos unas el la los las "
      "y tambien luego "
      "a al ante bajo cabe con contra de desde en "
      "entre hacia hasta para por segun "
      "sin so sobre tras ";

  return is_word_in_syns( word, ignorable_words );
}

void assign_word(Order * order, char * word)
{
  /* Truncate word, if needed */
  if ( strlen( word ) > LengthWord ) {
    *( word + LengthWord ) = 0;
  }

  /* Assign word to the appropriate slot in the order */
  if ( order->word2 == NULL ) {                   // Still something to assign?
    if ( !is_word_ignorable( word ) ) {
      // Store word's address in Order's pointers
      if ( order->verb == NULL ) {
        order->verb = word;
      } else {
        if ( order->word1 == NULL ) {
          order->word1 = word;
        } else {
          order->word2 = word;
        }
      }
    }
  }

  return;
}

Cmd * find_cmd(char * word)
{
    Cmd * toret = NULL;
    int i = 0;

    if ( word != NULL
      && strlen( word ) > 0 )
    {
        // Find command
        for (; i < NumCmds; ++i) {
            if ( is_word_in_syns( word, cmds[i].words ) ) {
                break;
            }
        }

        if ( i < NumCmds ) {
          toret = &cmds[ i ];
        } else {
          toret = cmdNop;
        }
    }

    return toret;
}

Obj * find_obj(Player * player, char * word)
{
    int i = 0;
    Obj * toret = NULL;

    if ( word != NULL
      && strlen( word ) > 0 )
    {
        for(; i < NumObjs; ++i) {
            if ( ( objs[ i ].num_loc == player->num_loc
                || objs[ i ].num_loc == PLAYER_NUM_LOC )
              && is_word_in_syns( word, objs[ i ].words ) )
            {
                toret = &objs[ i ];
                break;
            }
        }
    }

	return toret;
}

void find_words(Player * player, Order * order)
{
    order->cmd = find_cmd( order->verb );
    order->obj1 = find_obj( player, order->word1 );
    order->obj2 = find_obj( player, order->word2 );
}

Order * parse(Player * player, char * buffer)
{
	static Order toret;
	char * p = buffer;
	char * word = buffer;

	/* Init order */
	memset( &toret, 0, sizeof( toret ) );
	toret.cmd = cmdNop;

	/* Get to the input */
	while ( isspace( *p ) ) {
		++p;
		++word;
	}

	/* Run all over the input */
	while ( *p != 0
		 && *p != '\n'
		 && *p != '\r'
  	     && toret.word2 == NULL )
	{
		if ( *p == ' ' ) {
			*p = 0;
			assign_word( &toret, word );
			word = p + 1;
		} else {
			*p = tolower( *p );
		}

		++p;
	}

	// Last word
	*p = 0;
	assign_word( &toret, word );

	find_words( player, &toret );
	return &toret;
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

// Reveni (c) 2020 Baltasar MIT License <baltasarq@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <stdbool.h>

#include "player.h"
#include "cmds.h"
#include "locs.h"
#include "objs.h"


/* Constants */
const int MAX_COL = 65;
const char * PROMPT = ":> ";
const char * PROMPT_WAIT = "Pulsa ENTER...";

/* Fns */
void cls();
char * input(const char *);
void print(const char * txt);
Order * parse(Player * player, char * buffer);

void play_intro()
{
  cls();

  textcolor( BLACK );

  printf( "Reveni v1.0 20200411\n"
          "(c) 2020 Baltasar <baltasarq@gmail.com>\n\n" );
  print( "Teclea \"ayuda\" para conocer los posibles comandos.\n\n\n\n\n\n" );

  set_default_colors();

  print( "Un perfecto tiempo de descanso en las profundidades de la estaca "
          "de Bares. Buceando, disfrutando del momento de paz y sosiego que "
          "tan solo las bajas temperaturas a diez metros bajo la superficie "
          "del mar pueden ofrecerte.\n\n"
  );

  input( PROMPT_WAIT );
}

void restart(Player * player)
{
    init_game( player );
    play_intro();
    cls();
}

void do_loc_desc(int num_loc)
{
	int num_objs = how_many_objs_in( num_loc );

	// Show loc desc
	printf( "\n\n" );
    print( locs[ num_loc ].desc );

	// Show objects here
	if ( num_objs > 0 ) {
		printf( "\nPuedes ver:" );
		num_objs = list_objs_in( num_loc );
	}

	printf( "\n\n" );
}

int main()
{
	char * buffer;
	Player player;
	Order * order;

	init_game( &player );
	play_intro();

	// Main loop
	cls();
	do {
		// Proc1
        set_default_colors();
		do_loc_desc( player->num_loc );
		proc1( &player );

		do {
			buffer = input( PROMPT );
		} while( strlen( buffer ) == 0 );

		// Parse order
        set_answer_colors();
		order = parse( &player, buffer );
        resp( &player, order );

		// Proc2
		if ( order->cmd != cmdNop ) {
		  player.num_turns += 1;
		  proc2( &player );
		}
	} while( order->cmd.cmdId != CmdEnd );

	return EXIT_SUCCESS;
}

void set_default_colors()
{
    textbackground( WHITE );
    textcolor( BLUE );
}

void set_answer_colors()
{
    textbackground( WHITE );
    textcolor( BLACK );
}

/** Cleans the screen and sets the appropriate colors */
void cls()
{
  clrscr();
  set_default_colors();
}

/** Takes an order from the user
  * @param msg The message to show to the user.
  * @return A pointer to the char[] buffer */
char * input(const char * msg)
{
	char * last_char = NULL;
	static char buffer[32];

	// Prompt
    textbackground( BLUE );
    textcolor( YELLOW );

	cprintf( "%s", msg );
	fflush( stdout );

	// Get order
    set_default_colors();
    textcolor( RED );

	printf( " " );
	fgets( buffer, 32, stdin );

	// Remove last '\n'
	last_char = buffer + ( strlen( buffer ) - 1 );

	if ( *last_char == '\n' ) {
		*last_char = 0;
	}

    set_default_colors();
	return buffer;
}

/** Prints a (possibly) long text, taking max columns into account.
  * Warning: it modifies text, substituting spaces by CR.
  * @param txt The text to print, as a char *
  */
void print(const char * txt)
{
    int pos = MAX_COL - 1;

    while( pos < strlen( txt ) ) {
        while( pos > 2
            && !isspace( txt[ pos ] ) )
        {
            --pos;
        }

        txt[ pos ] = '\n';
        pos += MAX_COL - 1;
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

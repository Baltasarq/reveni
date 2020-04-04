// Reveni (c) 2020 Baltasar MIT License <baltasarq@gmail.com>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ctrl.h"


void play_intro()
{
	cls();
	set_default_colors();

	set_cursor_pos( FIRST_LINE_TEXT, 0 );
	printf( "Reveni v1.0 20200411 "
        	"(c) 2020 Baltasar <baltasarq@gmail.com>\n\n" );

	print( "La nave espacial mercante 'Aristarco' vuelve desde "
  			"'Proxima Centauri' con un cargamento minero.\n"
  			"En la soledad del espacio, el aislado tripulante "
  			"duerme en el interior de su vaina de crio-letargo.\n" );

	set_highlighted_colors();

	print( "De repente, un meteorito impacta en el carguero, "
  			"y la nave te despierta a ti, Daesder, el piloto.\n" );

	set_default_colors();
	print( "No hay tiempo. Tu vaina se acopla a otra mayor y sale "
		   "despedida por babor, rumbo a Ceres.\n\n" );

	printf( PROMPT_WAIT );
	read_key();
}

int main()
{
	Player player;
	Order * order;

	init_game( &player );
	play_intro();

	// Main loop
	cls();
	set_default_colors();
	do_loc_desc( player.num_loc );
	do {
		// Proc1
		proc1( &player );

		order = input_cmd( &player );

		if ( order->cmd != NULL ) {
			set_cursor_pos( FIRST_LINE_ANSWER, 0 );
		    set_highlighted_colors();

        	resp( &player, order );

			// Proc2
			if ( order->cmd != cmdNop ) {
		  		player.num_turns += 1;
		  		proc2( &player );
			}

			set_default_colors();
		}
	} while( order->cmd->cmdId != CmdEnd );

	return EXIT_SUCCESS;
}

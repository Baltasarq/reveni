// Reveni (c) 2020 Baltasar MIT License <baltasarq@gmail.com>


#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "ctrl.h"
#include "player.h"


void draw_presentation()
{
    int pic_data[] = {
        2, /* circle */ 50, 10, 10,
        3, /* fill   */ 50, 10,
        2, /* circle */ 100, 15, 25,
        0  /* end    */
    };
    
    draw_pic( pic_data );
}

void play_intro()
{
	cls();
	set_default_colors();

    draw_presentation();
    
	set_cursor_pos( FIRST_LINE_TEXT, 0 );
	println( "Reveni v1.0 20200411 "
        	"(c) 2020 Baltasar <baltasarq@gmail.com>" );
    lf();

	println( "La nave espacial mercante Aristarco vuelve desde "
  			 "Proxima Centauri con un cargamento minero, "
             "navegando cercana a Neptuno. "
             "En la soledad del espacio, el aislado tripulante "
  			 "duerme en el interior de su vaina de crio-letargo." );
    lf();

	set_highlighted_colors();
	println( "De repente, un meteorito impacta en el carguero, "
  			 "y la nave te despierta a ti, Daesder, el piloto." );
    lf();

	set_default_colors();
	println( "No hay tiempo. Tu vaina se acopla a otra mayor y sale "
		     "despedida por babor, rumbo a Ceres." );
    lf();
	wait_for_key();
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
	do_loc_desc( &player );

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

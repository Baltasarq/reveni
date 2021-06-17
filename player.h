// Reveni (c) 2020 Baltasar MIT License <baltasarq@gmail.com>

/* Player status */

#ifndef _INCLUDE_PLAYER_H
#define _INCLUDE_PLAYER_H

#include "cmds.h"


extern const int MAX_INV_OBJS;
extern const char * PROMPT_WAIT;

typedef struct _Player {
    int num_loc;
    int num_turns;
    int o2;
    int energy;
    int timer;
} Player;


/** Prepares the game. */
extern void init_game(Player *);

/** Executed just after describing the current loc
  * @param player The player structure
  */
extern void proc1(Player *);

/** Executed after resp() answered to a successful command
  * @param player The player structure
  */
extern void proc2(Player *);

/** Executed after user's prompt.
  * @param player A pointer to a Player structure
  * @param order A pointer to an Order structure
  */
extern void resp(Player *, Order *);

/** Describes a given loc. */
extern void do_loc_desc(Player * player);

/** Asks yes o no to the user, given a message
    @param msg The message to show to the user.
    @return false if the first letter of the user's reply is 'n',
    		true otherwise.
*/
extern bool ask_yes_no(const char * msg);

/** Restarts the game. */
extern void restart(struct _Player * player);

/** Shows the hud info. **/
extern void show_hud();

#endif

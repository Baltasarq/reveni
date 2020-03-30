// Reveni (c) 2020 Baltasar MIT License <baltasarq@gmail.com>

/* Player status */

#ifndef _INCLUDE_PLAYER_H
#define _INCLUDE_PLAYER_H

#include "cmds.h"

extern const int MAX_INV_OBJS;

typedef struct _Player {
    int num_loc;
    int num_turns;
} Player;

extern void init_game(Player *);
extern void play_intro();
extern void cls();
extern bool ask_yes_no(const char * msg);
extern void set_default_colors();
extern void set_answer_colors();
extern void print(const char *);
extern char * input(const char *);
extern void proc1(Player *);
extern void proc2(Player *);
extern void resp(Player *, Order *);

extern const char * PROMPT_WAIT;

#endif

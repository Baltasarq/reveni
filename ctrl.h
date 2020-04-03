// Reveni (c) 2020 Baltasar MIT License <baltasarq@gmail.com>


#ifndef _INCLUDE_CTRL_H_
#define _INCLUDE_CTRL_H_

#include "player.h"

#include <stdbool.h>


extern const int MAX_COLS;
extern const int FIRST_LINE_TEXT;
extern const int FIRST_LINE_ANSWER;
extern const int FIRST_LINE_CMDS;
extern const int MAX_LINES;
extern const char * PROMPT;
extern const char * PROMPT_WAIT;


/** Cleans the screen and sets the appropriate colors */
extern void cls();

/** @return The scancode of the key read. */
extern int read_key();

/** Prints a (possibly) long text, taking max columns into account.
  * Warning: it modifies text, substituting spaces by CR.
  * @param txt The text to print, as a char *
  */
extern void print(const char * txt);

extern void set_inverse_colors(bool is_inverse);
extern void set_default_colors();
extern void set_answer_colors();
extern void set_cursor_pos(int row, int col);

/** Describes a given loc. */
extern void do_loc_desc(int num_loc);

/** Takes an order from the user
  * @return A pointer to the char[] buffer */
extern char * input_cmd();
extern Order * parse(Player * player, char * buffer);
extern void restart(Player * player);

#endif

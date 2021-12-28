// Reveni (c) 2020 Baltasar MIT License <baltasarq@gmail.com>


#ifndef _INCLUDE_CTRL_H_
#define _INCLUDE_CTRL_H_

#include <stdbool.h>

#include "data.h"

struct _Player;
struct _Order;

enum Screen {
				SCR_FIRST_LINE_TEXT = 8,
				SCR_FIRST_LINE_ANSWER = 14,
				SCR_FIRST_LINE_CMDS = 20,
				SCR_MAX_LINES = 24,
				SCR_FIRST_LINE_CMD_OBJS = 22,
				SCR_MAX_COLS = 64
};


extern const char * PROMPT;
extern const char * PROMPT_WAIT;


/** Cleans the screen and sets the appropriate colors */
extern void cls();

/** @return The scancode of the key read. */
extern byte read_key();

/** Displays a "wait for key" prompt like <...> and waits for a key */
extern void wait_for_key();

/** Prints a (possibly) long text in the current position on the screen,
  * taking max columns into account.
  * Warning: it modifies text (if needed), substituting spaces by CR.
  * @param txt The text to print, as a char *
  */
extern void print(const char * txt);

/** Carriage return. */
#define lf()                    fputc_cons( '\n' )

/** Print and lf */
#define println(txt)            print(txt); lf()

/** Prints a single word, with the initial in inverse colors.
  * @param word The word to print, as a char *
  */
extern void print_word_marked_initial(const char * word);

extern void set_default_colors();
extern void set_highlighted_colors();
extern void set_colors(byte ink, byte paper);

/** Clears the screen zone for answers and commands. */
extern void clear_cmds_answer();

/** Takes an order from the user
  * @return A pointer to the char[] buffer */
extern const struct _Order * input_cmd();

/** Takes an order from the user
  * @return The char of the corresponding key. */
extern byte read_cmd_key();

/** Shows the game's intro. */
extern void play_intro();

/** Draws a picture following the data in ddata. */ 
void draw_pic(const byte * ddata);

#endif

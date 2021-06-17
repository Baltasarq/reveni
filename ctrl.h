// Reveni (c) 2020 Baltasar MIT License <baltasarq@gmail.com>


#ifndef _INCLUDE_CTRL_H_
#define _INCLUDE_CTRL_H_

#include <stdbool.h>


struct _Player;
struct _Order;

enum Screen {
				FIRST_LINE_TEXT = 8,
				FIRST_LINE_ANSWER = 14,
				FIRST_LINE_CMDS = 20,
				MAX_LINES = 24,
				FIRST_LINE_CMD_OBJS = 22,
				MAX_COLS = 64
};


extern const char * PROMPT;
extern const char * PROMPT_WAIT;


/** Cleans the screen and sets the appropriate colors */
extern void cls();

/** @return The scancode of the key read. */
extern int read_key();

/** Displays a "wait for key" prompt like <...> and waits for a key */
extern void wait_for_key();

/** Prints a single char in the current position on the screen. */
extern void print_char(int ch);

/** Prints a (possibly) long text in the current position on the screen,
  * taking max columns into account.
  * Warning: it modifies text (if needed), substituting spaces by CR.
  * @param txt The text to print, as a char *
  */
extern void print(const char * txt);

/** Carriage return. */
#define lf()                    print_char( '\n' )

/** Print and lf */
#define println(txt)            print(txt); lf()

/** Prints a single word, with the initial in inverse colors.
  * @param word The word to print, as a char *
  */
extern void print_word_marked_initial(const char * word);

extern void set_inverse_colors(bool is_inverse);
extern void set_default_colors();
extern void set_highlighted_colors();
extern void set_cursor_pos(int row, int col);
extern void set_colors(int ink, int paper);

/** Clears the screen zone for answers and commands. */
extern void clear_cmds_answer();

/** Takes an order from the user
  * @return A pointer to the char[] buffer */
extern struct _Order * input_cmd();

/** Takes an order from the user
  * @return The char of the corresponding key. */
extern int read_cmd_key();

/** Shows the game's intro. */
extern void play_intro();

/** Draws a picture following the data in ddata. */ 
void draw_pic(int * ddata);

#endif

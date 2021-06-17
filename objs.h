// Reveni (c) 2020 Baltasar MIT License <baltasarq@gmail.com>

/* Objects */

#ifndef _INCLUDE_OBJS_H
#define _INCLUDE_OBJS_H

#include <stdbool.h>

typedef enum _objLimits { NumObjs = 15 } ObjLimits;

extern const int PLAYER_NUM_LOC;
extern const int LIMBO;

typedef enum _Atr {
	Static, Portable, Clothing
} Atr;

typedef struct _Obj {
	char * id;
	char * desc;
	char * words;
	int num_loc;
    bool worn;
	Atr atr;
} Obj;

/** The vector for all objects **/
extern Obj objs[];

/** Prepares everything related to objects **/
extern void init_objs();

/** Lists all objects pertaining to a location (outputs to console)
	@param num_loc the loc to consider (PLAYER_NUM_LOC for player).
	@return the number of objects found.
*/
extern int list_objs_in(int num_loc);

/** @return the number of objects in a given location
	@param num_loc the loc to consider (PLAYER_NUM_LOC for player).
*/
extern int how_many_objs_in(int num_loc);

/** @return a NULL-terminated static-allocated vector
			with all objects in a given location.
	@param num_loc the loc to consider (PLAYER_NUM_LOC for player).
*/
extern const Obj ** get_objs_in(int num_loc);

/** @return a NULL-terminated static-allocated vector
			with all objects in a given location,
			and carried by the player.
	@param num_loc the loc to consider (don't use PLAYER_NUM_LOC).
*/
extern const Obj ** get_objs_in_player_and(int num_loc);

/** @return the object corresponding to a given id,
			or NULL if not found.
*/
extern Obj * locate_obj_by_id(const char * id);

#endif

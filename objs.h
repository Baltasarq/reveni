// Reveni (c) 2020 Baltasar MIT License <baltasarq@gmail.com>

/* Objects */

#ifndef _INCLUDE_OBJS_H
#define _INCLUDE_OBJS_H

#include <stdbool.h>

typedef enum _objLimits { NumObjs = 27 } ObjLimits;

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

extern Obj objs[];
extern void init_objs();
extern int list_objs_in(int num_loc);
extern int how_many_objs_in(int num_loc);
extern Obj * locate_obj_by_id(const char * id);

#endif


// Reveni (c) 2020 Baltasar MIT License <baltasarq@gmail.com>

/* Rooms */

#ifndef _INCLUDE_LOCS_H
#define _INCLUDE_LOCS_H

typedef enum _locLimits { NumLocs = 24, NumExits = 6 } LocLimits;

typedef enum _Exits {
    ExitNorth,
    ExitSouth,
    ExitEast,
    ExitWest,
    ExitUp,
    ExitDown
} Exits;

typedef struct _Loc {
  char * desc;
  int exits[NumExits];
} Loc;

extern Loc locs[];
extern void init_locs();

#endif

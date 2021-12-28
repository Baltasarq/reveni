// Reveni (c) 2020 Baltasar MIT License <baltasarq@gmail.com>

/* Rooms */

#ifndef _INCLUDE_LOCS_H
#define _INCLUDE_LOCS_H

#include "data.h"

typedef enum _locLimits { NumLocs = 15, NumExits = 6 } LocLimits;

typedef enum _drawCmd {
    DCMD_EOD,
    DCMD_Line,
    DCMD_Circle,
    DCMD_Fill
} DrawCmd;

typedef enum _exits {
    ExitNorth,
    ExitSouth,
    ExitEast,
    ExitWest,
    ExitUp,
    ExitDown
} Exits;

typedef struct _loc {
  char * desc;
  byte * pic_data;
  byte exits[NumExits];
} Loc;

extern Loc locs[];
extern void init_locs();

#endif

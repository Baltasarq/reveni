// Reveni (c) 2020 Baltasar MIT License <baltasarq@gmail.com>

/* Commands */

#ifndef _INCLUDE_CMDS_H
#define _INCLUDE_CMDS_H

#include "objs.h"

typedef enum _cmdLimits { LengthWord = 5, NumCmds = 21 } CmdLimits;

typedef enum _CmdId {
	CmdNorth, CmdSouth, CmdEast, CmdWest, CmdUp, CmdDown,
	CmdEnd,
	CmdHelp,
	CmdInventory,
	CmdExamine,
	CmdExits,
	CmdTake,
	CmdDrop,
	CmdSwim,
	CmdWear,
	CmdDisrobe,
    CmdWait,
    CmdBreak,
    CmdPush,
    CmdLookAround,
    CmdDbg,

	Cmd_Nop
} CmdId;

typedef struct _Cmd {
	CmdId cmdId;
	char *words;
	void (*doIt)();
} Cmd;

typedef struct _Order {
	char * verb;
	char * word1;
	char * word2;

	Cmd  * cmd;
	Obj * obj1;
	Obj * obj2;
} Order;

extern Cmd cmds[];
extern Cmd * cmdNop;
extern void init_cmds();

#endif


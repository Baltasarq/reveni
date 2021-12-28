// Reveni (c) 2020 Baltasar MIT License <baltasarq@gmail.com>

/* Commands */

#ifndef _INCLUDE_CMDS_H
#define _INCLUDE_CMDS_H

#include "objs.h"

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
    CmdPull,
    CmdLookAround,
    CmdDbg,

	Cmd_Nop
} CmdId;

typedef enum _cmdLimits {
				LengthWord = 5,
				NumCmds = Cmd_Nop + 1 }
CmdLimits;

typedef struct _Cmd {
	CmdId cmdId;
	char *words;
	void (*doIt)();
} Cmd;

typedef struct _Order {
	char * verb;
	char * word1;
	char * word2;

	const Cmd  * cmd;
	const Obj * obj1;
	const Obj * obj2;
} Order;

/** The vector with all available commands. */
extern Cmd cmds[];

/** A pointer to the command "You cannot do that" */
extern const Cmd * cmdNop;

/** Prepares everything related to commands. */
extern void init_cmds();

#endif


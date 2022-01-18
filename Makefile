CC=zcc
CFLAGS=+zx -O3
OBJ=obj

all: reveni

reveni: reveni.c ctrl player locs objs cmds
	$(CC) $(CFLAGS) -create-app reveni.c $(OBJ)/ctrl.o  $(OBJ)/player.o  $(OBJ)/locs.o  $(OBJ)/objs.o  $(OBJ)/cmds.o -oreveni -pragma-define:CLIB_CONIO_NATIVE_COLOUR=1 -pragma-define:CRT_ENABLE_STDIO=0 -pragma-redirect:fputc_cons=fputc_cons_generic -pragma-define:CRT_ORG_CODE=24576

ctrl: ctrl.h ctrl.c
	$(CC) $(CFLAGS) -c ctrl.c -o $(OBJ)/ctrl.o

player: player.h player.c
	$(CC) $(CFLAGS) -c player.c -o $(OBJ)/player.o

locs: locs.h locs.c
	$(CC) $(CFLAGS) -c locs.c -o $(OBJ)/locs.o

objs: objs.h objs.c
	$(CC) $(CFLAGS) -c objs.c -o $(OBJ)/objs.o

cmds: cmds.h cmds.c
	$(CC) $(CFLAGS) -c cmds.c -o $(OBJ)/cmds.o

clean:
	$(RM) $(OBJ)/*.o
	$(RM) reveni
	$(RM) *.tap
	$(RM) *.cpc
	$(RM) *.dsk
	$(RM) *.bin
	$(RM) *.def
	$(RM) *.reloc

run:
	fuse reveni.tap &

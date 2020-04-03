CC=zcc
CFLAGS=+zx -O3 -SO3

all: reveni

reveni: reveni.c ctrl player locs objs cmds
	$(CC) $(CFLAGS) -create-app reveni.c ctrl.o player.o locs.o objs.o cmds.o -oreveni -lndos

ctrl: ctrl.h ctrl.c
	$(CC) $(CFLAGS) -c ctrl.c -octrl.o

player: player.h player.c
	$(CC) $(CFLAGS) -c player.c -oplayer.o

locs: locs.h locs.c
	$(CC) $(CFLAGS) -c locs.c -olocs.o

objs: objs.h objs.c
	$(CC) $(CFLAGS) -c objs.c -oobjs.o

cmds: cmds.h cmds.c
	$(CC) $(CFLAGS) -c cmds.c -ocmds.o

clean:
	$(RM) *.o
	$(RM) reveni
	$(RM) *.tap
	$(RM) *.cpc
	$(RM) *.dsk
	$(RM) *.bin
	$(RM) *.def
	$(RM) *.reloc

run:
	fuse reveni.tap &

CC=zcc
CFLAGS=+zx -O3
OBJ=obj
EXEC=reveni


.PHONY: all clean run


all: $(EXEC)

$(EXEC): reveni.c ctrl.o player.o locs.o objs.o cmds.o
	$(CC) $(CFLAGS) -create-app reveni.c $(OBJ)/ctrl.o  $(OBJ)/player.o  $(OBJ)/locs.o  $(OBJ)/objs.o  $(OBJ)/cmds.o -o$(EXEC) -pragma-define:CLIB_CONIO_NATIVE_COLOUR=1 -pragma-define:CRT_ENABLE_STDIO=0 -pragma-redirect:fputc_cons=fputc_cons_generic -pragma-define:CRT_ORG_CODE=26112

ctrl.o: ctrl.h ctrl.c
	$(CC) $(CFLAGS) -c ctrl.c -o $(OBJ)/$@

player.o: player.h player.c
	$(CC) $(CFLAGS) -c player.c -o $(OBJ)/$@

locs.o: locs.h locs.c
	$(CC) $(CFLAGS) -c locs.c -o $(OBJ)/$@

objs.o: objs.h objs.c
	$(CC) $(CFLAGS) -c objs.c -o $(OBJ)/$@

cmds.o: cmds.h cmds.c
	$(CC) $(CFLAGS) -c cmds.c -o $(OBJ)/$@

clean:
	$(RM) $(OBJ)/*.o
	$(RM) $(EXEC)
	$(RM) $(EXEC).tap
	$(RM) *.cpc
	$(RM) *.dsk
	$(RM) *.bin
	$(RM) *.def
	$(RM) *.reloc

run:
	fuse $(EXEC).tap &

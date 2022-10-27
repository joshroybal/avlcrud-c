CC = cl.exe
CFLAGS = /Za /O2
LFLAGS =
OBJ =  main.obj avlbst.obj
EXE = driver.exe
RM = del.exe

$(EXE): $(OBJ)
	$(CC) /Fe$@ $(OBJ) $(LFLAGS)

main.obj: main.c avlbst.h
	$(CC) /c main.c $(CFLAGS)

avlbst.obj: avlbst.c avlbst.h
	$(CC) /c avlbst.c $(CFLAGS)

.PHONY : clean
clean:
	$(RM) $(EXE) $(OBJ)

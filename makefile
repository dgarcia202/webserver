CC=g++
CFLAGS=-g -Wall -pedantic
SRC=main.cpp dynws.cpp socket.cpp logger.cpp
EXE=dynws.exe
ODIR=.\bin

all:
	$(CC) $(CFLAGS) $(SRC) -o $(ODIR)\$(EXE) -lws2_32

run:
	$(ODIR)\$(EXE)

clean:
	del /F /Q $(ODIR)\$(EXE)

CC=g++
CFLAGS=-g -Wall -pedantic
SRC=src/main.cpp src/dynws.cpp src/socket.cpp src/logger.cpp src/stringtools.cpp
EXE=dynws.exe
ODIR=.\bin

all:
	$(CC) $(CFLAGS) $(SRC) -o $(ODIR)\$(EXE) -lws2_32

run:
	$(ODIR)\$(EXE)

clean:
	del /F /Q $(ODIR)\$(EXE)

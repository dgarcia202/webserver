CC=@g++
CFLAGS=-g -Wall -pedantic
SRC=src/main.cpp src/dynws.cpp src/socket.cpp src/logger.cpp src/stringtools.cpp
EXE=dynws.exe
ODIR=./bin

all:
	@echo Building...
	@mkdir -p $(ODIR)
	$(CC) $(CFLAGS) $(SRC) -o $(ODIR)\$(EXE) -lws2_32

run:
	@echo running program...
	@$(ODIR)\$(EXE)

clean:
	@echo Cleaning...
	@rm -f $(ODIR)/$(EXE) &> /dev/null

.PHONY: clean
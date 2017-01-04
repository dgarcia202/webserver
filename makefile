CC=g++
CFLAGS=-g -Wall -pedantic

SRCDIR=src
ODIR=bin

MODULES=dynws socket logger stringtools
EXE=dynws.exe

OBJECTS=$(patsubst %,$(ODIR)/%.o,$(MODULES))

all: $(OBJECTS)
	@echo Building $(ODIR)\$(EXE)
	$(CC) $(CFLAGS) $(SRCDIR)/main.cpp $(OBJECTS) -o $(ODIR)\$(EXE) -lws2_32
	@echo Build complete!!!

$(OBJECTS): $(ODIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.h
	@echo Building $@
	@mkdir -p $(ODIR)
	$(CC) -c $(CFLAGS) $< -o $@

run:
	@echo Running program...
	@$(ODIR)\$(EXE)

clean:
	@echo Cleaning...
	@rm -rf $(ODIR) &> /dev/null

.PHONY: clean run
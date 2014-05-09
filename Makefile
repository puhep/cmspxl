#
#  Xin Shi <Xin.Shi@cern.ch>
#  2014.03.11 
#

BIN=./bin
SRC=./src

CC = g++
GCCFLAGS  = -Wall -g 

ROOTCFLAGS    = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS     = $(shell $(ROOTSYS)/bin/root-config --glibs)
GLIBS         = $(filter-out -lz, $(ROOTGLIBS))

DRAWMODFLAGS=$(GCCFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -lHistPainter 
DRAWIVFLAGS=$(GCCFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -lHistPainter 

PROG=drawMod, drawIV, log2tree 
LIST=$(addprefix $(BIN)/, $(PROG))


all: $(LIST)
	@echo "Build successful."

$(LIST): | $(BIN)


$(BIN): 
	mkdir -p $(BIN)


$(BIN)/drawMod: $(SRC)/drawMod.cc
	$(CC) $< $(DRAWMODFLAGS) -o $@

$(BIN)/drawIV: $(SRC)/drawIV.cc
	$(CC) $< $(DRAWIVFLAGS) -o $@

$(BIN)/log2tree: $(SRC)/log2tree.cc
	$(CC) $< $(DRAWIVFLAGS) -o $@

clean:
	rm -f $(BIN)/drawMod $(BIN)/drawIV $(BIN)/log2tree
	rm -rf $(BIN)/drawMod.dSYM $(BIN)/drawIV.dSYM $(BIN)log2tree.dSYM




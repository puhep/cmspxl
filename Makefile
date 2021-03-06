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

FLAGS=$(GCCFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -lHistPainter 

#drawVD
PROG=drawMod drawTemp drawIV drawHist hdiff hsup parseTbm findHistMax
LIST=$(addprefix $(BIN)/, $(PROG))


all: $(LIST)
	@echo "Build successful."

$(LIST): | $(BIN)


$(BIN): 
	mkdir -p $(BIN)

$(BIN)/drawMod: $(SRC)/drawMod.cc
	$(CC) $< $(FLAGS) -o $@

$(BIN)/drawIV: $(SRC)/drawIV.cc
	$(CC) $< $(FLAGS) -o $@

$(BIN)/drawTemp: $(SRC)/drawTemp.cc
	$(CC) $< $(FLAGS) -o $@

$(BIN)/drawHist: $(SRC)/drawHist.cc
	$(CC) $< $(FLAGS) -o $@

$(BIN)/log2tree: $(SRC)/log2tree.cc
	$(CC) $< $(FLAGS) -o $@

$(BIN)/hdiff: $(SRC)/hdiff.cc
	$(CC) $< $(FLAGS) -o $@

$(BIN)/hsup: $(SRC)/hsup.cc
	$(CC) $< $(FLAGS) -o $@

$(BIN)/parseTbm: $(SRC)/parseTbm.cc
	$(CC) $< $(GCCFLAGS) -o $@

$(BIN)/drawVD: $(SRC)/drawVD.cc
	$(CC) $< $(FLAGS) -o $@

$(BIN)/findHistMax: $(SRC)/findHistMax.cc
	$(CC) $< $(FLAGS) -o $@

$(BIN)/compBXplot: $(SRC)/compBXplot.cc
	$(CC) $< $(FLAGS) -o $@

clean:
	rm -f $(BIN)/drawMod $(BIN)/drawIV $(BIN)/drawTemp $(BIN)/drawHist $(BIN)/hdiff $(BIN)/hsup $(BIN)/parseTbm $(BIN)/drawVD $(BIN)/findHistMax
	rm -rf $(BIN)/*.dSYM 





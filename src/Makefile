#
#  Xin Shi <Xin.Shi@cern.ch>
#  2014.03.11 
#

CC = g++
GCCFLAGS  = -Wall -g 

ROOTCFLAGS    = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS     = $(shell $(ROOTSYS)/bin/root-config --glibs)
GLIBS         = $(filter-out -lz, $(ROOTGLIBS))

DRAWMODFLAGS=$(GCCFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -lHistPainter 


all: drawMod 
	@echo "Build successful."

drawMod: drawMod.cc
	$(CC) $< $(DRAWMODFLAGS) -o $@

clean:
	rm -rf *~  *.dSYM 
	rm -f drawMod



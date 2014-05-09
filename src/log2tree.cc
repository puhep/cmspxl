// Convert log to ROOT tree 
// Author: Xin Shi <Xin.Shi@cern.ch> 
// 2014.05.09
// 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <TROOT.h>
#include <TSystem.h>
#include <TString.h>
#include <TFile.h> 
#include <TTree.h>


using namespace std; 

void log2tree(TString inputFile, TString outFile) {
  ifstream in;
  in.open(inputFile); 

  TFile *f = new TFile(outFile, "RECREATE");
  TTree *tree = new TTree("tree", "data from log file");
  Float_t voltage;
  Float_t current;
  Int_t timestamp; 
  
  tree->Branch("voltage", &voltage, "voltage/F" ); 
  tree->Branch("current", &current, "current/F" ); 
  tree->Branch("timestamp", &timestamp, "timestamp/I" ); 
  
  string line;

  int nlines = 0; 
  while (getline(in, line)) {
    istringstream iss(line);
    if ( line.find("#") == 0 ) continue; 
    if (!(iss >> voltage >> current >> timestamp )) break; 
    if (!in.good()) break;
    // if (nlines < 5) printf("x=%8f, y=%8e, z=%d\n",x,y,z);
    tree->Fill(); 
    nlines ++; 
  }

  tree->Write(); 
  in.close();
  f->Close();
  cout << "Saved to " << outFile << endl; 
}


#ifndef __CINT__ 
#include <iostream>
#include <algorithm>

char* get_option(char ** begin, char ** end, const std::string & option){
  char ** itr = std::find(begin, end, option);
  if (itr != end && ++itr != end)  return *itr;
  return 0;
}

bool option_exists(char** begin, char** end, const std::string& option){
  return std::find(begin, end, option) != end;
}

void print_usage(){
  cout << "Usage: log2tree inputFile [test.root]\n" 
       << endl; 
}

int main(int argc, char** argv) {
  if (argc < 2) {
    print_usage() ;  
    return -1; 
  }
  
  TString inputFile(argv[1]);
  if ( inputFile ) {
    TString outFile = "test.root"; 
    if (argc >= 2) outFile = argv[2];
    log2tree(inputFile, outFile);
  } else {
    cerr << "Unable to open file: " << inputFile << endl; 
  }
  
  gSystem->Exit(0);
  return 0 ;
}

#endif



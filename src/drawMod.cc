// 
// Author: Xin Shi <Xin.Shi@cern.ch> 
// 2014.03.11
// 

#include <iostream>
// #include <string> 

#include <TSystem.h>
#include <TString.h>

using namespace std; 


void daq(TString inputFile) {
  cout << inputFile << endl; 
  
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
  cerr << "Usage: drawMod daq inputFile\n" << endl; 
}

int main(int argc, char** argv) {
  if (argc < 2) {
    print_usage() ;  
    return -1; 
  }
  
  if (strcmp(argv[1], "daq") == 0 ) {
    TString inputFile = argv[2]; 
    daq(inputFile); 
  }
  
  else {
    print_usage(); 
  }

  gSystem->Exit(0);

  return 0 ;
}

#endif



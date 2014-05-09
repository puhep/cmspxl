// 
// Author: Xin Shi <Xin.Shi@cern.ch> 
// 2014.05.08
// 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <TROOT.h>
#include <TSystem.h>
#include <TString.h>
#include <TH2D.h> 
#include <TFile.h> 
#include <TCanvas.h> 
#include <TStyle.h> 
#include "Riostream.h"



using namespace std; 


void drawIV(TString inputFile, TString outFile) {
  ifstream in;
  in.open(inputFile); 
  // if ( !inputFile.is_open()) return; 

  string line;
  float x, y;
  int z;

  int nlines = 0; 
  while (getline(in, line)) {
    istringstream iss(line);
    // size_t found = line.find("#"); 
    // cout << "found pos: " << found << endl; 
    // if (found == 0) continue; // cout << line << endl;
    if ( line.find("#") == 0 ) continue; 

    // cout << line << endl; 
    // int a, b;
    if (!(iss >> x >> y >> z )) { break; } // error
    // process pair (a,b)
    if (!in.good()) break;
    if (nlines < 5) printf("x=%8f, y=%8e, z=%d\n",x,y,z);
    nlines ++; 
  }
  
  
  /* 
  Float_t x,y; 
  Int_t z;
  Int_t nlines = 0;
  // TFile *f = new TFile(outFile, "RECREATE");
  // TH1F *h1 = new TH1F("h1","x distribution",100, 0, -500);

  string line; 
  // while (getline(inputFile, line))
  //   {
  //     // if ( strcmp(line[0], "#") != 0 ) 
  //     size_t found = line.find("#"); 
  //     cout << "found pos: " << found << endl; 

  //     // if ( strcmp(line[0], "#") != 0 ) 
  // 	// {
  // 	//   istringstream iss(line);
  // 	//   float num; // The number in the line
	  
  // 	//   //while the iss is a number 
  // 	//   while ((iss >> num))
  // 	//     {
  //       //     //look at the number
  // 	//     }
  // 	// }
  //   }
  
  while (1) {
    in >> line; 
    size_t found = line.find("#"); 
    // cout << "found pos: " << found << endl; 
    if (found == 0) continue; // cout << line << endl; 

    // in >> x >> y >> z;
    cout << nlines << ": " << line << endl; 
    
    // if (!in.good()) break;
    // if (nlines < 5) printf("x=%8f, y=%8f, z=%d\n",x,y,z);
    // h1->Fill(x);
    nlines++;
  }

  printf(" found %d points\n",nlines);

  */

  in.close();

  // f->Write();

  // TFile::Open(inputFile.Data());
  // double max_trig = 10; 

  // TH2D *h3 = new TH2D("h3", "", 416, 0., 416., 160, 0., 160.);

  // for (int chip = 0; chip < 16 ; chip++) { 
  //   TString hist = Form("PixelAlive/PixelAlive_C%d_V%d", chip, V); 
  //   cout << "\n --- ROC " << chip << " ---: " << endl; 
  //   addChip(hist, chip, h3, max_trig); 
  // }
  
  // TCanvas *c = new TCanvas("c", "PixelAlive module", 800, 200); 
  // h3->DrawCopy("colz");

  // gROOT->SetStyle("Plain");
  
  // gStyle->SetPalette(1);
  // gStyle->SetOptStat(0);
  // gStyle->SetTitle(0);

  // c->SaveAs(outFile);
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
  cout << "Usage: drawIV inputFile [test.root]\n" 
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
    if (argc >= 3) outFile = argv[3]; 
    drawIV(inputFile, outFile);
    
  } else {
    cerr << "Unable to open file: " << inputFile << endl; 
  }
  
  gSystem->Exit(0);
  return 0 ;
}

#endif



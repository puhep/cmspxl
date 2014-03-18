// 
// Author: Xin Shi <Xin.Shi@cern.ch> 
// 2014.03.11
// 

#include <iostream>
#include <TROOT.h>
#include <TSystem.h>
#include <TString.h>
#include <TH2D.h> 
#include <TFile.h> 
#include <TCanvas.h> 
#include <TStyle.h> 

using namespace std; 


void addChip(const TString hist, int chip, TH2D *h3) {
  
  TH2D *h2d;
  gDirectory->GetObject(hist, h2d); 
  
  if (!h2d) {
    cerr << "Not valid histogram!" << endl; 
    return ; 
  }

  for (int icol = 0; icol < 52; icol++) {
    for (int irow = 0; irow < 80; irow++)  {
      double value = h2d->GetBinContent(icol, irow); 
      if (chip < 8) {h3->SetBinContent(415-(chip*52+icol)+1, 159-irow+1, value);}
      if (chip > 7) {h3->SetBinContent((chip-8)*52+icol+1, irow+1, value);}
    }
  }
}


void daq(TString inputFile, TString outFile="test.root", int V=0) {
  TFile::Open(inputFile.Data());
  TH2D *h3 = new TH2D("h3", "", 416, 0., 416., 160, 0., 160.);
  
  for (int chip = 0; chip < 16 ; chip++) { 
    TString hist = Form("DAQ/Hits_C%d_V%d", chip, V); 
    addChip(hist, chip, h3); 
  }

  TCanvas *c = new TCanvas("c", "DAQ module", 800, 200); 
  h3->DrawCopy("colz");

  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);
  gStyle->SetTitle(0);
  c->SaveAs(outFile);
}


void pixelAlive(TString inputFile, TString outFile) {
  TFile::Open(inputFile.Data());
  TH2D *h3 = new TH2D("h3", "", 416, 0., 416., 160, 0., 160.);

  for (int chip = 0; chip < 16 ; chip++) { 
    TString hist = Form("PixelAlive/PixelAlive_C%d_V0", chip); 
    addChip(hist, chip, h3); 
  }
  
  TCanvas *c = new TCanvas("c", "PixelAlive module", 800, 200); 
  h3->DrawCopy("colz");

  gROOT->SetStyle("Plain");
  
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);
  gStyle->SetTitle(0);

  c->SaveAs(outFile);
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
  cerr << "Usage: drawMod DAQ        inputFile [test.pdf]\n" 
       << "               PixelAlive inputFile [test.pdf]\n" 
       << endl; 
}

int main(int argc, char** argv) {
  if (argc < 2) {
    print_usage() ;  
    return -1; 
  }
  
  if (strcmp(argv[1], "DAQ") == 0 ) {
    TString inputFile(argv[2]);
    if ( inputFile ) {
      TString outFile = "test.pdf"; 
      if (argc == 4) outFile = argv[3]; 
      daq(inputFile, outFile);
    } else {
      cerr << "Unable to open file: " << argv[2] << endl; 
    }
  }

  else if (strcmp(argv[1], "PixelAlive") == 0 ) {
    TString inputFile(argv[2]);
    if ( inputFile ) {
      TString outFile = "test.pdf"; 
      if (argc == 4) outFile = argv[3]; 
      pixelAlive(inputFile, outFile);
    } else {
      cerr << "Unable to open file: " << argv[2] << endl; 
    }
  }
  
  else {
    print_usage(); 
  }

  gSystem->Exit(0);

  return 0 ;
}

#endif



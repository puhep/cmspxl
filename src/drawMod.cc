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
      double value = h2d->GetBinContent(icol+1, irow+1); //(0,0) is underflow. 

      if (value > 10) value = 10; 

      int icol_mod, irow_mod; 
      if (chip < 8) {
	icol_mod = 415-(chip*52+icol);
	irow_mod = 159-irow; 
      }
      if (chip > 7) {
	icol_mod = (chip-8)*52+icol; 
	irow_mod = irow; 
      }

      double old_value = h3->GetBinContent(icol_mod+1, irow_mod+1); //(0,0) is underflow
      double new_value = old_value + value; 
      h3->SetBinContent(icol_mod+1, irow_mod+1, new_value); 
    }
  }
}


void daq(TString inputFile, TString outFile="test.root", int V=0) {
  TFile::Open(inputFile.Data());
  TH2D *h3 = new TH2D("h3", "", 416, 0., 416., 160, 0., 160.);
  
  for (int chip = 0; chip < 16 ; chip++) { 
    for (int ver=0; ver<V+1; ver++) {
      TString hist = Form("DAQ/Hits_C%d_V%d", chip, ver); 
      addChip(hist, chip, h3); 
    }
  }
  
  TCanvas *c = new TCanvas("c", "DAQ module", 800, 200); 
  h3->DrawCopy("colz");

  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);
  gStyle->SetTitle(0);
  c->SaveAs(outFile);
}


void pixelAlive(TString inputFile, TString outFile, int V=0) {
  TFile::Open(inputFile.Data());
  TH2D *h3 = new TH2D("h3", "", 416, 0., 416., 160, 0., 160.);

  for (int chip = 0; chip < 16 ; chip++) { 
    TString hist = Form("PixelAlive/PixelAlive_C%d_V%d", chip, V); 
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
      int V = 0; 
      if (argc >= 4) outFile = argv[3]; 
      if (argc >= 5) V = atoi(argv[4]); 
      daq(inputFile, outFile, V);
    } else {
      cerr << "Unable to open file: " << argv[2] << endl; 
    }
  }

  else if (strcmp(argv[1], "PixelAlive") == 0 ) {
    TString inputFile(argv[2]);
    if ( inputFile ) {
      TString outFile = "test.pdf"; 
      int V = 0; 
      if (argc == 4) outFile = argv[3]; 
      if (argc >= 5) V = atoi(argv[4]); 
      pixelAlive(inputFile, outFile, V);
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



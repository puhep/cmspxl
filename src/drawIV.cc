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
#include <Riostream.h>
#include <TTree.h>
#include <TGraph.h>


using namespace std; 

void drawIVlogs(){
  TString inputFile = "SCAB_001_iv_20140508.log";
  ifstream in;
  in.open(inputFile); 

  Float_t voltage;
  Float_t current;
  Int_t timestamp; 

  string line;
  int nlines = 0; 
  while (getline(in, line)) {
    istringstream iss(line);
    if ( line.find("#") == 0 ) continue; 
    if (!(iss >> voltage >> current >> timestamp )) break; 
    if (!in.good()) break;
    nlines ++; 
  }

  cout << "Read " << nlines << " lines." << endl;
  in.close();
  
}



void drawIV(TString inputFile, TString outFile) {

  TFile* treeFile = TFile::Open(inputFile); 

  if (!treeFile) {
    cerr << "Not able to open file: " << inputFile << endl;
    return ;
  }
    
  TTree *tree = NULL;
  gDirectory->GetObject("tree", tree);

  if (!tree){
    cerr << "No object name tree! " << endl;
    return ;
  }

  Float_t voltage;
  Float_t current;
  tree->SetBranchAddress("voltage", &voltage); 
  tree->SetBranchAddress("current", &current); 

  TGraph *gr = new TGraph();

  Long64_t nentries = tree->GetEntries();
  for (Long64_t i=0;i<nentries;i++) {
    tree->GetEntry(i);
    // cout << voltage << " " << current << endl;
    // gr->SetPoint(i, voltage, current); 
    gr->SetPoint(i, -voltage, -current); 
  }

  TCanvas *c = new TCanvas("c", "IV scan", 400, 400); 

  gr->GetXaxis()->SetTitle("Bias Voltage [V]");
  gr->GetYaxis()->SetTitle("Leakage Current [A]");

  // gr->SetMarkerColor(kRed);
  gr->SetMarkerStyle(20);
  gr->Draw();
  // gr->Draw("ACP");
  
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
  cout << "Usage: drawIV inputFile [test.pdf]\n"
       << "               logs input1 input2 ... \n"
       << endl; 
}

int main(int argc, char** argv) {
  if (argc < 2) {
    print_usage() ;  
    return -1; 
  }
  TString outFile = "test.pdf";

  if (strncmp (argv[1], "logs", 4) == 0) {
    drawIVlogs(); 
    return 0 ;
  }

  TString inputFile(argv[1]);
  if ( inputFile ) {

    if (argc >= 2) outFile = argv[2]; 
    drawIV(inputFile, outFile);
  } else {
    cerr << "Unable to open file: " << inputFile << endl; 
  }
  
  gSystem->Exit(0);
  return 0 ;
}

#endif



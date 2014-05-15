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
#include <TMultiGraph.h>
#include <TLegend.h>


using namespace std; 

TGraph * get_graph_from_log(TString inputFile) {
  ifstream in;
  in.open(inputFile); 

  Float_t voltage;
  Float_t current;
  Int_t timestamp; 

  vector <Double_t> voltages; 
  vector <Double_t> currents; 

  string line;

  int nlines = 0; 
  while (getline(in, line)) {
    istringstream iss(line);
    if ( line.find("#") == 0 ) continue; 
    if (!(iss >> voltage >> current >> timestamp )) break; 
    if (!in.good()) break;
    voltages.push_back(-voltage);
    currents.push_back(-current);
    nlines ++; 
  }

  cout << inputFile << " contains " << nlines << " lines." << endl;
  in.close();
  TGraph *gr = new TGraph(nlines, &voltages[0], &currents[0]);
  return gr; 
}


void drawIV(vector<TString> inputFiles){
  TString outFile = "test.pdf";

  TCanvas *c = new TCanvas("c", "IV scan", 400, 400);
  c->SetGrid();

  TMultiGraph *mg = new TMultiGraph();
  TLegend *leg = new TLegend(0.1, 0.74, 0.4, 0.9);
  leg->SetBorderSize(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetNColumns(1);
  leg->SetTextSize(0.035);
  leg->SetTextSizePixels(25);

  for (vector<int>:: size_type i = 0; i != inputFiles.size(); i++) {
    TGraph *gr = get_graph_from_log(inputFiles[i]); 
    gr->SetMarkerStyle(20+i);
    gr->SetMarkerSize(0.5);
    gr->SetMarkerColor(i+1);
    leg->AddEntry(gr, inputFiles[i], "p"); 
    mg->Add(gr); 
  }
  
  mg->Draw("ap"); 
  mg->GetXaxis()->SetTitle("Bias Voltage [V]");
  mg->GetYaxis()->SetTitle("Leakage Current [A]");
  leg->Draw(); 
  
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
  cout << "Usage: drawIV input1 input2 ... \n"
       << endl; 
}

int main(int argc, char** argv) {
  if (argc < 2) {
    print_usage() ;  
    return -1; 
  }
  
  vector<TString> inputFiles(argv+1, argv+argc);
  drawIV(inputFiles);
  
  gSystem->Exit(0);
  return 0 ;
}

#endif



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
#include <TApplication.h> 
#include <TMath.h> 

using namespace std; 

TGraph * get_graph_from_log(TString inputFile) {
  ifstream in;
  in.open(inputFile); 

  Float_t voltage;
  Float_t current;
  // Int_t timestamp; 

  vector <Double_t> voltages; 
  vector <Double_t> currents; 

  string line;

  int nlines = 0; 
  while (getline(in, line)) {
    istringstream iss(line);
    if ( line.find("#") == 0 ) continue; 
    // if (!(iss >> voltage >> current >> timestamp )) break; 
    if (!(iss >> voltage >> current )) break; 
    if (!in.good()) break;
    // voltages.push_back(fabs(voltage));
    // currents.push_back(fabs(current));
    voltages.push_back(-voltage);
    currents.push_back(-current);
    nlines ++; 
  }

  cout << inputFile << " contains " << nlines << " lines." << endl;
  in.close();
  TGraph *gr = new TGraph(nlines, &voltages[0], &currents[0]);
  return gr; 
}

TCanvas* drawIV(vector<TString> inputFiles){
  TCanvas *c = new TCanvas("c", "IV scan", 800, 800);
  c->SetGrid();

  TMultiGraph *mg = new TMultiGraph();
  TLegend *leg = new TLegend(0.2, 0.6, 0.5, 0.9);
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
    int color = i+1;
    if (color >= 5) color ++; // bypass the yellow  
    gr->SetMarkerColor(color);
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
  return c;
}


#ifndef __CINT__ 
#include <iostream>

int print_usage(){
  cout << "Usage: drawIV [-b] input1 input2 ... \n"
       << endl;
  return 0; 
}

int main(int argc, char** argv) {
  if (argc < 2) {
    print_usage() ;  
    return -1; 
  }

  bool doBatch(false);
  vector<TString> inputFiles(argv+1, argv+argc);
  TString outFile = "test.pdf";
  
  for (int i = 0; i < argc; i++){
    if (!strcmp(argv[i], "-h")) print_usage();
    if (!strcmp(argv[i], "-b")) {
      doBatch = true;
      inputFiles.erase(inputFiles.begin()+i-1);
    }
  }

  cout << "After size = " << inputFiles.size() << endl;
  for (vector<int>:: size_type i = 0; i != inputFiles.size(); i++) {
    cout << i << " : " << inputFiles[i] << endl; 
  }

  if (doBatch) { 
    cout << "Run in batch mode ... " << endl;
    TCanvas *c = drawIV(inputFiles);
    // c->SaveAs(outFile);
    delete c;
    gSystem->Exit(0);
  }
  
  TApplication theApp("App", 0, 0);
  theApp.SetReturnFromRun(true);
  drawIV(inputFiles);
  theApp.Run();
}

#endif



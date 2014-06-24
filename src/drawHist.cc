// 
// Author: Xin Shi <Xin.Shi@cern.ch> 
// 2014.06.18
// 

#include <iostream>
#include <limits>  
#include <TROOT.h>
#include <TSystem.h>
#include <TString.h>
#include <TH2D.h> 
#include <TFile.h> 
#include <TCanvas.h> 
#include <TStyle.h> 
#include <TApplication.h> 

using namespace std; 

TCanvas* drawHist(TString inputFile, TString histType, TString histName, 
		  TString drawOption, double vmax, int V=0){
  TCanvas *c = new TCanvas("c", "c", 800, 800);
  TFile *f = new TFile(inputFile.Data()); 

  TString h_file_name = Form("h_%s", inputFile.Data()); 
  TFile *fo = new TFile(h_file_name, "RECREATE");

  if (!strcmp(histType, "TH1D")) {
    TH1D *h = (TH1D*)f->Get(histName);
    if (!h) {
      cout << "Not able to find hist: " << histName << endl; 
      return NULL; 
    }
    if ( vmax != numeric_limits<double>::max())
      h->SetMaximum(vmax); 
    h->Draw(drawOption); 
    h->Write();
  }

  else if (!strcmp(histType, "TH2D")) {
    TH2D *h = (TH2D*)f->Get(histName);
    if (!h) {
      cout << "Not able to find hist: " << histName << endl; 
      return NULL; 
    }
    if ( vmax != numeric_limits<double>::max())
      h->SetMaximum(vmax); 
    if (drawOption == "") h->Draw("colz"); 
    else h->Draw(drawOption);
    h->Write();
  }
  
  else {
    cout << "Not supported type: " << histType << endl; 
  }
    
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);

  fo->Close();
  cout << "Save the hist as: "<< h_file_name << endl;  

  return c; 
}


void print_usage(){
  cout << "Usage see: man drawHist " << endl; 
}

int main(int argc, char** argv) {
  if (argc < 2) {
    print_usage() ;  
    return -1; 
  }

  bool doRunGui(true);
  TString histType; 
  TString inputFile;
  TString histName; 
  TString drawOption(""); 
  double vmax = numeric_limits<double>::max();
  
  for (int i = 0; i < argc; i++){
    if (!strcmp(argv[i],"-b")) {doRunGui = false; } 
    if (!strcmp(argv[i],"-i")) {inputFile = string(argv[++i]); }   
    if (!strcmp(argv[i],"-t")) {histType = string(argv[++i]); }
    if (!strcmp(argv[i],"-drawOption")) {
      drawOption = string(argv[++i]);
      cout << "Using drawOption = " << drawOption << endl;  
    }
    if (!strcmp(argv[i],"-h")) {
      histName = string(argv[++i]); 
      cout << "Hist name = " << histName << endl; 
    }
    if (!strcmp(argv[i],"-vmax")) {
      vmax = atof(argv[++i]); 
      cout << "Using vmax = " << vmax << endl; 
    }
  }

  if (doRunGui) { 
    TApplication theApp("App", 0, 0);
    theApp.SetReturnFromRun(true);
    drawHist(inputFile, histType, histName, drawOption, vmax);  
    theApp.Run();
  } 
  
  else {
    TCanvas *c = drawHist(inputFile, histType, histName, drawOption, 
			  vmax);  
    TString outFile = inputFile;
    outFile.ReplaceAll("root",4,"pdf",3);  
    c->SaveAs(outFile);
    outFile.ReplaceAll("pdf",3,"png",3);  
    c->SaveAs(outFile);
    delete c;
    gSystem->Exit(0);
  }

}




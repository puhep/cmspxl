//
// Superimpose histograms 
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


TCanvas* hsup(vector<TString> inputFiles){
  TCanvas *c = new TCanvas("c", "c", 800, 800);

  // TFile *f = NULL; 
  TString hname = "dist_sig_scurveVcal_Vcal_C0_V0"; 

  for (vector<int>:: size_type i = 0; i != inputFiles.size(); i++) {
    TFile *f = new TFile(inputFiles[i]); 
    // f->Open(inputFiles[i]);
    TH1D *h = (TH1D*)f->Get(hname);
    h->SetDirectory(0); // "detach" the histogram from the file
    delete f; 
    int color = i+1;

    cout << "File name = " << inputFiles[i] << endl; 
    // h->SetLineColor(color); 
    if (i==0) h->Draw(); 
    else h->Draw("same"); 
  }

  c->Update();

  // TH2D *hsup = new TH2D("hsup", "", 416, 0., 416., 160, 0., 160.);
  // double v1, v2, sup; 
  
  // hsup->SetMaximum(1.);
  // hsup->SetMinimum(-1.);
  // hsup->Draw("colz");
  // gROOT->SetStyle("Plain");
  // gStyle->SetPalette(55);
  // gStyle->SetOptStat(0);
  // gStyle->SetTitle(0);

  return c; 
}



#ifndef __CINT__ 
#include <iostream>

void print_usage(){
  cout << "Usage: hsup h1.root h2.root ... \n" << endl; 
}


int main(int argc, char** argv) {
  if (argc < 2) {
    print_usage() ;  
    return -1; 
  }

  // bool doBatch(false);
  vector<TString> inputFiles(argv+1, argv+argc);
  TString outFile = "sup.pdf";
  
  // if (doBatch) { 
  //   cout << "Run in batch mode ... " << endl;
  //   TCanvas *c = hsup(inputFile1, inputFile2);
  //   c->SaveAs(outFile);
  //   delete c;
  //   gSystem->Exit(0);
  // }
  
  TApplication theApp("App", 0, 0);
  theApp.SetReturnFromRun(true);

  hsup(inputFiles);  
  theApp.Run();

}

#endif



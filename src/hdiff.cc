//
// Plot difference for histograms 
// Author: Xin Shi <Xin.Shi@cern.ch> 
// 2014.06.03
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


TCanvas* hdiff(TString inputFile1, TString inputFile2){

  TFile *f1 = NULL;
  TFile *f2 = NULL;
  
  TCanvas *c = new TCanvas("c", "c", 800, 200);
  f1->Open(inputFile1.Data());
  f2->Open(inputFile2.Data());

  TH2D *h2d1, *h2d2; 
  TString hist = "h3";

  gDirectory->GetObject(hist, h2d1);
  if (!h2d1) {
    cerr << "Not able to find histogram => " << hist << "in " <<
      inputFile1 << endl; 
    return NULL; 
  }

  gDirectory->GetObject(hist, h2d2);
  if (!h2d2) {
    cerr << "Not able to find histogram => " << hist << "in " <<
      inputFile2 << endl; 
    return NULL; 
  }

  return c; 
}



#ifndef __CINT__ 
#include <iostream>

void print_usage(){
  cerr << "Usage: hdiff h1.root h2.root \n" 
       << endl; 
}

int main(int argc, char** argv) {
  if (argc < 2) {
    print_usage() ;  
    return -1; 
  }

  bool doBatch(false);
  TString inputFile1(argv[1]); 
  TString inputFile2(argv[2]);
  TString outFile = "diff.pdf";

  
  if (doBatch) { 
    cout << "Run in batch mode ... " << endl;
    TCanvas *c = hdiff(inputFile1, inputFile2);
    c->SaveAs(outFile);
    delete c;
    gSystem->Exit(0);
  }
  
  TApplication theApp("App", 0, 0);
  theApp.SetReturnFromRun(true);

  hdiff(inputFile1, inputFile2);  
  theApp.Run();

}

#endif



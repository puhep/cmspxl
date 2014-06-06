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
  TCanvas *c = new TCanvas("c", "c", 800, 200);
  TString hist = "h3";

  TFile *f1 = new TFile(inputFile1.Data()); 
  TH2D *h2d1 = (TH2D*)f1->Get(hist); 
  if (!h2d1) {
    cerr << "Not able to find histogram => " << hist << "in " <<
      inputFile1 << endl; 
    return NULL; 
  }

  TFile *f2 = new TFile(inputFile2.Data()); 
  TH2D *h2d2 = (TH2D*)f2->Get(hist); 
  if (!h2d2) {
    cerr << "Not able to find histogram => " << hist << "in " <<
      inputFile2 << endl; 
    return NULL; 
  }

  int nbinx = h2d1->GetXaxis()->GetNbins();
  int nbiny = h2d1->GetYaxis()->GetNbins();

  TH2D *hdiff = new TH2D("hdiff", "", 416, 0., 416., 160, 0., 160.);
  double v1, v2, diff; 
  
  for (int ix = 1; ix <= nbinx; ix++) {
    for (int iy = 1; iy <= nbiny; iy++)  {
       v1 = h2d1->GetBinContent(ix, iy);
       v2 = h2d2->GetBinContent(ix, iy);
       
       if ( v1 == 0 || v2 == 0) diff = 0;
       else diff = (v1-v2)/v1;
       // if ( diff != 0 )  cout << "diff = " << diff << endl;
       hdiff->SetBinContent(ix, iy, diff); 
    }
  }

  hdiff->SetMaximum(1.);
  hdiff->SetMinimum(-1.);
  hdiff->Draw("colz");
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(55);
  gStyle->SetOptStat(0);
  gStyle->SetTitle(0);

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



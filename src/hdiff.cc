//
// Plot difference for histograms 
// Author: Xin Shi <Xin.Shi@cern.ch> 
// 2014.06.03
// 

#include <iostream>
#include <limits>
#include <stdlib.h> /* atof */ 
#include <math.h>       /* fabs */
#include <TROOT.h>
#include <TSystem.h>
#include <TString.h>
#include <TH2D.h> 
#include <TFile.h> 
#include <TCanvas.h> 
#include <TStyle.h> 
#include <TApplication.h> 

using namespace std; 


TCanvas* hdiff(TString inputFile1, TString inputFile2,
	       const double vmin, const double vmax){
  TCanvas *c = new TCanvas("c", "c", 800, 200);
  TString hist = "h3";

  TFile *f1 = new TFile(inputFile1.Data()); 
  TH2D *h2d1 = (TH2D*)f1->Get(hist); 
  if (!h2d1) {
    cerr << "Not able to find histogram => " << hist << " in " <<
      inputFile1 << endl; 
    return NULL; 
  }

  TFile *f2 = new TFile(inputFile2.Data()); 
  TH2D *h2d2 = (TH2D*)f2->Get(hist); 
  if (!h2d2) {
    cerr << "Not able to find histogram => " << hist << " in " <<
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
       diff = v2-v1; 
       // hdiff->SetBinContent(ix, iy, diff);
       
       // if ( v1 == 0 || v2 == 0) diff = 0;
       // else diff = (v1-v2)/v1;
       // if ( fabs(diff) > 1 )
       // 	 printf("v1: %.2f, v2: %.2f, diff: %.2f \n", v1, v2, diff);

       if (diff > vmin && diff < vmax )
	 hdiff->SetBinContent(ix, iy, diff);
       // else printf("Out of range: %.2f", diff);  
    }
  }


  if (vmin != -std::numeric_limits<double>::max())
    hdiff->SetMinimum(vmin);

  if (vmax != std::numeric_limits<double>::max())
    hdiff->SetMaximum(vmax);  

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
  cerr << "Usage: hdiff h1.root h2.root [-vmin value] \n" 
       << endl; 
}

int main(int argc, char** argv) {
  if (argc < 2) {
    print_usage() ;  
    return -1; 
  }

  // bool doBatch(false);
  TString inputFile1(argv[1]); 
  TString inputFile2(argv[2]);
  TString outFile = "diff.pdf";
  // double vmin = std::numeric_limits<double>::min();
  double vmin = -std::numeric_limits<double>::max();
  double vmax = std::numeric_limits<double>::max();
  
  for (int i = 0; i < argc; i++){
    if (!strcmp(argv[i], "-h")) print_usage();
    if (!strcmp(argv[i],"-vmin")) {
      vmin = atof(argv[++i]); 
      std::cout << "Using vmin = " << vmin << std::endl; 
    }
     if (!strcmp(argv[i],"-vmax")) {
      vmax = atof(argv[++i]); 
      std::cout << "Using vmax = " << vmax << std::endl; 
    }
  }

  // if (doBatch) { 
  //   cout << "Run in batch mode ... " << endl;
  //   TCanvas *c = hdiff(inputFile1, inputFile2);
  //   c->SaveAs(outFile);
  //   delete c;
  //   gSystem->Exit(0);
  // }
  
  TApplication theApp("App", 0, 0);
  theApp.SetReturnFromRun(true);

  hdiff(inputFile1, inputFile2, vmin, vmax);  
  theApp.Run();

}

#endif



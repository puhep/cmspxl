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

void get_roc_info(int x, int y,
		  int& roc, int& col, int& row) {
  int roc_x, roc_y;

  roc_x = x/52;
  roc_y = y/80;
    
  if (roc_y==0) {  // ROC start from 8 to 15 
    roc = 8+roc_x;
  }
  if (roc_y==1) {   // ROC start from 0 to 7
    roc = 7-roc_x;
  }
  col = x - roc_x*52;
  row = y - roc_y*80;
}


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
  // int roc_x, roc_y, roc_no, pix_x, pix_y;
  int ndiff_total(0);

  for (int ix = 1; ix <= nbinx; ix++) {
    for (int iy = 1; iy <= nbiny; iy++)  {
       v1 = h2d1->GetBinContent(ix, iy);
       v2 = h2d2->GetBinContent(ix, iy);
       diff = v2-v1;

       if (diff > vmin && diff < vmax ) {
	 hdiff->SetBinContent(ix, iy, diff);
	 ndiff_total += 1;

	 int roc, col, row;
	 get_roc_info(ix, iy, roc, col, row);  

	 printf("  ROC %i (c%i, r%i): v1=%f, v2=%f, diff=%f \n",
		roc, col, row, v1, v2, diff); 
       }
       // else printf("Out of range: %.2f", diff);  
    }
  }

  printf("Total diff = %i\n", ndiff_total); 

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



// 
// Author: Xin Shi <Xin.Shi@cern.ch> 
// 2014.03.11
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

void addChip(const TString hist, const int chip, TH2D *h3,
	     int& n_range, int& n_total, 
	     const bool checkrange=false, 
	     const double vmin=numeric_limits<double>::min(),
	     const double vmax=numeric_limits<double>::max() ) {
  
  TH2D *h2d;
  gDirectory->GetObject(hist, h2d); 
  
  if (!h2d) {
    cerr << "Chip "<< chip << ": Not valid histogram => " << hist << endl; 
    return ; 
  }

  n_total = 0; 
  n_range = 0;  
  
  for (int icol = 0; icol < 52; icol++) {
    for (int irow = 0; irow < 80; irow++)  {
      n_total += 1; 

      double value = h2d->GetBinContent(icol+1, irow+1); //(0,0) is underflow. 

      if (checkrange && value >= vmin && value <= vmax) 
	n_range += 1; 
      
      int icol_mod, irow_mod; 
      if (chip < 8) {
	icol_mod = 415-(chip*52+icol);
	irow_mod = 159-irow; 
      }
      
      if (chip > 7) {
	icol_mod = (chip-8)*52+icol; 
	irow_mod = irow; 
      }

      double old_value = h3->GetBinContent(icol_mod+1, irow_mod+1);
      //(0,0) is underflow
      double new_value = old_value + value; 
      h3->SetBinContent(icol_mod+1, irow_mod+1, new_value); 
    }
  }

  if (checkrange)
    printf("ROC%2d: %d / %d = %2.2f%%. \n", chip,
	   n_range, n_total, 100.*n_range/n_total); 
}


TCanvas* drawMod(TString label, TString inputFile, int V=0){

  TCanvas *c = new TCanvas("c", "c", 800, 200);
  TFile::Open(inputFile.Data());

  bool checkrange = false;
  double vmin = numeric_limits<double>::min(); 
  double vmax = numeric_limits<double>::max();
  int n_range = 0;
  int n_total = 0; 
  
  if (!strcmp(label, "BumpBonding") ){
     checkrange = true;
     vmin = 0.5;
     vmax = 500;
     printf("Number of good bumpbonding pixels:\n");
  }

  TString hist(label); 
  TH2D *h3 = new TH2D("h3", "", 416, 0., 416., 160, 0., 160.);

  for (int chip = 0; chip < 16 ; chip++) {

    if (!strcmp(label, "BumpBonding") ){
      // if (chip < 10)  hist = Form("BumpBonding/BB- %d", chip);
      // else hist = Form("BumpBonding/BB-%d", chip);

      if (chip == 0 ) hist = Form("BumpBonding/thr_calSMap_VthrComp_C%d_V%d", chip, V);
      else hist = Form("BumpBonding/thr_calSMap_vthrcomp_C%d_V%d", chip, V);
     }

    else if (!strcmp(label, "PixelAlive")) { 
      hist = Form("PixelAlive/PixelAlive_C%d_V%d", chip, V);
    }

    else if (!strcmp(label, "DAQ")) { 
      hist = Form("DAQ/Hits_C%d_V%d", chip, V); 
    }

    else {
      cerr << "No such hist name: " << hist << endl;
      break; 
    }

    int n_r, n_t; 
    addChip(hist, chip, h3, n_r, n_t, checkrange, vmin, vmax); 
    // addChip(hist, chip, h3);
    n_range += n_r;
    n_total += n_t; 
  }


  if (!strcmp(label, "BumpBonding") ){
    printf("Total good bump bonding pixels %d / %d = %.2f%% \n",
	   n_range, n_total, 100.*n_range/n_total); 
  }



  h3->Draw("colz");
  // h3->Draw("surf2");

  gROOT->SetStyle("Plain");
  // gStyle->SetPalette(1);
  gStyle->SetPalette(55); // rain bow 
  gStyle->SetOptStat(0);
  gStyle->SetTitle(0);

  TFile *f = new TFile("h_mod.root", "RECREATE");
  h3->Write();
  f->Close();
  cout << "Save the hist as: h_mod.root" << endl;  

  return c; 
}



#ifndef __CINT__ 
#include <iostream>

void print_usage(){
  cerr << "Usage: drawMod [-b] PixelAlive | BumpBonding | DAQ inputFile \n" 
       << endl; 
}

int main(int argc, char** argv) {
  if (argc < 2) {
    print_usage() ;  
    return -1; 
  }

  bool doBatch(false);
  TString label(argv[1]); 
  TString inputFile(argv[2]);
  TString outFile = "test.pdf";
  // int V = 0;
  
  for (int i = 0; i < argc; i++){
    if (!strcmp(argv[i], "-h")) print_usage();
    if (!strcmp(argv[i], "-b")) {
      doBatch = true;
      label = argv[2]; 
      inputFile = argv[3]; 
    }
  }

  if (doBatch) { 
    cout << "Run in batch mode ... " << endl;
    TCanvas *c = drawMod(label, inputFile);
    c->SaveAs(outFile);
    delete c;
    gSystem->Exit(0);
  }
  
  TApplication theApp("App", 0, 0);
  theApp.SetReturnFromRun(true);

  drawMod(label, inputFile);  
  theApp.Run();

}

#endif



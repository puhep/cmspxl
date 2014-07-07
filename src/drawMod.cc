// 
// Author: Xin Shi <Xin.Shi@cern.ch> 
// 2014.03.11
// 


#include <iostream>
#include <string> 
#include <limits>  
#include <TROOT.h>
#include <TSystem.h>
#include <TString.h>
#include <TH2D.h> 
#include <TFile.h> 
#include <TCanvas.h> 
#include <TStyle.h> 
#include <TApplication.h> 

bool addChip(const TString hist, const int chip, TH2D *h3,
	     int& n_range, int& n_total, 
	     const bool checkrange=false, 
	     const double vmin=std::numeric_limits<double>::min(),
	     const double vmax=std::numeric_limits<double>::max() ) {
  
  TH2D *h2d;
  gDirectory->GetObject(hist, h2d); 
  
  if (!h2d) {
    std::cerr << "Chip "<< chip << ": Not valid histogram => " << hist << std::endl; 
    return false; 
  }

  n_total = 0; 
  n_range = 0;  
  
  for (int icol = 0; icol < 52; icol++) {
    for (int irow = 0; irow < 80; irow++)  {
      n_total += 1; 

      double value = h2d->GetBinContent(icol+1, irow+1); //(0,0) is underflow. 

      if (checkrange && value >= vmin && value <= vmax) 
	n_range += 1; 
      
      if ( value < std::numeric_limits<double>::max() && value > vmax)
	value = vmax; 

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

  return true; 
}


TCanvas* drawModPretest(TString label, TString inputFile,
			TString drawOption, int V=0){
  TCanvas *c = new TCanvas("c", "c", 800, 800);
  TFile *f = new TFile(inputFile.Data()); 

  TH1D *h1 = (TH1D*)f->Get("Pretest/programROC_V0"); 
  TH1D *h2 = (TH1D*)f->Get("Pretest/VanaSettings_V0"); 
  TH1D *h3 = (TH1D*)f->Get("Pretest/Iana_V0"); 
  TH1D *h4 = (TH1D*)f->Get("Pretest/pretestCalDel_V0"); 
    
  c->Divide(4, 5); 
  c->cd(1); 
  h1->Draw();

  c->cd(2); 
  h2->Draw();
  c->cd(3); 
  h3->Draw();
  c->cd(4); 
  h4->Draw();

  TString common = "Pretest/pretestVthrCompCalDel_c11_r20"; 
  for (int chip=0; chip<16; chip++) {
    c->cd(5+chip); 
    TH2D *h5 = (TH2D*)f->Get(Form("%s_C%d_V0", common.Data(), chip)); 
    h5->Draw("colz"); 
  }

  gROOT->SetStyle("Plain");
  gStyle->SetPalette(55); // rain bow 
  gStyle->SetOptStat(0);
  
  return c; 
  
}


TCanvas* drawMod(TString label, TString inputFile,
		 TString drawOption, double vmax, int V=0){
 
  if (!strcmp(label, "pretest") ) 
    return drawModPretest(label, inputFile, drawOption);


  TCanvas *c = new TCanvas("c", "c", 800, 200);
  TFile::Open(inputFile.Data());

  bool checkrange = false;
  double vmin = std::numeric_limits<double>::min(); 
  // double vmax = std::numeric_limits<double>::max();
  int n_range = 0;
  int n_total = 0; 
  
  if (!strcmp(label, "bumpbonding") ){
     checkrange = true;
     vmin = 0.5;
     vmax = 500;
     printf("Number of good bumpbonding pixels:\n");
  }

  TString hist(label); 
  TH2D *h3 = new TH2D("h3", "", 416, 0., 416., 160, 0., 160.);
  TH2D *h2d;

  for (int chip = 0; chip < 16 ; chip++) {

    if (!strcmp(label, "bumpbonding") ){
      // if (chip < 10)  hist = Form("BumpBonding/BB- %d", chip);
      // else hist = Form("BumpBonding/BB-%d", chip);
      hist = Form("BumpBonding/thr_calSMap_VthrComp_C%d_V%d", chip, V);
      gDirectory->GetObject(hist, h2d);
      if (!h2d)
	hist = Form("BumpBonding/thr_calSMap_vthrcomp_C%d_V%d", chip, V);
    }

    else if (!strcmp(label, "pixelalive")) { 
      hist = Form("PixelAlive/PixelAlive_C%d_V%d", chip, V);
    }

    else if (!strcmp(label, "daq")) { 
      hist = Form("DAQ/Hits_C%d_V%d", chip, V); 
    }

    else if (!strcmp(label, "scurves")) { 
      hist = Form("Scurves/sig_scurveVcal_vcal_C%d_V%d", chip, V);
      gDirectory->GetObject(hist, h2d);
      if (!h2d)
	hist = Form("Scurves/sig_scurveVcal_Vcal_C%d_V%d", chip, V);
    }

    else {
      std::cerr << "No such hist name: " << hist << std::endl;
      break; 
    }

    int n_r, n_t; 
    addChip(hist, chip, h3, n_r, n_t, checkrange, vmin, vmax); 
    // addChip(hist, chip, h3);
    n_range += n_r;
    n_total += n_t; 
  }


  if (!strcmp(label, "bumpbonding") ){
    printf("Total good bump bonding pixels %d / %d = %.2f%% \n",
	   n_range, n_total, 100.*n_range/n_total); 
  }



  h3->Draw(drawOption);

  gROOT->SetStyle("Plain");
  gStyle->SetPalette(55); // rain bow 
  gStyle->SetOptStat(0);
  gStyle->SetTitle(0);

  TString h_mod_name = Form("h_mod_%s", inputFile.Data()); 
  TFile *f = new TFile(h_mod_name, "RECREATE");
  h3->Write();
  f->Close();
  std::cout << "Save the hist as: "<< h_mod_name << std::endl;  


  return c; 
}



void print_usage(){
  std::cout << "Usage see: man drawMod " << std::endl; 
}

int main(int argc, char** argv) {
  if (argc < 2) {
    print_usage() ;  
    return -1; 
  }

  bool doRunGui(false);
  TString testLabel; 
  TString inputFile; 
  TString drawOption("colz"); 
  double vmax = std::numeric_limits<double>::max();
  // int V = 0;

  for (int i = 0; i < argc; i++){
    if (!strcmp(argv[i], "-h")) print_usage();
    if (!strcmp(argv[i],"-g")) {doRunGui = true; } 
    if (!strcmp(argv[i],"-i")) {inputFile = std::string(argv[++i]); }   
    if (!strcmp(argv[i],"-t")) {testLabel = std::string(argv[++i]); }
    if (!strcmp(argv[i],"-draw")) {
      drawOption = std::string(argv[++i]);
      std::cout << "Using drawOption = " << drawOption << std::endl;  
    }
    if (!strcmp(argv[i],"-vmax")) {
      vmax = atof(argv[++i]); 
      std::cout << "Using vmax = " << vmax << std::endl; 
    }
  }

  if (doRunGui) { 
    TApplication theApp("App", 0, 0);
    theApp.SetReturnFromRun(true);
    drawMod(testLabel, inputFile, drawOption, vmax);  
    theApp.Run();
  } 
  
  else {
    TCanvas *c = drawMod(testLabel, inputFile, drawOption, vmax);  
    TString outFile = inputFile;
    outFile.ReplaceAll("root",4,"pdf",3);  
    c->SaveAs(outFile);
    outFile.ReplaceAll("pdf",3,"png",3);  
    c->SaveAs(outFile);
    delete c;
    gSystem->Exit(0);
  }

}



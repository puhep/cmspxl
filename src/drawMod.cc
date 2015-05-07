// 
// Author: Xin Shi <Xin.Shi@cern.ch> 
// 2014.03.11
// 


#include <iostream>
#include <string> 
#include <limits> 
#include <stdlib.h> /* atof */ 
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
	     const double vmin=-std::numeric_limits<double>::max(),
	     const double vmax=std::numeric_limits<double>::max(),
	     bool printpix=false) {
  
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

      //Print pixel values to stdout if -p option is active
      if (printpix && value >= vmin && value <= vmax) {
	printf("  ROC %i (c%i, r%i): %f \n", chip, icol+1, irow+1, value);
      }

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
    printf("ROC%2d: %d / %d = %2.2f%%. (%d)\n", chip,
	   n_range, n_total, 100.*n_range/n_total, (n_total-n_range));


  if (vmin != -std::numeric_limits<double>::max())
    h3->SetMinimum(vmin);

  if (vmax != std::numeric_limits<double>::max())
    h3->SetMaximum(vmax);  
    
  return true; 
}


TCanvas* drawModPretest(TString label, TString inputFile,
			TString drawOption, int col, int row, int V=0){
  TCanvas *c = new TCanvas("c", "c", 800, 800);
  TFile *f = new TFile(inputFile.Data()); 

  TH1D *h1 = (TH1D*)f->Get("Pretest/programROC_V0"); 
  TH1D *h2 = (TH1D*)f->Get("Pretest/VanaSettings_V0"); 
  TH1D *h3 = (TH1D*)f->Get("Pretest/Iana_V0"); 
  TH1D *h4 = (TH1D*)f->Get("Pretest/pretestCalDel_V0"); 
    
  c->Divide(4, 5); 
  c->cd(1); 
  if (h1) h1->Draw();
  c->cd(2); 
  if (h2) h2->Draw();
  c->cd(3); 
  if (h3) h3->Draw();
  c->cd(4); 
  if (h4) h4->Draw();

  // TString common = "Pretest/pretestVthrCompCalDel_c12_r22"; 
  // TString common = "Pretest/pretestVthrCompCalDel_c11_r20"; 
  TString common = Form("Pretest/pretestVthrCompCalDel_c%d_r%d", col, row); ; 
  for (int chip=0; chip<16; chip++) {
    c->cd(5+chip); 
    TH2D *h5 = (TH2D*)f->Get(Form("%s_C%d_V0", common.Data(), chip)); 
    if (h5) h5->Draw("colz"); 
    else printf("Not able to find %s\n",  common.Data());
  }

  gROOT->SetStyle("Plain");
  gStyle->SetPalette(55); // rain bow 
  gStyle->SetOptStat(0);
  
  return c; 
  
}


TCanvas* drawMod(TString label, TString inputFile, int roc, 
		 TString drawOption, double vmin, double vmax, bool printpix, 
		 int col, int row, int V=0){
 
  if (!strcmp(label, "pretest") ) 
    return drawModPretest(label, inputFile, drawOption, col, row);

  TCanvas *c = new TCanvas("c", "c", 800, 200);
  TFile::Open(inputFile.Data());

  bool checkrange = false;
  // double vmin = std::numeric_limits<double>::min(); 
  // double vmax = std::numeric_limits<double>::max();
  int n_range = 0;
  int n_total = 0; 
  
  if (!strcmp(label, "alive") ){
     checkrange = true;
     if (vmin == -std::numeric_limits<double>::max() )
       vmin = 9.; 
     if (vmax == std::numeric_limits<double>::max() )
       vmax = 10.; 

     printf("Number of alive pixels: (thr vmin %.1f vmax %.1f) \n", vmin, vmax);
  }

  if (!strcmp(label, "bb") ){
     checkrange = true;
     if (vmin == -std::numeric_limits<double>::max() )
       vmin = 20.; 
     if (vmax == std::numeric_limits<double>::max() )
       vmax = 80.; 

     printf("Number of good bumpbonding pixels: (thr vmin %.1f vmax %.1f) \n", vmin, vmax);
  }

  TString hist(label); 
  TH2D *h3 = new TH2D("h3", "", 416, 0., 416., 160, 0., 160.);
  TH2D *h2d;

  for (int chip = 0; chip < 16 ; chip++) {

    // only plot one roc case 
    if ( roc != 16 && chip != roc) continue;

    if (!strcmp(label, "bb") ){
      // if (chip < 10)  hist = Form("BumpBonding/BB- %d", chip);
      // else hist = Form("BumpBonding/BB-%d", chip);
      // need to extract the separation cut from the dist file
      //bb_cut = Form("BumbBonding/dist_thr_calSmap_VthrComp_C%d_V%d", chip, V);
      // replicate fitting procedure done in pXar?
      hist = Form("BumpBonding/thr_calSMap_VthrComp_C%d_V%d", chip, V);
      gDirectory->GetObject(hist, h2d);
      if (!h2d)
	hist = Form("BumpBonding/thr_calSMap_vthrcomp_C%d_V%d", chip, V);
    }

    else if (!strcmp(label, "alive")) { 
      hist = Form("PixelAlive/PixelAlive_C%d_V%d", chip, V);
    }

    else if (!strcmp(label, "daq")) { 
      hist = Form("DAQ/hits_C%d_V%d", chip, V); 
    }

    else if (!strcmp(label, "scurves")) { 
      hist = Form("Scurves/sig_scurveVcal_vcal_C%d_V%d", chip, V);
      gDirectory->GetObject(hist, h2d);
      if (!h2d)
	hist = Form("Scurves/sig_scurveVcal_Vcal_C%d_V%d", chip, V);
    }

    else if (!strcmp(label, "trim")) { 
      hist = Form("Trim/thr_TrimThrFinal_vcal_C%d_V%d", chip, V);
      gDirectory->GetObject(hist, h2d);
    }

    else {
      std::cerr << "No such hist name: " << hist << std::endl;
      break; 
    }

    int n_r, n_t; 
    addChip(hist, chip, h3, n_r, n_t, checkrange, vmin, vmax, printpix); 
    // addChip(hist, chip, h3);
    n_range += n_r;
    n_total += n_t;
    
  }

  if (!strcmp(label, "alive") ){
    printf("Total alive pixels %d / %d = %.2f%% (%d)\n",
	   n_range, n_total, 100.*n_range/n_total, (n_total-n_range)); 
  }


  if (!strcmp(label, "bb") ){
    printf("Total good bump bonding pixels %d / %d = %.2f%% (%d)\n",
	   n_range, n_total, 100.*n_range/n_total, (n_total-n_range)); 
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
  printf("NAME\n\tdrawMod - draw Module plots\n");
  printf("\nSYNOPSIS\n\tdrawMod [-t testname ] [-i input-file] [-g] [-r roc] [-opt draw-option] [-v] [-vmin min-value] [-vmax max-value] [-col column] [-row row]\n");
  printf("\nOPTIONS\n");
  printf("\t%-5s  %-40s\n", "-i", "Input file");
  printf("\n\t%-5s  %-40s\n", "-g", "Run GUI");
  printf("\n\t%-5s  %-40s\n", "-r", "ROC number [0, ... , 15]");
  printf("\n\t%-5s  %-40s\n", "-t", "test name [pretest, alive, bb, trim, daq]");
  printf("\n\t%-5s  %-40s\n", "-v", "version number for output file");
  printf("\n\t%-5s  %-40s\n", "-opt", "draw option for histogram [colz, surf2]");
  printf("\n\t%-5s  %-40s\n", "-vmax", "limit the histogram within vmax-value");
  printf("\n\t%-5s  %-40s\n", "-vmin", "limit the histogram within vmin-value");
  printf("\n\t%-5s  %-40s\n", "-col", "column value in pretest");
  printf("\n\t%-5s  %-40s\n", "-row", "row value in pretest");
  printf("\n\t%-5s  %-40s\n", "-p", "print pixel values to stdout");
  printf("\nAUTHOR\n\tXin Shi <Xin.Shi@cern.ch>\n");
}

int main(int argc, char** argv) {
  if (argc < 2) {
    print_usage() ;  
    return -1; 
  }

  bool doRunGui(false);
  TString testLabel; 
  TString version(""); 
  TString inputFile;
  int roc(16); 
  int col(12); 
  int row(22); 
  TString drawOption("colz"); 
  // double vmin = std::numeric_limits<double>::min();
  double vmin = -std::numeric_limits<double>::max();
  double vmax = std::numeric_limits<double>::max();
  bool printpix(false);
  // int V = 0;

  for (int i = 0; i < argc; i++){
    if (!strcmp(argv[i], "-h")) print_usage();
    if (!strcmp(argv[i],"-g")) {doRunGui = true; } 
    if (!strcmp(argv[i],"-i")) {inputFile = std::string(argv[++i]); }   
    if (!strcmp(argv[i],"-r")) {
      roc = atoi(argv[++i]);
      std::cout << "Using ROC " << roc << std::endl;  
    }
    if (!strcmp(argv[i],"-t")) {testLabel = std::string(argv[++i]); }
    if (!strcmp(argv[i],"-v")) {version = std::string(argv[++i]); }
    if (!strcmp(argv[i],"-opt")) {
      drawOption = std::string(argv[++i]);
      std::cout << "Using drawOption = " << drawOption << std::endl;  
    }
    if (!strcmp(argv[i],"-vmin")) {
      vmin = atof(argv[++i]); 
      std::cout << "Using vmin = " << vmin << std::endl; 
    }
    if (!strcmp(argv[i],"-vmax")) {
      vmax = atof(argv[++i]); 
      std::cout << "Using vmax = " << vmax << std::endl; 
    }
    if (!strcmp(argv[i],"-col")) {
      col = atof(argv[++i]); 
      std::cout << "Using col = " << col << std::endl; 
    }
    if (!strcmp(argv[i],"-row")) {
      row = atof(argv[++i]); 
      std::cout << "Using row = " << row << std::endl; 
    }
    if (!strcmp(argv[i],"-p")) {printpix = true; }
  }

  if (doRunGui) { 
    TApplication theApp("App", 0, 0);
    theApp.SetReturnFromRun(true);
    drawMod(testLabel, inputFile, roc, drawOption, vmin, vmax,
	    printpix, col, row);  
    theApp.Run();
  } 
  
  else {
    TCanvas *c = drawMod(testLabel, inputFile, roc, drawOption, 
			 vmin, vmax, printpix, col, row);  
    // TString comname = inputFile;
    // comname.ReplaceAll(".root", "");
    TString outFile;
    if (version == "") {
      outFile = Form("%s.pdf", testLabel.Data());
    }
    else {
      outFile = Form("%s_v%s.pdf", testLabel.Data(), version.Data());
    }
    c->SaveAs(outFile);

    outFile.ReplaceAll("pdf",3,"png",3);  
    c->SaveAs(outFile);
    delete c;
    gSystem->Exit(0);
  }

}



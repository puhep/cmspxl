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
#include <TKey.h> 
#include <TApplication.h> 

using namespace std; 

// template<class T>
// T* getHist(TFile *f, TString histName){
//   T *h = (T*)f->Get(histName); 
//   return h; 
// }


TH1D* getHist(TFile *f, TString histName) {
  TH1D *h = (TH1D*)f->Get(histName); 
  return h; 
}

TCanvas* drawHist(TString inputFile, TString histType, TString histName, 
		  TString drawOption, int V=0){
  TCanvas *c = new TCanvas("c", "c", 800, 800);
  TFile *f = new TFile(inputFile.Data()); 
  // cout << "Key = " << f->GetListOfKeys() << endl; 

  //histName = "dist_sig_scurveVcal_Vcal_C0_V0"; 
  
  // if (!strcmp(dirName, ""))
  //   f->cd(); 
  // else 
  //   cout << "Chaning dir: " << f->cd(dirName) << endl; 
  
  // f->cd("Scurves"); 

  // TIter nextkey(f->GetListOfKeys());
  // TKey *key; 
  // while ( (key = (TKey*)nextkey()) ) {
  //   cout << "key name = " << key->GetName() 
  // 	 << ", class name = " << key->GetClassName() << endl; 
  // }

  // TH1D *h = getHist(f, histName); 
  // if (!strcmp(histType, "TH1D")) {
  //   TH1D *h = (TH1D*)f->Get(histName);
  //   h->Draw(); 
  // }
  // else if (!strcmp(histType, "TH2D")) {
  //   TH2D *h = (TH2D*)f->Get(histName);
  //   h->Draw(); 
  // }
  
  // else {
  //   cout << "Not supported type: " << histType << endl; 
  // }
  // h->Draw();
  // }

  TH2D *h = (TH2D*)f->Get(histName);

  if (!h) cout << "Not able to find hist!" << endl; 

  h->Draw(); 
    
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);

  // TString h_file_name = Form("h_%s", inputFile.Data()); 
  // TFile *fo = new TFile(h_file_name, "RECREATE");
  // h->Write();
  // fo->Close();
  // cout << "Save the hist as: "<< h_file_name << endl;  

  return c; 
}



#ifndef __CINT__ 
#include <iostream>

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
  // TString dirName(""); 

  
  for (int i = 0; i < argc; i++){
    // if (!strcmp(argv[i], "-h")) print_usage();
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
    // if (!strcmp(argv[i],"-d")) {
    //   dirName = string(argv[++i]); 
    //   cout << "Dir name = " << dirName << endl; 
    // }
    
  }

  if (doRunGui) { 
    TApplication theApp("App", 0, 0);
    theApp.SetReturnFromRun(true);
    drawHist(inputFile, histType, histName, drawOption);  
    theApp.Run();
  } 
  
  else {
    TCanvas *c = drawHist(inputFile, histType, histName, drawOption);  
    TString outFile = inputFile;
    outFile.ReplaceAll("root",4,"pdf",3);  
    c->SaveAs(outFile);
    outFile.ReplaceAll("pdf",3,"png",3);  
    c->SaveAs(outFile);
    delete c;
    gSystem->Exit(0);
  }

}

#endif



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

TCanvas* drawHist(vector<TString> inputFiles,
		  TString histType, 
		  TString histName, 
		  TString drawOption, 
		  double vmax, 
		  int V=0){
 
  TCanvas *c = new TCanvas("c", "c", 800, 800);

  c->Divide(inputFiles.size()); 
  
  // TString h_file_name = Form("h_test", inputFile.Data()); 
  TString h_file_name = "h_test.root"; 

  TFile *fo = new TFile(h_file_name, "RECREATE");
  for (vector<int>:: size_type i = 0; i != inputFiles.size(); i++) {
    c->cd(i+1); 

    TFile *f = new TFile(inputFiles[i]); 
    
    if (!strcmp(histType, "TH1D")) {
      TH1D *h = (TH1D*)f->Get(histName);
      if (!h) {
	cout << "Not able to find hist: " << histName << endl; 
	return NULL; 
      }
      h->SetDirectory(0); // "detach" the histogram from the file
      delete f; 
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
      h->SetDirectory(0); // "detach" the histogram from the file
      delete f; 
      if ( vmax != numeric_limits<double>::max())
	h->SetMaximum(vmax); 
      if (drawOption == "") h->Draw("colz"); 
      else h->Draw(drawOption);
      h->Write();
    }
  
    else {
      cout << "Not supported type: " << histType << endl; 
    }
  }
  c->Update();

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
  vector<TString> inputFiles(argv+1, argv+argc);
  TString histName; 
  TString drawOption(""); 
  double vmax = numeric_limits<double>::max();
  
  int delta_idx = 0; 
  for (int i = 0; i < argc; i++){
    if (!strcmp(argv[i],"-b")) {doRunGui = false; } 
    // if (!strcmp(argv[i],"-i")) {inputFile = string(argv[++i]); }  

    if (!strcmp(argv[i],"-t")) {
      histType = string(argv[++i]); 
      // inputFiles.erase(inputFiles.begin()+i-2, inputFiles.begin()+i); 
      inputFiles.erase(inputFiles.begin()+i-2+delta_idx,
		       inputFiles.begin()+i+delta_idx); 
      delta_idx = -2; 
    }
    
    if (!strcmp(argv[i],"-drawOption")) {
      drawOption = string(argv[++i]);
      inputFiles.erase(inputFiles.begin()+i-1); 
      cout << "Using drawOption = " << drawOption << endl;  
    }

    if (!strcmp(argv[i],"-h")) {
      histName = string(argv[++i]); 
      //inputFiles.erase(inputFiles.begin()+i-4, 
      // inputFiles.begin()+i-2);
      inputFiles.erase(inputFiles.begin()+i-2+delta_idx,
		       inputFiles.begin()+i+delta_idx); 
      delta_idx -= 2; 
      cout << "Hist name = " << histName << endl; 
    }
    if (!strcmp(argv[i],"-vmax")) {
      vmax = atof(argv[++i]); 
      cout << "Using vmax = " << vmax << endl; 
    }
  }
  
  for (vector<int>:: size_type i = 0; i != inputFiles.size(); i++) {
    cout << "inputFile >>> " << inputFiles[i] << endl; 
  }
  // exit(0); 

  if (doRunGui) { 
    TApplication theApp("App", 0, 0);
    theApp.SetReturnFromRun(true);
    drawHist(inputFiles, histType, histName, drawOption, vmax);  
    theApp.Run();
  } 
  
  else {
    TCanvas *c = drawHist(inputFiles, histType, histName, drawOption, 
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




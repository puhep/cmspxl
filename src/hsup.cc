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
#include <TLegend.h>    
#include <TApplication.h>
#include <TPaveStats.h>
#include <TPad.h> 

using namespace std; 


TCanvas* hsup(vector<TString> inputFiles){
  gROOT->SetStyle("Plain");
  // gStyle->SetPalette(55);
  gStyle->SetOptStat("Mner");
  // gStyle->SetOptStat(1111111);
  // gStyle->SetOptFit(1011);
  gStyle->SetTitle(0);
  
  TCanvas *c = new TCanvas("c", "c", 800, 800);

  TString hname = "dist_sig_scurveVcal_Vcal_C0_V0"; 
  
  TLegend *leg = new TLegend(0.2, 0.6, 0.5, 0.8);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetNColumns(1);
  leg->SetTextSize(0.02);
  leg->SetTextSizePixels(25);

  for (vector<int>:: size_type i = 0; i != inputFiles.size(); i++) {
    TFile *f = new TFile(inputFiles[i]); 
    TH1D *h = (TH1D*)f->Get(hname);
    h->SetDirectory(0); // "detach" the histogram from the file
    delete f; 
    int color = i+1;
    h->SetStats(1); 
    cout << "File name = " << inputFiles[i] << endl; 
    h->SetLineColor(color);

    // h->Fit("gaus");
    if (i==0) {
      h->Draw();
    }
    else h->Draw("sames");

    // TPaveStats* st = (TPaveStats*) h->FindObject("stats");
    //st->SetTextColor(color); 
    // st->SetX1NDC(0.1);
    // st->SetX2NDC(0.3);
    // st->SetY1NDC(0.7);
    // st->SetY2NDC(0.9);
    //gPad->Update();     

    leg->AddEntry(h, Form("%s", inputFiles[i].Data()),"f"); 
  }

  // TH2D *hsup = new TH2D("hsup", "", 416, 0., 416., 160, 0., 160.);
  // double v1, v2, sup; 
  
  // hsup->SetMaximum(1.);
  // hsup->SetMinimum(-1.);
  // hsup->Draw("colz");
  
  leg->Draw(); 
  c->Update();
  
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



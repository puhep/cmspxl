// 
// Author: Xin Shi <Xin.Shi@cern.ch> 
// 2014.06.18
// 

#include <iostream>
#include <stdlib.h> /* atof */ 
#include <limits>  
#include <TROOT.h>
#include <TSystem.h>
#include <TString.h>
#include <TH2D.h> 
#include <TFile.h> 
#include <TCanvas.h> 
#include <TStyle.h> 
#include <TApplication.h>
#include <TLegend.h>    
#include <TPaveStats.h>


using namespace std; 

void set_root_style(int stat=1110, int grid=0){
  gROOT->Reset();

  gStyle->SetTitleFillColor(0) ; 
  gStyle->SetTitleBorderSize(0); 
    
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetCanvasDefX(0); 
  gStyle->SetCanvasDefY(0); 
  gStyle->SetFrameBorderMode(0); 
  gStyle->SetFrameBorderSize(1); 
  gStyle->SetFrameFillColor(0); 
  gStyle->SetFrameFillStyle(0); 
  gStyle->SetFrameLineColor(1); 
  gStyle->SetFrameLineStyle(1); 
  gStyle->SetFrameLineWidth(1); 

  // gStyle->SetPadTopMargin(PadTopMargin);  
  gStyle->SetPadLeftMargin(0.10);  
  gStyle->SetPadRightMargin(0.25);  

  gStyle->SetLabelSize(0.03, "XYZ");  
  gStyle->SetTitleSize(0.04, "XYZ");  
  gStyle->SetTitleOffset(1.2, "Y");  

  gStyle->SetPadBorderMode(0);  
  gStyle->SetPadColor(0);  
  gStyle->SetPadTickX(1); 
  gStyle->SetPadTickY(1); 
  gStyle->SetPadGridX(grid); 
  gStyle->SetPadGridY(grid); 

  gStyle->SetOptStat(stat); 
  gStyle->SetStatColor(0); 
  gStyle->SetStatBorderSize(1); 
}


TCanvas* drawHist(vector<TString> inputFiles,
		  TString histType, 
		  TString histName, 
		  TString drawOption, 
		  double vmax,
		  int npad, 
		  int V=0){

  int nfig, ww, wh;
  if (npad == 0) {
    nfig = inputFiles.size();
    ww = 400*nfig;
    wh = 400; 
  } else {
    nfig = npad;
    ww = 800;
    wh = 800; 
  }
  
  set_root_style();
  TCanvas *c = new TCanvas("c", "c", ww, wh); 

  if (npad > 1) 
    c->Divide(nfig); 
  
  // TString h_file_name = Form("h_test", inputFile.Data()); 
  TString h_file_name = "h_test.root"; 

  // TFile *fo = new TFile(h_file_name, "RECREATE");
  TH1D *h;

  TLegend *leg = new TLegend(0.2, 0.6, 0.5, 0.8);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetNColumns(1);
  leg->SetTextSize(0.02);
  leg->SetTextSizePixels(25);

  for (vector<int>:: size_type i = 0; i != inputFiles.size(); i++) {
    if (npad > 1) 
      c->cd(i+1); 

    TFile *f = new TFile(inputFiles[i]); 
    
    if (!strcmp(histType, "TH1D")) {
      // TH1D *h = (TH1D*)f->Get(histName);
      h = (TH1D*)f->Get(histName);
      if (!h) {
	cout << "Not able to find hist: " << histName << endl; 
	return NULL; 
      }

      // std::cout << ">>> testing... " << std::endl; 
      // h->SetDirectory(0); 
      // delete f; 
      // h->SetTitle(inputFiles[i]); 
      if ( vmax != numeric_limits<double>::max())
	h->SetMaximum(vmax);

      if ( npad != 1) h->Draw(drawOption);
      else { // superimpose on one pad
	// h->SetStats(1); 
	int color = i+1;
	h->SetLineColor(color);
	
	if (i==0) 
	  h->Draw(drawOption);
	else
	  h->Draw("sames");

	gPad->Update();
	TPaveStats* st = (TPaveStats*) h->FindObject("stats");
	// cout << ">>>> st : " << st << endl; 
	st->SetTextColor(color); 
	st->SetX1NDC(0.78);
	st->SetX2NDC(0.98);
	st->SetY1NDC(0.98-0.22*i);
	st->SetY2NDC(0.78-0.22*i);
	
	leg->AddEntry(h, Form("%s", inputFiles[i].Data()),"f"); 
      }
      // h->Write();
    }

    else if (!strcmp(histType, "TH2D")) {
      TH2D *h = (TH2D*)f->Get(histName);
      if (!h) {
	cout << "Not able to find hist: " << histName << endl; 
	return NULL; 
      }
      // h->SetDirectory(0); 
      // delete f; 
      h->SetTitle(inputFiles[i]); 
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

  leg->Draw(); 
  c->Update();

  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);

  TFile *fo = new TFile(h_file_name, "RECREATE");
  h->Write();
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
  int npad = 0; 

  int delta_idx = 0; 
  for (int i = 0; i < argc; i++){
    // if (!strcmp(argv[i],"-b")) {
    //   doRunGui = false;  
    //   inputFiles.erase(inputFiles.begin()+i-2+delta_idx,
    // 		       inputFiles.begin()+i+delta_idx); 
    //   delta_idx -= 1; 
    // } 

    if (!strcmp(argv[i],"-t")) {
      histType = string(argv[++i]); 
      inputFiles.erase(inputFiles.begin()+i-2+delta_idx,
		       inputFiles.begin()+i+delta_idx); 
      delta_idx -= 2; 
    }
    
    if (!strcmp(argv[i],"-drawOption")) {
      drawOption = string(argv[++i]);
      inputFiles.erase(inputFiles.begin()+i-2+delta_idx,
		       inputFiles.begin()+i+delta_idx); 
      delta_idx -= 2; 
      cout << "Using drawOption = " << drawOption << endl;  
    }

    if (!strcmp(argv[i],"-h")) {
      histName = string(argv[++i]); 
      inputFiles.erase(inputFiles.begin()+i-2+delta_idx,
		       inputFiles.begin()+i+delta_idx); 
      delta_idx -= 2; 
      cout << "Hist name = " << histName << endl; 
    }
    if (!strcmp(argv[i],"-vmax")) {
      vmax = atof(argv[++i]); 
      inputFiles.erase(inputFiles.begin()+i-2+delta_idx,
		       inputFiles.begin()+i+delta_idx); 
      delta_idx -= 2; 
      cout << "Using vmax = " << vmax << endl; 
    }
    
    if (!strcmp(argv[i],"-npad")) {
      npad = atof(argv[++i]); 
      inputFiles.erase(inputFiles.begin()+i-2+delta_idx,
		       inputFiles.begin()+i+delta_idx); 
      delta_idx -= 2; 
      cout << "Using npad = " << npad << endl; 
    }
 
  }
  
  for (vector<int>:: size_type i = 0; i != inputFiles.size(); i++) {
    cout << "inputFile >>> " << inputFiles[i] << endl; 
  }
  // exit(0); 

  if (doRunGui) { 
    TApplication theApp("App", 0, 0);
    theApp.SetReturnFromRun(true);
    drawHist(inputFiles, histType, histName, drawOption, vmax, npad);  
    theApp.Run();
  } 
  
  else {
    TCanvas *c = drawHist(inputFiles, histType, histName, drawOption, 
			  vmax, npad);  
    TString outFile = inputFile;
    outFile.ReplaceAll("root",4,"pdf",3);  
    c->SaveAs(outFile);
    outFile.ReplaceAll("pdf",3,"png",3);  
    c->SaveAs(outFile);
    delete c;
    gSystem->Exit(0);
  }

}




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
		  TString opt, 
		  double vmax,
		  double vmin,
		  bool printpix,
		  int npad,
		  int V=0){

  int ww, wh;
  if (npad == 1) {
    ww = 800;
    wh = 800; 
  } else {
    ww = 400*inputFiles.size();
    wh = 400; 
  }
  
  set_root_style();
  TCanvas *c = new TCanvas("c", "c", ww, wh); 

  if (npad > 1) 
    c->Divide(npad); 
  
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

      if ( npad != 1) h->Draw(opt);
      else { // superimpose on one pad
	// h->SetStats(1); 
	int color = i+1;
	h->SetLineColor(color);
	
	if (i==0) 
	  h->Draw(opt);
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
      
      int nbinx = h->GetXaxis()->GetNbins();
      int nbiny = h->GetYaxis()->GetNbins();
      double v;
      // h->SetDirectory(0); 
      // delete f;
      if (printpix==true) {
	printf("  Pixel Values:\n");
        for (int ix = 1; ix <= nbinx; ix++) {
	  for (int iy = 1; iy <= nbiny; iy++) {
	    v = h->GetBinContent(ix, iy);
	    if (v>=vmin && v<=vmax) {
	      printf("\tc%i, r%i: %f \n", ix, iy, v);
	    }
	  }
        }
      }
      h->SetTitle(inputFiles[i]);
      if ( vmax != numeric_limits<double>::max())
	h->SetMaximum(vmax);
      if (vmin != -numeric_limits<double>::max())
	h->SetMinimum(vmin);
      if (opt == "") h->Draw("colz"); 
      else h->Draw(opt);
      //h->Write();
    }
  
    else {
      cout << "Not supported type: " << histType << endl; 
    }
  }

  leg->Draw(); 
  c->Update();

  // gROOT->SetStyle("Plain");
  // gStyle->SetOptStat(0);

  //TFile *fo = new TFile(h_file_name, "RECREATE");
  //h->Write();
  //fo->Close();
  //cout << "Save the hist as: "<< h_file_name << endl;  
  
  return c; 
}


void print_usage(){
  printf("NAME\n\tdrawHist - draw Histograms\n");
  printf("\nSYNOPSIS\n\tdrawHist [-t hist-type ] [-opt draw-option]\n "); 
  printf("\t[-h hist-name ] [-vmax max-value] [-npad num-pad] [-b] input1 input2 ...\n");
  printf("\nOPTIONS\n");
  printf("\t%-5s  %-40s\n", "-b", "batch mode");
  printf("\t%-5s  %-40s\n", "-t", "hist type [TH1D, TH2D]");
  printf("\n\t%-5s  %-40s\n", "-opt", "draw option for histgram [colz, surf2]");
  printf("\n\t%-5s  %-40s\n", "-h", "histogram name");
  printf("\n\t%-5s  %-40s\n", "-vmax", "limit the histogram within vmax-value");
  printf("\n\t%-5s  %-40s\n", "-vmin", "limit the histogram within vmin-value");
  printf("\n\t%-5s  %-40s\n", "-p", "print pixel values to stdout");
  printf("\nAUTHOR\n\tXin Shi <Xin.Shi@cern.ch>\n");
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
  TString opt(""); 
  double vmax = numeric_limits<double>::max();
  double vmin = -numeric_limits<double>::max();
  bool printpix(false);
  int npad = 1; // use 1 as default

  int delta_idx = 0; 
  for (int i = 0; i < argc; i++){
    if (!strcmp(argv[i],"-b")) {
      doRunGui = false;  
      inputFiles.erase(inputFiles.begin()+i-2+delta_idx,
    		       inputFiles.begin()+i+delta_idx); 
      delta_idx -= 1; 
    } 

    if (!strcmp(argv[i],"-t")) {
      histType = string(argv[++i]); 
      inputFiles.erase(inputFiles.begin()+i-2+delta_idx,
		       inputFiles.begin()+i+delta_idx); 
      delta_idx -= 2; 
    }
    
    if (!strcmp(argv[i],"-opt")) {
      opt = string(argv[++i]);
      inputFiles.erase(inputFiles.begin()+i-2+delta_idx,
		       inputFiles.begin()+i+delta_idx); 
      delta_idx -= 2; 
      cout << "Using opt = " << opt << endl;  
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
    
    if (!strcmp(argv[i],"-vmin")) {
      vmin = atof(argv[++i]); 
      inputFiles.erase(inputFiles.begin()+i-2+delta_idx,
    		       inputFiles.begin()+i+delta_idx); 
      delta_idx -= 2; 
      cout << "Using vmin = " << vmin << endl;
    }

    if (!strcmp(argv[i],"-p")) {
      printpix = true;
      inputFiles.erase(inputFiles.begin()+i-1+delta_idx,
      	       inputFiles.begin()+i+delta_idx); 
      delta_idx -= 1;
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
    drawHist(inputFiles, histType, histName, opt, vmax, vmin, printpix, npad);  
    theApp.Run();
  } 
  
  else {
    TCanvas *c = drawHist(inputFiles, histType, histName, opt, 
			  vmax, vmin, printpix, npad);  
    TString outFile = "h_test.pdf";
    // TString outFile = inputFile;
    // outFile.ReplaceAll("root",4,"pdf",3);  
    // c->SaveAs(outFile);
    // outFile.ReplaceAll("pdf",3,"png",3);  
    c->SaveAs(outFile);
    delete c;
    gSystem->Exit(0);
  }

}




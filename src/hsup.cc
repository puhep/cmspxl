//
// Superimpose histograms 
// Author: Xin Shi <Xin.Shi@cern.ch> 
// 2014.06.18
// 

#include <iostream>
#include <fstream>
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


TCanvas* hsup(vector<TString> inputFiles, TString hname, TString mname){
  gROOT->SetStyle("Plain");
  // gStyle->SetPalette(55);
  gStyle->SetOptStat("Mner");
  // gStyle->SetOptStat(1111111);
  // gStyle->SetOptFit(1011);
  gStyle->SetTitle(0);
  
  TCanvas *c = new TCanvas("c", "c", 800, 800);

  // TString hname = "dist_sig_scurveVcal_Vcal_C0_V0";
  TString roc0 = "C0";
  TString roc1 = "C1";
  TString roc2 = "C2";
  TString roc3 = "C3";
  TString roc4 = "C4";
  TString roc5 = "C5";
  TString roc6 = "C6";
  TString roc7 = "C7";
  int chip;
  
  if(hname.Contains(roc0))
  {
  	chip = 0;
  }
  else if(hname.Contains(roc1))
  {
	  chip = 1;
  }
  else if(hname.Contains(roc2))
  {
	  chip = 2;
  }
  else if(hname.Contains(roc3))
  {
	  chip = 3;
  }
  else if(hname.Contains(roc4))
  {
	  chip = 4;
  }
  else if(hname.Contains(roc5))
  {
	  chip = 5;
  }
  else if(hname.Contains(roc6))
  {
	  chip = 6;
  }
  else if(hname.Contains(roc7))
  {
	  chip = 7;
  }
  
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
    if (color == 3) color ++; // skip green 
    h->SetStats(1); 
    cout << "File name = " << inputFiles[i] << endl; 
    h->SetLineColor(color);
    
    // h->Fit("gaus");
    if (i==0) {
      h->Draw();
    }
    else h->Draw("sames");
    gPad->Update();     
    TPaveStats* st = (TPaveStats*) h->FindObject("stats");
    // cout << ">>>> st : " << st << endl; 
    st->SetTextColor(color); 
    st->SetX1NDC(0.78);
    st->SetX2NDC(0.98);
    st->SetY1NDC(0.98-0.22*i);
    st->SetY2NDC(0.78-0.22*i);
	
	// Output the mean and mean error to the mean file: (added by Ben Fasig)
	ofstream meanfile;
	double mean;
	double meanerr;
	
	if(mname.Sizeof() >= 5)
	{
		meanfile.open(mname, ios::app);
		mean = h->GetMean();
		meanerr = h->GetMeanError();
		cout << "Mean: " << mean << " +/- " << meanerr << endl;
		
		if(meanfile.is_open())
		{
			meanfile.precision(4); //Sets number of decimal places to use in file output
			if(i==0)
			{
				meanfile << endl;
				meanfile << "roc";
				meanfile << chip;
			}
			meanfile << "\t";
			meanfile << mean;
			meanfile << " +/- ";
			meanfile << meanerr;
			meanfile.close();
		}
		else cout << "Unable to open mean file" << endl;
		
	}
	


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
  TString histName; 
  TString meanFileName;
  TString outFile = "sup.pdf";
  
  // if (doBatch) { 
  //   cout << "Run in batch mode ... " << endl;
  //   TCanvas *c = hsup(inputFile1, inputFile2);
  //   c->SaveAs(outFile);
  //   delete c;
  //   gSystem->Exit(0);
  // }
    int delta_idx = 0; 
  for (int i = 0; i < argc; i++){

    if (!strcmp(argv[i],"-h")) {
      histName = string(argv[++i]); 
      inputFiles.erase(inputFiles.begin()+i-2+delta_idx,
		       inputFiles.begin()+i+delta_idx); 
      delta_idx -= 2; 
      cout << "Hist name = " << histName << endl; 
    }
	
    if (!strcmp(argv[i],"-m")) {
      meanFileName = string(argv[++i]); 
      inputFiles.erase(inputFiles.begin()+i-2+delta_idx,
		       inputFiles.begin()+i+delta_idx); 
      delta_idx -= 2; 
      cout << "Mean file name = " << meanFileName << endl; 
    }
  }
 

  TApplication theApp("App", 0, 0);
  theApp.SetReturnFromRun(true);

  hsup(inputFiles, histName, meanFileName);  
  theApp.Run();

}

#endif



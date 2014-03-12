// 
// Author: Xin Shi <Xin.Shi@cern.ch> 
// 2014.03.11
// 

#include <iostream>
// #include <string> 

#include <TSystem.h>
#include <TString.h>
#include <TH2D.h> 
#include <TFile.h> 
#include <TCanvas.h> 

using namespace std; 

/*
void addVcalThreshold(char *dirName, int chip, TH2D *h3) 
{
 
  int icol, irow, value;

  float thr, sig;
  int a,b;
  int VcalOut = 0;
  FILE *inputFile;
  char string[200];
  sprintf(string, "%s/SCurve_C%i.dat", dirName, chip);
  inputFile = fopen(string, "r");
  if (!inputFile)
  {
	 printf("moduleSummary> !!!!!!!!!  ----> SCurve: Could not open file %s to read fit results\n", string);
  }
  else {
    for (int i = 0; i < 2; i++) fgets(string, 200, inputFile);
    
    for (icol = 0; icol < 52; icol++) {
      for (irow = 0; irow < 80; irow++)  {
	
	fscanf(inputFile, "%e %e %s %2i %2i\n", &thr, &sig, string, &a, &b); 
	value = thr / 65;
	
	if (chip < 8) {h3->SetBinContent(415-(chip*52+icol)+1, 159-irow+1, value);}
	if (chip > 7) {h3->SetBinContent((chip-8)*52+icol+1, irow+1, value);}

      }
    }
  }
  }*/ 



void daq(TFile * inputFile) {
  // cout << inputFile << endl; 
  

  // TDirectory* myDir = myFile->GetDirectory(Form("MyCMSPixelClusteringProcessor/detector_%d", nDetector));
  // if (!myDir) {
  //   std::cerr << "Could not find the right directory" << std::endl;
  //   return -1;    
  // }
  // myHisto = (TH2D*)myDir->GetObjectChecked(Form("hitMap_d%d", nDetector), "TH2D");
  // if (!myHisto) {
  //   std::cerr << "Could not find the histogram" << std::endl;
  //   return -1;
  // }
  TH2D *h3 = new TH2D("h3", "", 416, 0., 416., 160, 0., 160.);
  TH2D *h2d;
  for (int chip = 5; chip < 16 ; chip++) { 
    gDirectory->GetObject(Form("DAQ/Hits_C%d_V0", chip), h2d); 
    
    if (! h2d){
      cerr << "No object name found: " << endl;
      return ;
    }
    
    // cout << h2d->GetEntries() << endl; 
    
    for (int icol = 0; icol < 52; icol++) {
      for (int irow = 0; irow < 80; irow++)  {
	double value = h2d->GetBinContent(icol, irow); 
	cout << icol << "," << irow << ": " << value << endl;  
	if (chip < 8) {h3->SetBinContent(415-(chip*52+icol)+1, 159-irow+1, value);}
	if (chip > 7) {h3->SetBinContent((chip-8)*52+icol+1, irow+1, value);}
      }
    }
  }
  
  TCanvas *c = new TCanvas("c", "DAQ module",800, 200); 
  h3->DrawCopy("colz");
  c->SaveAs(Form("test.pdf"));  
}





#ifndef __CINT__ 
#include <iostream>
#include <algorithm>

char* get_option(char ** begin, char ** end, const std::string & option){
  char ** itr = std::find(begin, end, option);
  if (itr != end && ++itr != end)  return *itr;
  return 0;
}

bool option_exists(char** begin, char** end, const std::string& option){
  return std::find(begin, end, option) != end;
}

void print_usage(){
  cerr << "Usage: drawMod daq inputFile\n" << endl; 
}

int main(int argc, char** argv) {
  if (argc < 2) {
    print_usage() ;  
    return -1; 
  }
  
  if (strcmp(argv[1], "daq") == 0 ) {
    TFile * inputFile = TFile::Open(argv[2]);
    if ( inputFile ) {
      daq(inputFile); 
    } else {
      cerr << "Unable to open file: " << argv[2] << endl; 
    }
  }
  
  else {
    print_usage(); 
  }

  gSystem->Exit(0);

  return 0 ;
}

#endif



// 
// Author: Sam Higginbotham <shigginb@purdue.edu>
// Date: 2014.08.14 
// Extensive help from Developer: Xin Shi.

 
//Global Parameters
#include <iostream>
#include <fstream> 
#include <sstream>
#include <string>


#include <TROOT.h>
#include <TSystem.h>
#include <TString.h>
#include <TH2D.h> 
#include <TFile.h> 
#include <TCanvas.h> 
#include <TStyle.h> 
#include <Riostream.h>
#include <TTree.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TLegend.h>
#include <TApplication.h> 
#include <TMath.h> 



//User Defined Functions
void createTree(); 
void createHist();


//Executables
int main()
{

 /* TApplication theApp("App", 0, 0);
  theApp.SetReturnFromRun(true);
  drawVD(inputFiles);
  theApp.Run();
  */
  createTree();
  createHist(VD.root);

  return(0);
}


//NOTE!CONTRIBUTIONS STATED: Creating Tree for Data. Example from the ROOTUsersGuideLetter.pdf page 318. 
//Structure to hold the 3 data types of interest

void createTree()
{

  gROOT->Reset();


  struct voltage_t
    {
	float_t Roc;
	float_t vd;
	float_t DacCap;
	float_t Vdig;

    };

  voltage_t voltage;


  //Open the data file-may need to change the pointer...VD.dat may not be correct.
  FILE * fp = fopen("VD.dat","r");

  //end of line
  char line[28];

  //Create Root file
  TFile *f = new TFile("VD.root","RECREATE");

  //create a TTree
  TTree *tree = new TTree("T","Voltage Drop data from file");


  //create one branch with information form the stucture
  tree->Branch("voltage", &voltage.Roc,"Roc/I:vd:DacCap:Vdig");


  //Parces the text file and fills the tree

  while(fgets(line,27,fp))
  {
    sscanf(&line[0],"%3f%3f%3f%3f",&voltage.Roc,&voltage.vd, &voltage.DacCap,&voltage.Vdig);
    std::cout <<  "line: " << line << std::endl; 
    tree->Fill();
  } 

  //Shows the tree after it has been filled. 
  //tree->Print();
  fclose(fp);
  f->Write();
}

//Creating the graphical Interface. 
void createHist(VD.root)
{
 


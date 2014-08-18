// 
// Author: Sam Higginbotham <shigginb@purdue.edu>
// Date: 2014.08.14 
// 
//Global Parameters
#include <iostream>
#include <fstream> 
#include <string>


//Executables

//NOTE!CONTRIBUTIONS STATED: Creating Tree for Data. Example from the ROOTUsersGuideLetter.pdf page 318. 
//Structure to hold the 3 data types of interest

struct voltage_t{
	Int_t Roc;
	Int_t VD[V];
	Int_t DAC_CAP[V];
	Int_t Vdig[V];

};

//voltage_t voltage;


//Open the data file-may need to change the pointer...VD.dat may not be correct.
FILE *fp = fopen("VD.dat","r");

//end of file


//Create Root file
TFILE *f = new TFile("VD.root","RECREATE");

//create a TTree
TTree *tree = new TTree("T","Voltage Drop data from file");


//create one branch with information form the stucture
tree->Branch("VoltageDrop", &staff.cat,"cat/Cap1:Cap2:Cap3");


//Parces the text file. 

while(fgets(&line. 

int main(int argc, char** argv)
{
  int data [5] = {0};
  int start = 0;

  std::cout << "This is my test!\n";
  
  return 0;
}


//Creating the graphical Interface. 

//
// Parse the output from TBM 
// Author: Xin Shi <Xin.Shi@cern.ch> 
// 2014.07.03
// 


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


void print_usage(){
  std::cout << "Usage: parseTbm inputFile" << std::endl; 
}


int main(int argc, char** argv) {
  if (argc < 2) {
    print_usage() ;  
    return 1; 
  }

  std::string inputFile(argv[1]); 
  std::ifstream fin;
  fin.open(inputFile.c_str());

  if (!fin.good()) 
    return 1;

  std::string line;
  int nlines = 0; 
  while(getline(fin, line))   {
    nlines ++; 
    std::istringstream iss(line);
    if (line.find("words") == 0) {
      std::cout << nlines << ": " << line << std::endl; 
      }
    // getline(iss, name, ':');
    // getline(iss, age, '-');
    // getline(iss, salary, ',');
    // getline(iss, hoursWorked, '[');
    // getline(iss, randomText, ']');
  }
  fin.close();
  
}



//
// Parse the output from TBM 
// Author: Xin Shi <Xin.Shi@cern.ch> 
// 2014.07.03
// 


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <bitset> 

static inline std::string &ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(),
				  std::not1(std::ptr_fun<int, int>(std::isspace))));
  return s;
}

void print_usage(){
  std::cout << "Usage: parseTbm inputFile" << std::endl; 
}

int get_value_from_digits(std::string line, std::string digits){
  // std::cout << line << std::endl;
  std::size_t pos = line.find("=");
  std::string value = line.substr(pos+2);
  // value = "111100110";
  std::bitset<16> b_val(value);  
  std::bitset<16> b_dig(digits);  

  b_val = (b_val & b_dig);
  int i_value = b_val.to_ulong(); 
  // std::cout << value << " ==== " << (b_val & b_dig) <<  std::endl; 
  // std::cout << value << ", i_value = " << i_value << std::endl; 
  
  // exit(0); 
  return i_value; 
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
  int line_num = 0;
  //int tbm_line_num = 0; 
  bool check_tbm_header(false);
  // bool tbm_trailer(false);

  std::string digits("1111"); 
  while(getline(fin, line))   {
    line_num ++; 
    std::istringstream iss(line);
    // std::string line_trim = ltrim(line);
    line = ltrim(line);

    if (line.find("words") == 0) {
      std::cout << line_num << ": " << line << std::endl;
      check_tbm_header = true;
      // tbm_line_num = line_num + 1; 
    }

    if (check_tbm_header)  {
      if (line.find("8") == 0) {
	std::cout << "Event: " << get_value_from_digits(line, digits); //<< std::endl; 
      }

      if (line.find("9") == 0) {
	std::cout << get_value_from_digits(line, digits) << std::endl; 
      }

    }

    // getline(iss, name, ':');
    // getline(iss, age, '-');
    // getline(iss, salary, ',');
    // getline(iss, hoursWorked, '[');
    // getline(iss, randomText, ']');
  }
  fin.close();
  
}



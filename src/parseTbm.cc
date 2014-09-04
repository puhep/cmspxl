//
// Parse the output from TBM 
// Authors: Xin Shi <Xin.Shi@cern.ch> 
//	    Kamal Khan <khan62@purdue.edu>
// 2014.07.18
// 


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <bitset> 

void print_usage(){
  std::cout << "Usage: parseTbm inputFile" << std::endl; 
}

// Checks the haystack for the needle, starting at cur_pos. If found, cur_pos is
// updated to point to the end of needle in haystack, and any characters between
// cur_pos and the beginning of needle are stored in extra. If not found, cur_pos
// and extra are not updated.
int parse(int& cur_pos, std::string& extra, std::string needle, std::string haystack){ 

  std::size_t found = haystack.find(needle, cur_pos);

  if(found == std::string::npos){
	return 0;
  }
  
  if(found-cur_pos > 0){
  	extra = haystack.substr(cur_pos, found-cur_pos);
  }

  cur_pos += extra.length();
  cur_pos += needle.length();

  return 1;
}

int rocparse(int& cur_pos, std::string& extra, std::string& roc, std::string needle, std::string haystack){ 

  std::size_t found = haystack.find(needle, cur_pos);

  if(found == std::string::npos || found > haystack.length()-5){
	return 0;
  }
  
  if(found-cur_pos > 0){
  	extra = haystack.substr(cur_pos, found-cur_pos);
  }

  roc = haystack.substr(found, 12);

  cur_pos += extra.length();
  cur_pos += roc.length();

  return 1;
}

int arbitraryparse(int& cur_pos, std::string& parsed, std::string haystack, int num){

	parsed = haystack.substr(cur_pos, num);

	cur_pos += num;

	return 1;
}

std::string readable(std::string binstr){

	for(int i=4; i<binstr.length(); i+=5){

		binstr.insert(i, " ");

	}
	return binstr;
}

//If non-empty, extra is printed.
void print_extra(std::string extra){

  if(extra == ""){
	return;
  }
  else{
	std::cout << extra << " Extra Bits" << std::endl;
	return;
  }
}

int coreparse(std::string name, std::string input){
  
  std::string header("011111111100");
  std::string trailer("011111111110");
  std::string event_num("");
  std::string cal_mode("");
  std::string roc("0111111110");
  std::string res_roc_cal_trig("");
  std::string stack_count("");

  int cur_pos = 0;
  int cur_end = input.length()-1; 
 
  std::string extra_pre("");
  std::string extra_ev_num("");
  std::string extra_cal_mode("");
  std::string extra_roc0("");
  std::string extra_roc1("");
  std::string extra_roc2("");
  std::string extra_roc3("");
  std::string extra_roc4("");
  std::string extra_roc5("");
  std::string extra_roc6("");
  std::string extra_roc7("");
  std::string extra_trailer("");
  std::string extra_res_roc_cal_trig("");
  std::string extra_stack_count("");
  std::string extra_post("");

  std::string roc0("");
  std::string roc1("");
  std::string roc2("");
  std::string roc3("");
  std::string roc4("");
  std::string roc5("");
  std::string roc6("");
  std::string roc7("");

  int found_header = parse(cur_pos, extra_pre, header, input);
  int found_ev_num = arbitraryparse(cur_pos, event_num, input, 8);
  int found_cal_mode = arbitraryparse(cur_pos, cal_mode, input, 8);
  
  int found_roc0 = rocparse(cur_pos, extra_roc0, roc0, roc, input);
  int found_roc1 = rocparse(cur_pos, extra_roc1, roc1, roc, input);
  int found_roc2 = rocparse(cur_pos, extra_roc2, roc2, roc, input);
  int found_roc3 = rocparse(cur_pos, extra_roc3, roc3, roc, input);
  int found_roc4 = rocparse(cur_pos, extra_roc4, roc4, roc, input);
  int found_roc5 = rocparse(cur_pos, extra_roc5, roc5, roc, input);
  int found_roc6 = rocparse(cur_pos, extra_roc6, roc6, roc, input);
  int found_roc7 = rocparse(cur_pos, extra_roc7, roc7, roc, input);

  int found_trailer = parse(cur_pos, extra_trailer, trailer, input);
  int found_res_roc_cal_trig = arbitraryparse(cur_pos, res_roc_cal_trig, input, 10);
  int found_stack_count = arbitraryparse(cur_pos, stack_count, input, 6);
  
  if(cur_pos < cur_end){
  	extra_post = input.substr(cur_pos, cur_pos-cur_end);
  }

  std::cout << name << std::endl;

  //std::cout << "Input: " << input << std::endl;

  std::cout << "Parse: " << std::endl;

  std::cout << extra_pre << " Idle Pattern 1" << std::endl;
  if(found_header){
	std::cout << readable(header) << " TBM Header" << std::endl;
  }
  else{
	std::cout << "No TBM Header Found" << std::endl;
  }

  //print_extra(extra_ev_num);
  if(found_ev_num){
	std::cout << readable(event_num)  << " Event Number" << std::endl;
  }
  else{
	std::cout << "No Event Number Found" << std::endl;
  }
  // print_extra(extra_cal_mode);
  if(found_cal_mode){
	std::cout << readable(cal_mode) << " Calibration Mode" << std::endl;
  }
  else{
	std::cout << "No Calibration Mode Found" << std::endl;
  }

  print_extra(extra_roc0);
  if(found_roc0){
	std::cout << readable(roc0) << " ROC0" << std::endl;
  }
  else{
	std::cout << "No ROC0 Found" << std::endl;
  }

  print_extra(extra_roc1);
  if(found_roc1){
	std::cout << readable(roc1) << " ROC1" << std::endl;
  }
  else{
	std::cout << "No ROC1 Found" << std::endl;
  }

  print_extra(extra_roc2);
  if(found_roc2){
	std::cout << readable(roc2) << " ROC2" << std::endl;
  }
  else{
	std::cout << "No ROC2 Found" << std::endl;
  }

  print_extra(extra_roc3);
  if(found_roc3){
	std::cout << readable(roc3) << " ROC3" << std::endl;
  }
  else{
	std::cout << "No ROC3 Found" << std::endl;
  }

  print_extra(extra_roc4);
  if(found_roc4){
	std::cout << readable(roc4) << " ROC4" << std::endl;
  }
  else{
	std::cout << "No ROC4 Found" << std::endl;
  }

  print_extra(extra_roc5);
  if(found_roc5){
	std::cout << readable(roc5) << " ROC5" << std::endl;
  }
  else{
	std::cout << "No ROC5 Found" << std::endl;
  }

  print_extra(extra_roc6);
  if(found_roc6){
	std::cout << readable(roc6) << " ROC6" << std::endl;
  }
  else{
	std::cout << "No ROC6 Found" << std::endl;
  }

  print_extra(extra_roc7);
  if(found_roc7){
	std::cout << readable(roc7) << " ROC7" << std::endl;
  }
  else{
	std::cout << "No ROC7 Found" << std::endl;
  }

  print_extra(extra_trailer);
  if(found_trailer){
	std::cout << readable(trailer) << " TBM Trailer" << std::endl;
  }
  else{
	std::cout << "No TBM Trailer Found" << std::endl;
  }

  //print_extra(extra_res_roc_cal_trig);
  if(found_res_roc_cal_trig){
	std::cout << readable(res_roc_cal_trig) << " Reset ROC, Cal Trigger" << std::endl;
  }
  else{
	std::cout << "No Reset ROC, Cal Trigger Found" << std::endl;
  }

  //print_extra(extra_stack_count);
  if(found_stack_count){
	std::cout << readable(stack_count) << " Stack Count" << std::endl;
  }
  else{
	std::cout << "No Stack Count Found" << std::endl;
  }

  //std::cout << bin_line.substr(cur_pos, cur_end-cur_pos) << " Idle Pattern 2" << std::endl;
  
  std::cout << extra_post << " Idle Pattern 2" << std::endl;

  std::cout << "END" << std::endl;  

  return 1;
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
  std::string bin_lineA("");
  std::string bin_lineB("");
  int start_A = 0;
  int start_B = 0;

  while(getline(fin, line)){
    if(line[0] == '#'){
	if(start_A){
		start_B = 1;
	}
	else{
		start_A = 1;
	}
	continue;
    }
    if(line.length() < 6){
	continue;
    }

    //std::istringstream iss(line);

    line.erase(std::remove(line.begin(), line.end(),' '),line.end());

    if(start_A && !start_B){
    	bin_lineA += line.substr(line.find('=')+1);
    }
    if(start_B){
    	bin_lineB += line.substr(line.find('=')+1);
    }
  }
  fin.close();

  coreparse("Core A", bin_lineA);
  coreparse("Core B", bin_lineB);
}


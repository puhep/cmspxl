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

  extra = haystack.substr(cur_pos, found-cur_pos);

  cur_pos += extra.length();
  cur_pos += needle.length();

  return 1;
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

int main(int argc, char** argv) {
  if (argc < 2) {
    print_usage() ;  
    return 1; 
  }

  std::string header("011111111100");
  std::string trailer("011111111110");
  std::string event_num("00000100");
  std::string cal_mode("10110000");
  std::string roc("011111111000");
  std::string res_roc_cal_trig("0010001000");
  std::string stack_count("000000");


  std::string inputFile(argv[1]); 
  std::ifstream fin;
  fin.open(inputFile.c_str());

  if (!fin.good()) 
    return 1;

  std::string line;
  std::string bin_line("");
  int line_num = 0;

  while(getline(fin, line))   {
    if(line_num == 0){
	line_num++;
	continue;
    }
    std::istringstream iss(line);
    bin_line += line.substr(5);

    line_num++; 
  }
  fin.close();

  int cur_pos = 0;
  
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

  int found_header = parse(cur_pos, extra_pre, header, bin_line);
  int found_ev_num = parse(cur_pos, extra_ev_num, event_num, bin_line);
  int found_cal_mode = parse(cur_pos, extra_cal_mode, cal_mode, bin_line);
  int found_roc0 = parse(cur_pos, extra_roc0, roc, bin_line);
  int found_roc1 = parse(cur_pos, extra_roc1, roc, bin_line);
  int found_roc2 = parse(cur_pos, extra_roc2, roc, bin_line);
  int found_roc3 = parse(cur_pos, extra_roc3, roc, bin_line);
  int found_roc4 = parse(cur_pos, extra_roc4, roc, bin_line);
  int found_roc5 = parse(cur_pos, extra_roc5, roc, bin_line);
  int found_roc6 = parse(cur_pos, extra_roc6, roc, bin_line);
  int found_roc7 = parse(cur_pos, extra_roc7, roc, bin_line);
  int found_trailer = parse(cur_pos, extra_trailer, trailer, bin_line);
  int found_res_roc_cal_trig = parse(cur_pos, extra_res_roc_cal_trig, res_roc_cal_trig, bin_line);
  int found_stack_count = parse(cur_pos, extra_stack_count, stack_count, bin_line);
  
  if(cur_pos < bin_line.length()){
  extra_post = bin_line.substr(cur_pos);
  }

  std::cout << "Input: " << bin_line << std::endl;

  std::cout << "Parse: " << std::endl;

  std::cout << extra_pre << " Idle Pattern" << std::endl;
  if(found_header){
	std::cout << header << " TBM Header" << std::endl;
  }
  else{
	std::cout << "No TBM Header Found" << std::endl;
  }
 
  print_extra(extra_ev_num);
  if(found_ev_num){
	std::cout << event_num  << " Event Number" << std::endl;
  }
  else{
	std::cout << "No Event Number Found" << std::endl;
  }
  print_extra(extra_cal_mode);
  if(found_cal_mode){
	std::cout << cal_mode << " Calibration Mode" << std::endl;
  }
  else{
	std::cout << "No Calibration Mode Found" << std::endl;
  }

  print_extra(extra_roc0);
  if(found_roc0){
	std::cout << roc << " ROC0" << std::endl;
  }
  else{
	std::cout << "No ROC0 Found" << std::endl;
  }

  print_extra(extra_roc1);
  if(found_roc1){
	std::cout << roc << " ROC1" << std::endl;
  }
  else{
	std::cout << "No ROC1 Found" << std::endl;
  }

  print_extra(extra_roc2);
  if(found_roc2){
	std::cout << roc << " ROC2" << std::endl;
  }
  else{
	std::cout << "No ROC2 Found" << std::endl;
  }

  print_extra(extra_roc3);
  if(found_roc3){
	std::cout << roc << " ROC3" << std::endl;
  }
  else{
	std::cout << "No ROC3 Found" << std::endl;
  }

  print_extra(extra_roc4);
  if(found_roc4){
	std::cout << roc << " ROC4" << std::endl;
  }
  else{
	std::cout << "No ROC4 Found" << std::endl;
  }

  print_extra(extra_roc5);
  if(found_roc5){
	std::cout << roc << " ROC5" << std::endl;
  }
  else{
	std::cout << "No ROC5 Found" << std::endl;
  }

  print_extra(extra_roc6);
  if(found_roc6){
	std::cout << roc << " ROC6" << std::endl;
  }
  else{
	std::cout << "No ROC6 Found" << std::endl;
  }

  print_extra(extra_roc7);
  if(found_roc7){
	std::cout << roc << " ROC7" << std::endl;
  }
  else{
	std::cout << "No ROC7 Found" << std::endl;
  }

  print_extra(extra_trailer);
  if(found_trailer){
	std::cout << roc << " TBM Trailer" << std::endl;
  }
  else{
	std::cout << "No TBM Trailer Found" << std::endl;
  }

  print_extra(extra_res_roc_cal_trig);
  if(found_res_roc_cal_trig){
	std::cout << res_roc_cal_trig << " Reset ROC, Cal Trigger" << std::endl;
  }
  else{
	std::cout << "No Reset ROC, Cal Trigger Found" << std::endl;
  }

  print_extra(extra_stack_count);
  if(found_stack_count){
	std::cout << stack_count << " Stack Count" << std::endl;
  }
  else{
	std::cout << "No Stack Count Found" << std::endl;
  }

  std::cout << extra_post << " Idle Pattern" << std::endl;

  std::cout << "END" << std::endl;  
}



#pragma once

#include <iostream> 
#include <fstream> 
#include <string> 
#include <ctype.h> 
#include <time.h> 
using namespace std;

enum Error_code {
	success, fail, utility_range_error, underflow, overflow, fatal, not_present,
	duplicate_error, entry_inserted, entry_found, internal_error, range_error
};



const char* return_error_message(Error_code code);

bool user_says_yes();

void initialize(int& end_time, int& queue_limit,
	double& arrival_rate, double& departure_rate);

void run_idle(int time);

int get_command();
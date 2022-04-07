#include "utility.h"
#include <iostream> 
using namespace std;



const char* error_messages[] = { "success", "fail", "utility_range_error", "underflow", "overflow", "fatal", "not_present",
"duplicate_error", "entry_inserted", "entry_found", "internal_error" };

bool user_says_yes() {
	int c;
	bool initial_response = true;

	do { // Loop until an appropriate input is received. 
		if (initial_response)
			cout << " (y,n)? " << flush;
		else
			cout << "Respond with either y or n: " << flush;

		do { // Ignore white space. 
			c = cin.get();
		} while (c == '\n' || c == ' ' || c == '\t');

		initial_response = false;
	} while (c != 'y' && c != 'Y' && c != 'n' && c != 'N');

	return (c == 'y' || c == 'Y');
}

const char* return_error_message(Error_code code)
{
	return error_messages[(int)code];
}


void initialize(int& end_time, int& queue_limit,
    double& arrival_rate, double& departure_rate)
    /*
    Pre:  The user specifies the number of time units in the simulation,
          the maximal queue sizes permitted,
          and the expected arrival and departure rates for the airport.
    Post: The program prints instructions and initializes the parameters
          end_time, queue_limit, arrival_rate, and departure_rate to
          the specified values.
    Uses: utility function user_says_yes
    */

{
    cout << "This program simulates an airport with only one runway." << endl
        << "One plane can land or depart in each unit of time." << endl;
    cout << "Up to what number of planes can be waiting to land "
        << "or take off at any time? " << flush;
    cin >> queue_limit;

    cout << "How many units of time will the simulation run? " << flush;
    cin >> end_time;

    bool acceptable;
    do {
        cout << "Expected number of arrivals per unit time? " << flush;
        cin >> arrival_rate;
        cout << "Expected number of departures per unit time? " << flush;
        cin >> departure_rate;
        if (arrival_rate < 0.0 || departure_rate < 0.0)
            cerr << "These rates must be nonnegative. " << endl;
        else
            acceptable = true;

        if (acceptable && arrival_rate + departure_rate > 1.0)
            cerr << "Safety Warning: This airport will become saturated. " << endl;

    } while (!acceptable);
}

void run_idle(int time)
/*
Post: The specified time is printed with a message that the runway is idle.
*/
{
    cout << time << ": Runway is idle." << endl;
}

int get_command() {

    bool waiting=true;
    int command;
    cout << endl;
    cout << "Select command and press <Enter>: ";

    while (waiting) {

        cin>> command;

        if (command == 1 || command == 2 || command == 3 || command == 4 || command == 5 || command == 0) {
            waiting = false;
        }
        else {
            cout << "Give command '1' is for 1 point program." << endl;
            cout << "'2' is for 1 point program." << endl;
            cout << "'3' is for 2 point program." << endl;
            cout << "'4' is for 3 point program." << endl;
            cout << "'5' is for 4 point program." << endl;
            cout << "'0' is for closing the program." << endl;
        }
    }

    return command;
}
#include<iostream>

#include"main_1.h"
#include"main_2.h"
#include"main_3.h"
#include"main_4.h"
#include"main_5.h"
#include"Utility.h"

using namespace std;

int main()     //  Airport simulation program
/*
Pre:  The user must supply the number of time intervals the simulation is to
      run, the expected number of planes arriving, the expected number
      of planes departing per time interval, and the
      maximum allowed size for runway queues.
Post: The program performs a random simulation of the airport, showing
      the status of the runway at each time interval, and prints out a
      summary of airport operation at the conclusion.
Uses: Classes Runway, Plane, Random and functions run_idle, initialize.
*/

{

    cout << "Give command '1' is for 1 point program." << endl;
    cout << "'2' is for 1 point program." << endl;
    cout << "'3' is for 1 point program." << endl;
    cout << "'4' is for 1 point program." << endl;
    cout << "'5' is for 1 point program." << endl;
    cout << "'0' is for closing the program." << endl;


    int a = get_command();
    while (a != 0) {
        switch (a) {
        case 1:
            main_1();
            break;
        case 2:
            main_2();
            break;
        case 3:
            main_3();
            break;
        case 4:
            main_4();
            break;
        case 5:
            main_5();
            break;
        }

        a = get_command();
    }



}
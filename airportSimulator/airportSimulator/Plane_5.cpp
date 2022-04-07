#include "Plane_5.h"


using namespace std;


Plane_5::Plane_5(int flt, int aTime, Plane_status status)
/*
Post:  The Plane data members flt_num, clock_start,
       and state are set to the values of the parameters flt,
       time and status, respectively.
*/

{
    fuel = -1;
    flt_num = flt;
    clock_start = aTime;
    state = status;
    cout << "Plane number " << flt << " ready to ";
    if (status == arriving) {
        cout << "land." << endl;
    }
    else
        cout << "take off." << endl;
}

Plane_5::Plane_5(int flt, int aTime, Plane_status status, int aFuel)
{
    fuel = -1;
    flt_num = flt;
    clock_start = aTime;
    state = status;
    cout << "Plane number " << flt << " ready to ";
    if (status == arriving) {
        cout << "land." << endl;
        fuel = aFuel;

    }
    else
        cout << "take off." << endl;
}

Plane_5::Plane_5()
/*
Post:  The Plane data members flt_num, clock_start,
       state and fuel are set to illegal default values.
*/
{
    flt_num = -1;
    clock_start = -1;
    state = null;
    fuel = -1; 
}

void Plane_5::refuse() const
/*
Post: Processes a Plane wanting to use Runway, when
      the Queue is full.
*/

{
    cout << "Plane number " << flt_num;
    if (state == arriving)
        cout << " directed to another airport" << endl;
    else
        cout << " told to try to takeoff again later" << endl;
}


void Plane_5::land(int time) const
/*
Post: Processes a Plane that is landing at the specified time.
*/

{
    int wait = time - clock_start;
    cout << time << ": Plane number " << flt_num << " landed after "
        << wait << " time unit" << ((wait == 1) ? "" : "s")
        << " in the takeoff queue." << endl;
}


void Plane_5::fly(int time) const
/*
Post: Process a Plane that is taking off at the specified time.
*/

{
    int wait = time - clock_start;
    cout << time << ": Plane number " << flt_num << " took off after "
        << wait << " time unit" << ((wait == 1) ? "" : "s")
        << " in the takeoff queue." << endl;
}


int Plane_5::started() const
/*
Post: Return the time that the Plane entered the airport system.
*/
{
    return clock_start;
}

int Plane_5::fuel_on_arrival()
{
    return fuel;
}

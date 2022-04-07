#include "main_5.h"
#include<iostream>
#include"RANDOM.H"
#include"Plane_5.h"
#include"Runway_5.h"





using namespace std;

void main_5()
{
    int max_fuel = 10;

    int end_time;            //  time to run simulation
    int queue_limit;         //  size of Runway queues
    int flight_number = 0,fuel;
    double arrival_rate, departure_rate;
    initialize(end_time, queue_limit, arrival_rate, departure_rate);
    Random variable;
    Runway_5 small_airport(queue_limit);
    for (int current_time = 0; current_time < end_time; current_time++) { //  loop over time intervals
        int number_arrivals = variable.poisson(arrival_rate);  //  current arrival requests
        for (int i = 0; i < number_arrivals; i++) {
            fuel = variable.random_integer(1,max_fuel);

            Plane_5 current_plane(flight_number++, current_time, arriving,fuel);
            
            if (current_plane.fuel_on_arrival() == 1)
                small_airport.emergency(current_plane);

            if (small_airport.can_land(current_plane) != success) {
                small_airport.makes_to_next_airport(current_time, current_plane);
                current_plane.refuse();
            }
        }

        int number_departures = variable.poisson(departure_rate); //  current departure requests
        for (int j = 0; j < number_departures; j++) {
            Plane_5 current_plane(flight_number++, current_time, departing);
            if (small_airport.can_depart(current_plane) != success)
                current_plane.refuse();
        }


        Plane_5 moving_plane;
        if (small_airport.emergency_landing(current_time,moving_plane)) {
            moving_plane.land(current_time);

        }
        else {
            switch (small_airport.activity(current_time, moving_plane)) {
                //  Let at most one Plane onto the Runway at current_time.
            case land:
                moving_plane.land(current_time);
                break;
            case takeoff:
                moving_plane.fly(current_time);
                break;
            case idle:
                run_idle(current_time);
            }
        }
    }
    cout << endl;
    small_airport.shut_down(end_time);
}

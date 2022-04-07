#include "main_4.h"
#include<iostream>
#include"RANDOM.H"
#include"Plane.h"
#include"Runway_4.h"


using std::cout;

void main_4()
{



    int end_time;            //  time to run simulation
    int queue_limit;         //  size of Runway queues
    int flight_number = 0;
    double arrival_rate, departure_rate;
    initialize(end_time, queue_limit, arrival_rate, departure_rate);
    Random variable;
    Runway_4 runway_1(queue_limit),runway_2(queue_limit),runway_3(queue_limit);
    Runway_4 total(queue_limit);
    for (int current_time = 0; current_time < end_time; current_time++) { //  loop over time intervals
        int number_arrivals = variable.poisson(arrival_rate);  //  current arrival requests
        for (int i = 0; i < number_arrivals; i++) {
            Plane current_plane(flight_number++, current_time, arriving);
            if (runway_1.can_land(current_plane) != success)
                current_plane.refuse();
        }

        int number_departures = variable.poisson(departure_rate); //  current departure requests
        for (int j = 0; j < number_departures; j++) {
            Plane current_plane(flight_number++, current_time, departing);
            if (runway_2.can_depart(current_plane) != success)
                current_plane.refuse();
        }

        Plane moving_plane;
        switch (runway_1.landing(current_time,moving_plane)) {

        case land:
            moving_plane.land(current_time);
            break;
        case idle:
            run_idle(current_time);
            break;
        }

        switch (runway_2.takingoff(current_time, moving_plane)) {

        case takeoff:
            moving_plane.fly(current_time);
            break;
        case idle:
            run_idle(current_time);
            break;
        }

        if (!runway_1.landing_queue_empty()) {
            Plane movePlane;
            runway_1.take_from_landing(movePlane);
            runway_3.can_land(movePlane);
        }
        else if(!runway_2.takeoff_queue_empty()) {
            Plane movePlane;
            runway_2.take_from_takeoff(movePlane);
            runway_3.can_depart(movePlane);
        }
        switch (runway_3.activity(current_time, moving_plane)) {
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
    cout << endl;

    cout << "The activity on runway 1, that has only landings happening on it." << endl;
    runway_1.shut_down(end_time);

    cout << "The activity on runway 2, that has only takeoffs happening on it." << endl;
    runway_2.shut_down(end_time);

    cout << "The activity on runway 3, that took landings if there were planes in the landing queue " << endl;
    cout << "and if there were no planes in landing queue it took takeoffs if in queue." << endl;
    runway_3.shut_down(end_time);
      
    

    cout << "Activity for the whole airport" << endl;
    total.combine(runway_1);
    total.combine(runway_2);
    total.combine(runway_3);
    total.shut_down(end_time);


}

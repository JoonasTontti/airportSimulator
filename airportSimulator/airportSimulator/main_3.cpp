#include "main_3.h"
#include"Runway_3.h"
#include"RANDOM.H"

using std::cout;

void main_3()
{
    int end_time;            //  time to run simulation
    int queue_limit;         //  size of Runway queues
    int flight_number = 0;
    double arrival_rate, departure_rate;
    initialize(end_time, queue_limit, arrival_rate, departure_rate);
    Random variable;
    Runway_3 landing_runway(queue_limit);
    Runway_3 takingoff_runway(queue_limit);
    Runway_3 total(queue_limit);
    for (int current_time = 0; current_time < end_time; current_time++) { //  loop over time intervals
        int number_arrivals = variable.poisson(arrival_rate);  //  current arrival requests
        for (int i = 0; i < number_arrivals; i++) {
            Plane current_plane(flight_number++, current_time, arriving);
            if (landing_runway.landing_full()) {
                if (takingoff_runway.can_land(current_plane) != success)
                    current_plane.refuse();
            }
            else {
                if (landing_runway.can_land(current_plane) != success)
                    current_plane.refuse();
            }
        }

        int number_departures = variable.poisson(departure_rate); //  current departure requests
        for (int j = 0; j < number_departures; j++) {
            Plane current_plane(flight_number++, current_time, departing);
            if (takingoff_runway.can_depart(current_plane) != success)
                current_plane.refuse();
        }

        Plane moving_plane;
        if ((landing_runway.no_activity()==true) && (takingoff_runway.no_activity()==false))
        {
            Plane movePlane;
            takingoff_runway.take_from_takeoff(movePlane);
            landing_runway.can_depart(movePlane);

        }
      
        switch (landing_runway.activity(current_time, moving_plane)) {
            //  Let at most one Plane onto a landing Runway at current_time.
        case land:
            moving_plane.land(current_time);
            break;
        case takeoff:
            moving_plane.fly(current_time);
            break;
        case idle:
            run_idle(current_time);
        }
        

        if ((landing_runway.no_activity() == false) && (takingoff_runway.no_activity() == true))
        {
            Plane movePlane;
            landing_runway.take_from_landing(movePlane);
            takingoff_runway.can_land(movePlane);

        }

        switch (takingoff_runway.activity(current_time, moving_plane)) {
            //  Let at most one Plane onto a take off Runway at current_time.
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

    cout << "Activity for runway 1 which was used for landing primarily." << endl;
    landing_runway.shut_down(end_time);

    cout << "Activity for runway 2 which was used for takeoffs primarily." << endl;
    takingoff_runway.shut_down(end_time);

    cout << "Activity for the whole airport" << endl;
    total.combine(takingoff_runway);
    total.combine(landing_runway);
    total.shut_down(end_time);

}

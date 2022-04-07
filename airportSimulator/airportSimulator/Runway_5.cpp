#include "Runway_5.h"




Runway_5::Runway_5(int limit)
/*
Post:  The Runway data members are initialized to record no
       prior Runway use and to record the limit on queue sizes.
*/

{
    queue_limit = limit;
    num_land_requests = num_takeoff_requests = 0;
    num_landings = num_takeoffs = 0;
    num_land_refused = num_takeoff_refused = 0;
    num_land_accepted = num_takeoff_accepted = 0;
    land_wait = takeoff_wait = idle_time = 0;
    fallen_planes = 0;
}


Error_code Runway_5::can_land(const Plane_5& current)
/*
Post:  If possible, the Plane current is added to the
       landing Queue; otherwise, an Error_code of overflow is
       returned. The Runway statistics are updated.
Uses:  class Extended_queue.
*/

{
    Error_code result;
    if (mLanding.size() < queue_limit)
        result = mLanding.append(current);
    else
        result = fail;
    num_land_requests++;

    if (result != success) 
        num_land_refused++;
    else
        num_land_accepted++;

    return result;
}


Error_code Runway_5::can_depart(const Plane_5& current)
/*
Post:  If possible, the Plane current is added to the
       takeoff Queue; otherwise, an Error_code of overflow is
       returned. The Runway statistics are updated.
Uses:  class Extended_queue.
*/

{
    Error_code result;
    if (mTakeoff.size() < queue_limit)
        result = mTakeoff.append(current);
    else
        result = fail;
    num_takeoff_requests++;
    if (result != success)
        num_takeoff_refused++;
    else
        num_takeoff_accepted++;

    return result;
}


Runway_activity Runway_5::activity(int time, Plane_5& moving)
/*
Post:  If the landing Queue has entries, its front
       Plane is copied to the parameter moving
       and a result  land is returned. Otherwise,
       if the takeoff Queue has entries, its front
       Plane is copied to the parameter moving
       and a result  takeoff is returned. Otherwise,
       idle is returned. Runway statistics are updated.
Uses:  class Extended_queue.
*/

{
    Runway_activity in_progress;
    if (!mLanding.empty()) {
        mLanding.retrieve(moving);

        if (!enough_fuel_landing(time, moving)) {

            in_progress = fall;
        }
        else {
            land_wait += time - moving.started();
            num_landings++;
            in_progress = land;
        }

        mLanding.serve();
        
    }

    else if (!mTakeoff.empty()) {
        mTakeoff.retrieve(moving);
        takeoff_wait += time - moving.started();
        num_takeoffs++;
        in_progress = takeoff;
        mTakeoff.serve();
    }

    else {
        idle_time++;
        in_progress = idle;
    }
    return in_progress;
}


void Runway_5::shut_down(int time) const
/*
Post: Runway usage statistics are summarized and printed.
*/

{
    cout << endl;
    cout << "Simulation has concluded after " << time << " time units." << endl
        << "Total number of planes processed "
        << (num_land_requests + num_takeoff_requests) << endl
        << "Total number of planes asking to land "
        << num_land_requests << endl
        << "Total number of planes asking to take off "
        << num_takeoff_requests << endl
        << "Total number of planes accepted for landing "
        << num_land_accepted << endl
        << "Total number of planes accepted for takeoff "
        << num_takeoff_accepted << endl
        << "Total number of planes refused for landing "
        << num_land_refused << endl
        << "Total number of planes refused for takeoff "
        << num_takeoff_refused << endl
        << "Total number of planes that landed "
        << num_landings << endl
        << "Total number of planes that took off "
        << num_takeoffs << endl
        << "Total number of planes left in landing queue "
        << mLanding.size() << endl
        << "Total number of planes left in takeoff queue "
        << mTakeoff.size() << endl;
    cout << "Percentage of time runway idle "
        << 100.0 * ((float)idle_time) / ((float)time) << "%" << endl;
    cout << "Average wait in landing queue "
        << ((float)land_wait) / ((float)num_landings) << " time units";
    cout << endl << "Average wait in takeoff queue "
        << ((float)takeoff_wait) / ((float)num_takeoffs)
        << " time units" << endl;
    cout << "Average observed rate of planes wanting to land "
        << ((float)num_land_requests) / ((float)time)
        << " per time unit" << endl;
    cout << "Average observed rate of planes wanting to take off "
        << ((float)num_takeoff_requests) / ((float)time)
        << " per time unit" << endl;
    cout << "Amount of planes that have fallen "
        << fallen_planes << endl;
    cout << endl;
}

bool Runway_5::enough_fuel_landing(int time, Plane_5& current)
{
    bool status;
    if ((current.fuel_on_arrival()-(time - current.started()))<1 ) {
        status = false;
        fallen_planes++;

    }
    else {
        status = true;
    }

    return status;
}

bool Runway_5::emergency_landing(int time, Plane_5& landing)
{
    bool status;
    if (!mEmegencyLanding.empty()) {
        mEmegencyLanding.retrieve(landing);
        land_wait += time - landing.started();
        num_landings++;
        status = true;
        mEmegencyLanding.serve();
    }
    else {
        status = false;
    }

    return status;
}

bool Runway_5::makes_to_next_airport(int time, Plane_5& fly)
{
    bool status;
    if (fly.fuel_on_arrival()>fual_to_closest_aiport) {

        status = true;
    }
    else {
        fallen_planes++;

        status = false;
    }

    return status;
}

void Runway_5::emergency(Plane_5& current)
{

    mEmegencyLanding.append(current);

}


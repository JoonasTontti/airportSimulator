#include "Runway_3.h"



Runway_3::Runway_3(int limit)
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
}


Error_code Runway_3::can_land(const Plane& current)
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


Error_code Runway_3::can_depart(const Plane& current)
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


Runway_activity Runway_3::activity(int time, Plane& moving)
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
        land_wait += time - moving.started();
        num_landings++;
        in_progress = land;
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


void Runway_3::shut_down(int time) const
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
    cout << endl;
}

bool Runway_3::no_activity()
{

    bool noActivity = false;

    if (mTakeoff.empty() && mLanding.empty())
        noActivity = true;


    return noActivity;
}

bool Runway_3::landing_full()
{
    bool result = true;

    if (mLanding.size() < queue_limit)
        result = false;

    return result;
}

bool Runway_3::takeoff_full()
{
    bool result = true;

    if (mTakeoff.size() < queue_limit)
        result = false;

    return result;
}

Error_code Runway_3::take_from_takeoff( Plane& movePlane)
{
    Error_code result;


    if (mTakeoff.empty())
        result = underflow;

    else {
        result = mTakeoff.serve_and_retrieve(movePlane);
        num_takeoff_accepted--;
        num_takeoff_requests--;
    }

    return result;
}

Error_code Runway_3::take_from_landing(Plane& movePlane)
{
    Error_code result;

    if (mLanding.empty())
        result = underflow;

    else {
        result = mLanding.serve_and_retrieve(movePlane);
        num_land_accepted--;
        num_land_requests--;
    }

    return Error_code();
}


void Runway_3::combine(Runway_3& add)
{
    Extended_queue landing = add.get_landing();
    Plane b, c;
    while (!landing.empty()) {
        landing.serve_and_retrieve(b);
        mLanding.append(b);

    }
    Extended_queue takeoff = add.get_takeoff();
    while (!takeoff.empty()) {

        takeoff.serve_and_retrieve(c);
        mTakeoff.append(c);
    }
    num_land_requests = num_land_requests + add.get_land_requests();
    num_takeoff_requests = num_takeoff_requests + add.get_takeoff_requests();
    num_landings = num_landings + add.get_landings();
    num_takeoffs = num_takeoffs + add.get_takeoffs();
    num_land_accepted = num_land_accepted + add.get_landing_accepted();
    num_takeoff_accepted = num_takeoff_accepted + add.get_takeoff_accepted();
    num_land_refused = num_land_refused + add.get_landing_refused();
    num_takeoff_refused = num_takeoff_refused + add.get_takeoff_refused();
    land_wait = land_wait + add.get_landing_waiting();
    takeoff_wait = takeoff_wait + add.get_takeoff_waiting();
    idle_time = idle_time + add.get_idle_time();

}

Extended_queue Runway_3::get_landing()
{
    return mLanding;
}

Extended_queue Runway_3::get_takeoff()
{
    return mTakeoff;
}

int Runway_3::get_land_requests()
{
    return num_land_requests;
}

int Runway_3::get_takeoff_requests()
{
    return num_takeoff_requests;
}

int Runway_3::get_landings()
{
    return num_landings;
}

int Runway_3::get_takeoffs()
{
    return num_takeoffs;
}

int Runway_3::get_landing_accepted()
{
    return num_land_accepted;
}

int Runway_3::get_takeoff_accepted()
{
    return num_takeoff_accepted;
}

int Runway_3::get_landing_refused()
{
    return num_land_refused;
}

int Runway_3::get_takeoff_refused()
{
    return num_takeoff_refused;
}

int Runway_3::get_landing_waiting()
{
    return land_wait;
}

int Runway_3::get_takeoff_waiting()
{
    return takeoff_wait;
}

int Runway_3::get_idle_time()
{
    return idle_time;
}

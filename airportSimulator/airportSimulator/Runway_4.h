#pragma once
#include"Utility.h"
#include"Plane.h"
#include"extended_queue.h"

enum Runway_activity { idle, land, takeoff };

class Runway_4 {
public:
	Runway_4(int limit);
	Error_code can_land(const Plane& current);
	Error_code can_depart(const Plane& current);
	Runway_activity activity(int time, Plane& moving);
	void shut_down(int time) const;

	bool landing_queue_empty();
	bool takeoff_queue_empty();

	Runway_activity landing(int time,Plane& moving);
	Runway_activity takingoff(int time,Plane& moving);


	Error_code take_from_takeoff(Plane& movePlane);
	Error_code take_from_landing(Plane& movePlane);

	void combine(Runway_4& combine);
	Extended_queue get_landing();
	Extended_queue get_takeoff();
	int get_land_requests();
	int get_takeoff_requests();
	int get_landings();
	int get_takeoffs();
	int get_landing_accepted();
	int get_takeoff_accepted();
	int get_landing_refused();
	int get_takeoff_refused();
	int get_landing_waiting();
	int get_takeoff_waiting();
	int get_idle_time();


private:
	Extended_queue mLanding;
	Extended_queue mTakeoff;
	int queue_limit;
	int num_land_requests;        //  number of planes asking to land
	int num_takeoff_requests;     //  number of planes asking to take off
	int num_landings;             //  number of planes that have landed
	int num_takeoffs;             //  number of planes that have taken off
	int num_land_accepted;        //  number of planes queued to land
	int num_takeoff_accepted;     //  number of planes queued to take off
	int num_land_refused;         //  number of landing planes refused
	int num_takeoff_refused;      //  number of departing planes refused
	int land_wait;                //  total time of planes waiting to land
	int takeoff_wait;             //  total time of planes waiting to take off
	int idle_time;                //  total time runway is idle
};


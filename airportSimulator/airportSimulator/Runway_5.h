#pragma once
#include"Utility.h"
#include"Plane_5.h"
#include"extended_queue_5.h"

enum Runway_activity { idle, land, takeoff, fall };


class Runway_5 {
public:
	Runway_5(int limit);
	Error_code can_land(const Plane_5& current);
	Error_code can_depart(const Plane_5& current);
	Runway_activity activity(int time, Plane_5& moving);
	void shut_down(int time) const;

	bool enough_fuel_landing(int time,Plane_5& current);
	bool emergency_landing(int time, Plane_5& landing);

	bool makes_to_next_airport(int time,Plane_5& fly);

	void emergency(Plane_5& current);



private:
	Extended_queue_5 mLanding;
	Extended_queue_5 mTakeoff;

	Extended_queue_5 mEmegencyLanding;

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

	int fallen_planes;
	int fual_to_closest_aiport = 5;
};

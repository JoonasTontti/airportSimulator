#pragma once
#include"Utility.h"

enum Plane_status { null, arriving, departing };

class Plane_5 {
public:
	Plane_5();
	Plane_5(int flt, int time, Plane_status status);
	Plane_5(int flt, int time, Plane_status status,int fuel);

	void refuse() const;
	void land(int time) const;
	void fly(int time) const;
	int started() const;
	int fuel_on_arrival();

private:
	int flt_num;
	int clock_start;
	Plane_status state;
	int fuel;
};
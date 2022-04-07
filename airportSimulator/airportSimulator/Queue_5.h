#pragma once
#include"Plane_5.h"
#include "utility.h"
#include<iostream>

// Section 3.3:

typedef Plane_5 Queue_entry;

const int maxqueue = 100; //  small value for testing

class Queue_5 {
public:
	Queue_5();
	bool empty() const;
	Error_code serve();
	Error_code append(const Queue_entry& item);
	Error_code retrieve(Queue_entry& item) const;

protected:
	int count;
	int front, rear;
	Queue_entry entry[maxqueue];
};

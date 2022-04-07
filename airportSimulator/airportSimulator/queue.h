#pragma once
#include"Plane.h"
#include "utility.h"
#include<iostream>

// Section 3.3:

typedef Plane Queue_entry;

const int maxqueue = 100; //  small value for testing

class Queue {
public:
   Queue();
   bool empty() const;
   Error_code serve();
   Error_code append(const Queue_entry &item);
   Error_code retrieve(Queue_entry &item) const;

protected:
   int count;
   int front, rear;
   Queue_entry entry[maxqueue];
};

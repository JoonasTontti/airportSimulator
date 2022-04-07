#pragma once

#include "Queue_5.h"

class Extended_queue_5 : public Queue_5 {
public:
	bool full() const;
	int size() const;
	void clear();
	Error_code serve_and_retrieve(Queue_entry& item);

	//void print();
};

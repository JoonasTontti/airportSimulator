#include "extended_queue_5.h"
#include<iostream>
using namespace std;

int Extended_queue_5::size() const
/*
Post:   Return the number of entries in the Extended_queue.
*/
{
	return count;
}

bool Extended_queue_5::full() const
{
	return maxqueue == this->count;
}

void Extended_queue_5::clear()
{
	this->count = 0;
	this->front = 0;
	this->rear = maxqueue - 1;
}

Error_code Extended_queue_5::serve_and_retrieve(Queue_entry& item)
{
	if (count <= 0) return underflow;
	item = entry[front];
	count--;
	front = ((front + 1) == maxqueue) ? 0 : (front + 1);
	return success;
}

/*
void Extended_queue::print()
{
	for ( int i = 0, j = front;
	i < this -> count; i++, j = ( ( j + 1 ) == maxqueue ) ? 0 : ( j + 1 ) )
		cout << this->entry[ j ] << ' ';

	cout << endl;

}
*/
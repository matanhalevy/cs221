#ifndef _ARRAYQUEUE_CPP
#define _ARRAYQUEUE_CPP

//ArrayQueue.cpp

#include "ArrayQueue.hpp"
#include <cstdlib> //for NULL
#include <cassert>
#include <iostream>
using namespace std;

// 221 STUDENTS:
//
// This skeleton file (along with the .hpp) is
// here to help get you started, but you are
// free to change function signatures, etc.
// as long as ArrayQueue is some subtype
// of BagOfPuzzleStates
ArrayQueue::ArrayQueue() : front(0), back(0)
{
  // Constructor: initialize member variables
  //              and do any other initialization
  //              needed (if any)
  // TODO: implement constructor
	array = new PuzzleState*[INIT_SIZE];
	capacity = INIT_SIZE;

}

void ArrayQueue::add(PuzzleState *elem)
{
  // TODO: uncomment parameter name (commented out so you don't get a warning)
  // TODO: implement add method
	ensure_capacity(back + 1);
	array[back] = elem;
	back++;
}

PuzzleState *ArrayQueue::remove()
{
  // TODO: implement remove method
  assert(!is_empty());
  PuzzleState *x = array[front];
  front++;
  return x;
}

bool ArrayQueue::is_empty()
{
	return front == back;
}

// TODO: implement ensure_capacity (but leave this to last.. just start with lots of capacity!)
void ArrayQueue::ensure_capacity(int n)
{
	if (capacity < n) {
		// Make plenty of room.

		int target_capacity = (n > 2 * capacity + 1) ? n : (2 * capacity + 1); /* TODO: the larger of n and twice the current capacity */;

		// TODO: Set the current array aside and make room for the new one.
		PuzzleState **oldarray = array;
		array = new PuzzleState*[target_capacity];

		// TODO: Copy each element of the old array over.
		// Update front carefully as you go!  Can you just use front++?
		for (int i = 0; i < back; i++) {
			array[i] = oldarray[front + i];
			int x = i + 1;

			// TODO: Fix front and back and capacity so they correspond to the new array.
			capacity = target_capacity;
			front = 0;
			back = x;



			// TODO: Delete the old array.
			delete[] oldarray;
		}
	}

}

ArrayQueue::~ArrayQueue()
{
  // TODO: implement the destructor

  // do any cleanup like deallocating
  // any dynamically allocated memory

	delete[] array;
}

#endif

//HeapPriorityQueue.cpp
#ifndef _HEAPPRIORITYQUEUE_CPP
#define _HEAPPRIORITYQUEUE_CPP

#include "HeapPriorityQueue.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>

HeapPriorityQueue::HeapPriorityQueue() {
	// blank
}

HeapPriorityQueue::~HeapPriorityQueue() {
	// blank
}

void HeapPriorityQueue::add(PuzzleState *elem) {
	if (is_empty())
		heap.push_back(elem);
	else {
		heap.push_back(elem);
		switch_up(heap.size() - 1);
	}
}

PuzzleState * HeapPriorityQueue::remove() {
	assert(heap.size() > 0);
	PuzzleState *returnVal = heap.front();
	heap[0] = heap.at(heap.size() - 1);
	heap.pop_back();
	switch_down(0);
	return returnVal;
}

void HeapPriorityQueue::switch_up(long unsigned int index){
	if (index < 1) // do not switch if element is @ root node.
		return;
	
	if (heap[index]->getBadness() < heap[parent(index)]->getBadness()){
		PuzzleState *temp = heap[index];
		heap[index] = heap[parent(index)];
		heap[parent(index)] = temp;
		switch_up(parent(index));
	}
}

void HeapPriorityQueue::switch_down(long unsigned int index){
	long unsigned int leftChild = (2 * index) + 1;
	long unsigned int rightChild = (2 * index) + 2;
	long unsigned int min = index;

	if (leftChild < heap.size() && heap[leftChild]->getBadness() < heap[min]->getBadness())
		min = leftChild;
	if (rightChild < heap.size() && heap[rightChild]->getBadness() < heap[min]->getBadness())
		min = rightChild;

	if (min != index) {
		PuzzleState* temp = heap[index];
		heap[index] = heap[min];
		heap[min] = temp;
		switch_down(min);
	}
}

long unsigned int HeapPriorityQueue::parent(long unsigned int index){
	if (index != 0){
		return (index - 1) >> 1;
	}
	return -1;
}

PuzzleState *HeapPriorityQueue::get_next() {
	if (heap.size() < 1) return NULL;
	return heap.at(0);
}

bool HeapPriorityQueue::is_empty() {
	return (heap.size() == 0);
}

#endif
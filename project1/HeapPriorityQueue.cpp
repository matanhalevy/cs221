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
  heap.push_back(elem);
  switch_up(index);
}

PuzzleState * HeapPriorityQueue::remove() {
  assert(size() > 0);
  PuzzleState *returnVal = heap[0];
  heap[0] = heap.pop_back();
  switch_down(0);
  return returnVal;
}

int HeapPriorityQueue::switch_up(int index){
	if(is_root(index)) // do not switch if element is @ root node.
		return index;
	int parent = parent(index); //switches up until condition no longer holds
	if(heap[index]->value < heap[parent]->value){
		PuzzleState *temp = heap[index];
		heap[index] = heap[parent];
		heap[parent] = temp;
		return switch_up(parent);
	}

	return index;
}

int HeapPriorityQueue::switch_down(int index){
	if(is_leaf(index))
		return index;
	int rightChild = right_child(index);
	int leftChild = left_child(index);
	switch_index = index;
	if(heap[index]->value >=heap[leftChild]->value)
		switch_index = leftChild;
	if(num_children(index) == 2) {
		if(heap[switch_index]->value >=heap[rightChild]->value)
			switch_index = rightChild;
	}
	if(switch_index != index){ //switch until children > parent.
		PuzzleState *temp = heap[index];
		heap[index] = heap[switch_index];
		head[switch_index] = temp;
		return switch_down(switch_index);
	}
	return index;
}

int HeapPriorityQueue::parent(int index){
	return int(floor((index-1)/2));
}

int HeapPriorityQueue::num_children(int index){
	int amt_children = 0;
	if (left_child(index) < size())
		amt_children++
	if (right_child(index) < size())
		amt_children++
	return children;
}

int HeapPriorityQueue::is_root(int index){
	if (index==1)
		return true;
	else return false;
}

int HeapPriorityQueue::is_leaf(int index){
	if (num_children(index) == 0)
		return true;
	else return false;
}

int HeapPriorityQueue::size(){
	return int(heap.size());
}

PuzzleState *HeapPriorityQueue::get_next() {
  if (size() < 1)
  	return NULL;
  return heap[1];
}

bool HeapPriorityQueue::is_empty() {
  return (heap.size() == 0);
}

#endif

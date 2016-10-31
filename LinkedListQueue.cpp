//LinkedListQueue.cpp
#ifndef _LINKEDLISTQUEUE_CPP
#define _LINKEDLISTQUEUE_CPP

#include "LinkedListQueue.hpp"
#include <cstdlib> //for NULL
#include <cassert>
#include <iostream>
LinkedListQueue::LinkedListQueue()
{
	head = NULL;
	tail = NULL;
}

void LinkedListQueue::add(PuzzleState *elem)
{
		node * temp = new node;
		temp->data = elem;
		temp->next = NULL;
		if (!head) head = temp;
		else tail->next = temp;
		tail = temp;
		size++;
}

PuzzleState *LinkedListQueue::remove()
{
	assert(!is_empty());
	PuzzleState *return_data = head->data;
	node* temp = head;
	head = head->next;
	delete temp;
	size--;
	return return_data;
	
}

bool LinkedListQueue::is_empty()
{
	return size == 0;
}

LinkedListQueue::~LinkedListQueue()
{
	while (head != NULL)
		remove();

}

#endif


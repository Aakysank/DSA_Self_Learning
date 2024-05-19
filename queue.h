#pragma once
#include "linkedlist.h"

class Queue
{
	singleLinkedList q;
public:
	Queue(): q()
	{
		
	}

	~Queue()
	{
		removeAll();
	}

	void removeAll() { q.removeAll(); }

	void enqueue(int data)
	{
		q.insertAtTail(data);
	}

	int dequeue()
	{
		q.deleteAt(0);
	}

	int size() { return q.size(); }
};
#pragma once
#include "linkedlist.h"

class SingleSideQueue
{
	singleLinkedList q;
public:
	SingleSideQueue(): q()
	{
		
	}

	~SingleSideQueue()
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

	int front()
	{
		return q.get(0);
	}

	int size() { return q.size(); }
};
#pragma once
//Hashing -- Implemented hashing using open hashing (separate chaining method)
#include "linkedlist.h"

class Hashing
{
	singleLinkedList Hash[10];
	
	//Using modulo function as hash function
	int hash(int key)
	{
		return key % 10;
	}

public:
	Hashing()
	{

	}

	~Hashing() {}

	void insert(int key)
	{
		int index = hash(key);
		Hash[index].insertSorted(key);
	}

	int search(int key)
	{
		int index = hash(key);
		
		int x = -1;
		for (int i = 0; i < Hash[index].size(); i++)
		{
			if (Hash[index].get(i) < key)
			{
			}
			else if (Hash[index].get(i) > key)
				return x;
			else
				return key;
		}
		
		return x;
	}

	int DeleteKey(int key)
	{
		int index = hash(key);

		int x = -1;
		for (int i = 0; i < Hash[index].size(); i++)
		{
			if (Hash[index].get(i) < key)
			{
			}
			else if (Hash[index].get(i) > key)
				return x;
			else
				x = Hash[index].deleteAt(i);
		}

		return x;
	}
};
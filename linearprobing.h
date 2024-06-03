#pragma once
#include<memory>
int SIZE = 10;
class HashLinearProbing
{
private:
	int H[10];

	int hash(int key)
	{
		return key % 10;
	}

	int probe(int key)
	{
		int index = hash(key);
		int i = 0;
		while (H[(index + i) % SIZE] != 0)
			i++;

		return (index + i) % SIZE;
	}

public:
	HashLinearProbing() { memset(H, 0, sizeof(int) * 10); }
	~HashLinearProbing() {}
	void insert(int key)
	{
		int index = hash(key);
		if (H[index] != 0)
			index = probe(key);

		H[index] = key;
	}

	int search(int key)
	{
		int index = hash(key);
		if (H[index] != key)
		{
			int i = index;
			while (H[i%SIZE] != key)
				i++;

			return i % SIZE;
		}
	}
};
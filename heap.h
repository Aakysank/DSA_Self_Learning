#pragma once
#include <limits>
#include <vector>

using namespace std;
class Heap
{
	int* _Heap_Root;
	int _capacity;
	int _size;
public:
	Heap(int size)
	{
		_Heap_Root = new int[size];
		for (int i = 0; i < size; i++)
			_Heap_Root[i] = INT_MIN;

		_capacity = size;
		_size = 0;
	}

	~Heap()
	{
		delete[] _Heap_Root;

		_size = 0;
		_capacity = 0;
	}

	void InsertInHeap(int num)
	{
		int index = _size, parent_index = 0;
		_Heap_Root[index] = num;

		if (index % 2 == 0)
			parent_index = (index - 2) / 2;
		else
			parent_index = (index - 1) / 2;

		while (index > 0 && _Heap_Root[parent_index] < _Heap_Root[index])
		{
			int temp = _Heap_Root[parent_index];
			
			_Heap_Root[parent_index] = _Heap_Root[index];
			_Heap_Root[index] = temp;
			
			index = parent_index;

			if (parent_index % 2 == 0)
				parent_index = (parent_index - 2) / 2;
			else
				parent_index = (parent_index - 1) / 2;
		}

		_size++;
	}

	void getHeapData(std::vector<int>& data)
	{
		data.reserve(_size);
		for (int i = 0; i < _size; i++)
			data.emplace_back(_Heap_Root[i]);
	}

	int Delete()
	{
		int x = _Heap_Root[0];
		_Heap_Root[0] = _Heap_Root[_size-1];
		_Heap_Root[_size - 1] = x;
		_size--;

		int cur_ind = 0;
		while (cur_ind < _size-1)
		{
			int lchild_index = (2 * cur_ind) + 1, rchild_index = (2 * cur_ind) + 2;
			int j = lchild_index;
		
			if (lchild_index >= _size && rchild_index >= _size)
				break;

			if (lchild_index < _size && rchild_index < _size)
			{
				if (_Heap_Root[lchild_index] < _Heap_Root[rchild_index])
					j = rchild_index;
			}

			if (j < _size && _Heap_Root[cur_ind] < _Heap_Root[j])
			{
				int temp = _Heap_Root[j];
				_Heap_Root[j] = _Heap_Root[cur_ind];
				_Heap_Root[cur_ind] = temp;

				cur_ind = j;
			}
			else
				break;
		}

		return x;
	}
};
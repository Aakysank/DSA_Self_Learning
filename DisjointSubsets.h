#pragma once
//Disjoint subsets are data structures that are used to detect cycles in a graph
//This is used in creating spanning tree in kruskal's algorithm, for skipping the edges
//that try to form cycle. (as spanning trees are acyclic graph/subgraph with n vertices and n-1 edges.
class DisJointSubset
{
	int _size;
	int* DJS;

public:
	DisJointSubset(int size)
	{
		_size = size;
		DJS = new int[_size];
		
		for (int i = 0; i < _size; i++)
			DJS[i] = -1;//Initialize all the items to -1
	}

	~DisJointSubset()
	{
		delete[] DJS;
	}

	void weightedUnion(int u, int v)
	{
		if (DJS[u] < DJS[v])
		{
			DJS[u] += DJS[v];
			DJS[v] = u;
		}
		else
		{
			DJS[v] += DJS[u];
			DJS[u] = v;
		}
	}

	int collapsingFind(int u)
	{
		int x = u;
		while (DJS[x] > 0)
			x = DJS[x];

		return x;
	}
};
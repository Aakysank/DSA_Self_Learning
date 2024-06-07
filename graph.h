#pragma once
#include <iostream>
#include "queue.h"
#include "stack.h"

class Graph
{
	int G_Adjacency_Matrix[7][7];
    bool dfsVisited[7];
public:
	Graph()
	{
        int G[7][7] = { {0,0,0,0,0,0,0},
                 {0,0,1,1,0,0,0},
                 {0,1,0,0,1,0,0},
                 {0,1,0,0,1,0,0},
                 {0,0,1,1,0,1,1},
                 {0,0,0,0,1,0,0},
                 {0,0,0,0,1,0,0} };

        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 7; j++)
                G_Adjacency_Matrix[i][j] = G[i][j];
        }

        memset(dfsVisited, false, sizeof(bool) * 7);
	}

    void BFS(int start)
    {
        if (start < 1 && start > 6)
            return;

        bool visited[7] = { false };
        SingleSideQueue q;
        
        q.enqueue(start);
        std::cout << start << "\t";
        visited[start] = true;

        while (q.size() != 0)
        {
            int u = q.front();
            q.dequeue();
            for (int v = 1; v < 7; v++)
            {
                if (G_Adjacency_Matrix[u][v] == 1 && visited[v] == false)
                {
                    std::cout << v << "\t";
                    visited[v] = 1;
                    q.enqueue(v);
                }
            }
        }
    }

    void DFS(int start)
    {
        if (start < 1 && start > 6)
            return;

        if (dfsVisited[start] == false)
        {
            std::cout << start << "\t";
            dfsVisited[start] = true;
            for (int j = 1; j < 7; j++)
            {
                if (G_Adjacency_Matrix[start][j] == 1 && dfsVisited[j] == false)
                {
                    DFS(j);
                }
            }
        }
    }


};

class PrimsSpanningTree
{
    int G[8][8];
    int near_array[8];
    int treeEdges[2][6];
   
    void CreateSpanningTree()
    {
        //First find the minimum cost edge,
        //Traverse the lower triangular matrix- because matrix is symmetric
        //For n vertices, there will be n-1 edges in case of spanning tree.
        ///In case of Prims algorithm, the spanning tree is constructed
        //by selecting the minimum cost edge and then growing the spanning tree 
        //from this selected edge having vertices-- finding the next minimums
        int minCostEdge = INT_MAX, u = 0, v = 0;
        for (int i = 1; i < 8; i++)
        {
            for (int j = 1; j < 8; j++)
            {
                if (i > j)
                    continue;

                if (G[i][j] < minCostEdge)
                {
                    minCostEdge = G[i][j];
                    u = i;
                    v = j;
                }
            }
        }

        //after finding the minimum cost edge -- set the flags of the
        //associated index in near array to 0, with near array we are going to
        //find the rest of the edges.
        near_array[u] = 0;
        near_array[v] = 0;
        
        //First edge
        treeEdges[0][0] = u, treeEdges[1][0] = v;
        
        //updating the near array, based on the first edge.
        for (int i = 1; i < 8; i++)
        {
            if (near_array[i] == 0)
                continue;

            if (G[i][u] < G[i][v])
                near_array[i] = u;
            else
                near_array[i] = v;
        }

        //Finding other edges.
        for (int i = 1; i < 6; i++)
        {
            int minCostEdge = INT_MAX, k = 0;
            //Finding the next minimumCost edge
            for (int j = 1; j < 8; j++)
            {
                if (near_array[j] == 0)
                    continue;

                if (G[j][near_array[j]] < minCostEdge)
                {
                    minCostEdge = G[j][near_array[j]];
                    k = j;//Storing the new vertex in k
                }
            }

            treeEdges[0][i] = k;
            treeEdges[1][i] = near_array[k];

            near_array[k] = 0;

            for (int j = 1; j < 8; j++)
            {
                if (near_array[j] == 0)
                    continue;

                if (G[j][k] < G[j][near_array[j]])
                {
                    near_array[j] = k;
                }
            }

        }
    }

public:
    PrimsSpanningTree()
    {
        //used adjacency matrix (2D array) to represent the graph
        // graph looks like this 
        
                        //    1
                        //  /   \
                        //6       2
                        // \    / |
                        //  5--7  |
                        //   \    |
                        //    4---3

        //The cost of edge connecting 1 to 6 is 5, 1 to 2 is 25 and so on
        //This is what is represented in the adjacency matrix.
        int g[8][8] = {
            {INT_MAX, INT_MAX ,INT_MAX ,INT_MAX ,INT_MAX ,INT_MAX, INT_MAX,INT_MAX },
            {INT_MAX, INT_MAX ,25 ,INT_MAX ,INT_MAX ,INT_MAX ,5, INT_MAX },
            {INT_MAX, 25 ,INT_MAX ,17 ,INT_MAX ,INT_MAX ,INT_MAX, 16 },
            {INT_MAX, INT_MAX,17,INT_MAX ,10 ,INT_MAX ,INT_MAX,INT_MAX },
            {INT_MAX, INT_MAX,INT_MAX,17 ,INT_MAX ,12 ,INT_MAX,14 },
            {INT_MAX, INT_MAX,INT_MAX,INT_MAX,12 ,INT_MAX,20,18 },
            {INT_MAX, 5,INT_MAX,INT_MAX, INT_MAX ,20,INT_MAX,INT_MAX },
            {INT_MAX, INT_MAX,16,INT_MAX, 14 ,18,INT_MAX,INT_MAX }
        };

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                G[i][j] = g[i][j];
            }
        }

        for (int i = 0; i < 8; i++)
        {
            near_array[i] = INT_MAX;
        }

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 7; j++)
                treeEdges[i][j] = 0;
        }

        CreateSpanningTree();
    }
    
    void getSpanningTree(int treeData[2][6])
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 6; j++)
                treeData[i][j] = treeEdges[i][j];
        }
    }
};
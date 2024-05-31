// SelfLearningDataStructures.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "linkedlist.h"
#include "doublylinkedlist.h"
#include "queue.h"
#include "stack.h"
#include "binarysearchtree.h"
#include "heap.h"

using namespace std;


int main(int argc, char** argv)
{
    std::cout << "Running unit test for datastructures developed from scratch" << std::endl;
    testing::InitGoogleTest(&argc, argv);

    int b[] = { 10, 20, 30, 25, 5, 40, 35 };
    std::vector<int> heapData;
    Heap h(7);

    for (int i = 0; i < 7; i++)
        h.InsertInHeap(b[i]);

    h.getHeapData(heapData);
    for (auto data : heapData)
    {
        std::cout << data << "\t";
    }

    std::cout << std::endl;

    for (int i = 0; i < 7; i++)
        std::cout << h.Delete() << "\t";

    std::cout << std::endl;

    TreeNode* pMyBST = NULL;
    CreateBinaryTree(&pMyBST);
    isBalanced(pMyBST);

    return RUN_ALL_TESTS();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

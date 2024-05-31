#pragma once
#include<deque>
struct TreeNode
{
	int data;
	TreeNode* left;
	TreeNode* right;
};

void CreateBinaryTree(TreeNode** root)
{
	if (!root)
		return;

	TreeNode* start = NULL;

	std::deque<TreeNode*> BinaryTreeNodeQueue;
	int val = -1;

	std::cout << "Enter the value for the root node ";
	std::cin >> val;

	if (val != -1)
	{
		start = new TreeNode;
		start->left = NULL;
		start->right = NULL;

		start->data = val;
	}

	BinaryTreeNodeQueue.push_front(start);

	while (BinaryTreeNodeQueue.size() != 0)
	{
		TreeNode* n = BinaryTreeNodeQueue.front();
		BinaryTreeNodeQueue.pop_front();

		if (n)
		{
			int val = -1;
			std::cout << "Enter the value for the left child of " << n->data << " node ";
			std::cin >> val;

			if (val != -1)
			{
				TreeNode* l = NULL;
				l = new TreeNode;
				l->left = NULL;
				l->right = NULL;

				l->data = val;

				n->left = l;

				BinaryTreeNodeQueue.push_back(l);
			}

			std::cout << "Enter the value for the right child of " << n->data << " node ";
			std::cin >> val;

			if (val != -1)
			{
				TreeNode* r = NULL;
				r = new TreeNode;
				r->left = NULL;
				r->right = NULL;

				r->data = val;

				n->right = r;

				BinaryTreeNodeQueue.push_back(r);
			}
		}
	}

	*root = start;
	return;
}
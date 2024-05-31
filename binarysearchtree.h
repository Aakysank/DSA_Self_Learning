#pragma once
#include<gtest/gtest.h>
#include "binarytree.h"
#include <stack>
#include <vector>

using namespace std;

enum class NODE_TYPES
{
	ALL_NODES,
	DEGREE_ONE_NODES,
	DEGREE_TWO_NODES,
	LEAF_NODES
};

int DegreeTwoNodeCount(TreeNode* t)
{
	int x = 0, y = 0;

	x = DegreeTwoNodeCount(t->left);
	y = DegreeTwoNodeCount(t->right);

	if (t->left && t->right)
		return x + y + 1;
	else
		return x + y;
}

int DegreeOneNodeCount(TreeNode *t)
{
	int x = 0, y = 0;

	x = DegreeOneNodeCount(t->left);
	y = DegreeOneNodeCount(t->right);

	if (!t->left ^ !t->right)
		return x + y + 1;
	else
		return x + y;
}

int leafNodeCount(TreeNode* t)
{
	int x = 0, y = 0;

	x = leafNodeCount(t->left);
	y = leafNodeCount(t->right);

	if (!t->left && !t->right)
		return x + y + 1;
	else
		return x + y;
}

int getTreeHeight(TreeNode *t)
{
	int lsh = 0, rsh = 0;
	lsh = getTreeHeight(t->left);
	rsh = getTreeHeight(t->right);

	if (lsh > rsh)
		return lsh + 1;
	else
		return rsh + 1;
}
class BST
{
	TreeNode* root;
	int node_count;
	int height;
public:
	BST()
	{
		root = NULL;
		height = 0;
		node_count = 0;
	}

	~BST()
	{

	}

	TreeNode* getRoot() { return root; }

	int getCount(NODE_TYPES eNodeType)
	{
		if (eNodeType == NODE_TYPES::ALL_NODES)
			return node_count;
		else if (eNodeType == NODE_TYPES::DEGREE_TWO_NODES)
			return DegreeTwoNodeCount(root);
		else if (eNodeType == NODE_TYPES::DEGREE_ONE_NODES)
			return DegreeOneNodeCount(root);
		else if (eNodeType == NODE_TYPES::LEAF_NODES)
			return leafNodeCount(root);
	}
	
	int getHeight() { return getTreeHeight(root); }

	void insert(int data)
	{
		TreeNode* p = root, *q = NULL;
		while (p != NULL)
		{
			q = p;
			if (data < p->data)
				p = p->left;
			else
				p = p->right;
		}

		TreeNode* t = new TreeNode;
		t->data = data;
		t->right = NULL;
		t->left = NULL;

		if (q)
		{
			if (data < q->data)
				q->left = t;
			else
				q->right = t;
		}
		else
			root = t;

		node_count++;
	}

	bool search(int data)
	{
		TreeNode* p = root;
		while (p != NULL)
		{
			if (data == p->data)
				return true;

			if (data < p->data)
				p = p->left;
			else
				p = p->right;
		}

		return false;
	}

	void preOrder(TreeNode* p, std::vector<int>& preOrderData)
	{
		if (!p)
			return;

		preOrderData.push_back(p->data);
		preOrder(p->left, preOrderData);
		preOrder(p->right, preOrderData);
	}

	void Inorder(TreeNode* p, std::vector<int>& inorderData)
	{
		if (!p)
			return;

		Inorder(p->left, inorderData);
		inorderData.push_back(p->data);
		Inorder(p->right, inorderData);
	}

	void PostOrder(TreeNode* p, std::vector<int>& postOrderData)
	{
		if (!p)
			return;


		PostOrder(p->left, postOrderData);
		PostOrder(p->right, postOrderData);
		postOrderData.push_back(p->data);
	}

	void levelOrder(TreeNode* p, std::vector<int>& levelOrderData)
	{
		if (!p)
			return;

		TreeNode* t = p;
		std::deque<TreeNode*> queue;

		queue.push_front(t);
		
		while (!queue.empty())
		{
			TreeNode* n = queue.front();
			queue.pop_front();

			if (n)
			{
				levelOrderData.push_back(n->data);

				queue.push_front(n->right);
				queue.push_front(n->left);
			}
		}
		return;
	}

	TreeNode* InOrderPre(TreeNode* p)
	{
		if (!p)
			return NULL;

		while (p && p->right)
			p = p->right;

		return p;
	}

	TreeNode* InOrderSucc(TreeNode* p)
	{
		if (!p)
			return NULL;

		while (p && p->left)
			p = p->left;

		return p;
	}

	TreeNode* Delete(TreeNode* p, int key)
	{
		if (!p)
			return NULL;

		if (!p->left && !p->right)
		{
			if (p == root)
				root = NULL;

			delete p;
			p = NULL;

			return NULL;
		}
		//Searching for the node happens
		if (key < p->data)
			p->left = Delete(p->left, key);
		else if (key > p->data)
			p->right = Delete(p->right, key);
		else
		{
			//If the node is found, take the inorder successor or inorder predecessor of the node
			//If the height on the left side of node is greater than right inorder sucessor is taken
			//If the height on the right side of node is greater or equal to left, inorder predecessor is taken
			//The value of the inorder sucessor/predecessor will be swapped with the current node
			//always the root node will be deleted.
			if (getTreeHeight(p->left) > getTreeHeight(p->right))
			{
				TreeNode* q = InOrderPre(p->left);
				p->data = q->data;

				p->left = Delete(p->left, q->data);
			}
			else
			{
				TreeNode* q = InOrderSucc(p->right);
				p->data = q->data;

				p->right = Delete(p->right, q->data);
			}
		}
		
		return p;
	}
};



//Formula- - left child of any parent index = 2*p + 1
//rchild parent index = 2*p+2

void FindCousins(int val, std::vector<int>& BinaryTreeToArray, std::vector<int>& Cousins)
{
	auto it = std::find(BinaryTreeToArray.begin(), BinaryTreeToArray.end(), val);

	if (it == BinaryTreeToArray.end())
	{
		std::cout << "The given value is not found in the binary tree" << std::endl;
		return;
	}

	int parent_index = 0, cousin_parent = 0, cousin_lchild = 0, cousin_rchild = 0;
	int index = it - BinaryTreeToArray.begin();

	if (index % 2 == 0)
		parent_index = (index - 2) / 2;
	else
		parent_index = (index - 1) / 2;

	if (parent_index < 0)
	{
		std::cout << "The given value doesnot have any cousins" << std::endl;
		return;
	}

	cousin_parent = parent_index + 1;
	cousin_lchild = cousin_parent * 2 + 1;
	cousin_rchild = cousin_parent * 2 + 2;

	if (cousin_lchild >= BinaryTreeToArray.size())
	{
	}
	else
		Cousins.push_back(BinaryTreeToArray[cousin_lchild]);

	if (cousin_rchild >= BinaryTreeToArray.size())
	{
	}
	else
		Cousins.push_back(BinaryTreeToArray[cousin_rchild]);

	return;
}

void ConvertBinaryTreeToArray(TreeNode *root, std::vector<int>& BinaryTreeArrayRep)
{
	if (!root)
		return;

	std::deque<TreeNode*> BinaryTreeNodeQueue;
	BinaryTreeNodeQueue.push_back(root);

	while (!BinaryTreeNodeQueue.empty())
	{
		TreeNode* n = BinaryTreeNodeQueue.front();
		BinaryTreeNodeQueue.pop_front();

		if (n)
		{
			BinaryTreeArrayRep.push_back(n->data);

			BinaryTreeNodeQueue.push_back(n->left);
			BinaryTreeNodeQueue.push_back(n->right);
		}
	}

	std::vector<int> Cousins;
	int findCousin = 0;
	
	std::cout << "Enter the node for which you need to find the cousin ";
	std::cin >> findCousin;

	FindCousins(findCousin, BinaryTreeArrayRep, Cousins);
	return;
}

void InOrderTraversal(TreeNode* root, std::vector<int>& inorderTaversalVect)
{
	if (!root)
		return;

	InOrderTraversal(root->left, inorderTaversalVect);
	inorderTaversalVect.push_back(root->data);
	InOrderTraversal(root->right, inorderTaversalVect);

	return;
}

void FindTriplets(TreeNode *root, vector<vector<int>>& ans)
{
	if (!root)
		return;

	std::vector<int> inorderTraversalVect;

	InOrderTraversal(root, inorderTraversalVect);
	if (inorderTraversalVect.empty())
		return;

	for (int i = 0; i < inorderTraversalVect.size(); i++)
	{
		int j = i + 1;
		int k = inorderTraversalVect.size()-1;

		while (j < k)
		{
			int x = inorderTraversalVect[i] + inorderTraversalVect[j] + inorderTraversalVect[k];

			if (x > 0)
				k--;
			else if (x < 0)
				j++;
			else
			{
				vector<int> triplet = { inorderTraversalVect[i], inorderTraversalVect[j], inorderTraversalVect[k] };
				j++;
				k++;

				ans.push_back(triplet);
			}
		}
	}
}

int height(TreeNode* root)
{
	if (!root)
		return 0;

	int lsh = 0, rsh = 0;

	lsh = height(root->left);
	rsh = height(root->right);

	if (lsh > rsh)
		return lsh + 1;
	else
		return rsh + 1;
}

int BalanceFactor(TreeNode* root)
{
	if (!root)
		return 0;

	int lsh = 0, rsh = 0;
	lsh = height(root->left);
	rsh = height(root->right);

	return lsh - rsh;
}

bool isBalanced(TreeNode* root) {

	if (!root)
		return true;

	if (BalanceFactor(root) == 1 || BalanceFactor(root) == 0 || BalanceFactor(root) == -1)
		return true;


	return false;

}


#pragma once
#include "binarytree.h"

class AVLTree
{
	TreeNode* root;
private:
	int height(TreeNode* p)
	{
		if (!p)
			return 0;

		int lsh = 0, rsh = 0;
		lsh = height(p->left);
		rsh = height(p->right);

		if (lsh > rsh)
			return lsh + 1;
		else
			return rsh + 1;
	}

	int BalanceFactor(TreeNode* p)
	{
		if (!p)
			return 0;

		int lsh = height(p->left);
		int rsh = height(p->right);

		return lsh - rsh;
	}

	TreeNode* getInOrderSuccessor(TreeNode* p)
	{
		TreeNode* t = p;
		while (t && t->left)
			t = t->left;
		
		return t;
	}

	TreeNode* getInorderPredecessor(TreeNode* p)
	{
		TreeNode* t = p;
		while (t && t->right)
			t = t->right;

		return t;
	}
	void LLRotation(TreeNode* p)
	{
		if (!p)
			return;

		TreeNode* t = p;
		TreeNode* tl = p->left;
		TreeNode* tll = tl->left;
		TreeNode* tlr = tl->right;

		p = p->left;
		p->right = t;
		p->left = tll;
		p->right->left = tlr;

		return;
	}

	void RRotation(TreeNode* p)
	{
		if (!p)
			return;

		TreeNode* t = p;
		TreeNode* tr = p->right;
		TreeNode* trl = p->right->left;

		p = p->right;
		p->left = t;
		p->left->right = trl;

		return;
	}

	void LRRotation(TreeNode* p)
	{
		if (!p)
			return;

		TreeNode* t = p;
		TreeNode* tl = p->left;
		TreeNode* tlr = tl->right;

		p = tlr;
		p->left = tl;
		p->left->right = tlr->left;

		p->right = t;
		p->right->left = tlr->right;
	}

	void RLRotation(TreeNode* p)
	{
		if (!p)
			return;

		TreeNode* t = p;
		TreeNode* tr = p->right;
		TreeNode* trl = p->right->left;

		p = trl;
		p->left = t;
		p->left->right = trl->left;

		p->right = tr;
		p->right->left = trl->right;
	}

	TreeNode* RInsert(TreeNode* p, int key)
	{
		if (!p)
		{
			TreeNode* t = new TreeNode;
			t->data = key;
			t->left = NULL;
			t->right = NULL;
			
			return t;
		}

		if (key < p->data)
			p->left = RInsert(p->left, key);
		else if (key > p->data)
			p->right = RInsert(p->right, key);

		if (BalanceFactor(p) == 2 && BalanceFactor(p->left) == 1)
			LLRotation(p);
		else if (BalanceFactor(p) == -2 && BalanceFactor(p->right) == -1)
			RRotation(p);
		else if (BalanceFactor(p) == 2 && BalanceFactor(p->left) == -1)
			LRRotation(p);
		else if (BalanceFactor(p) == -2 && BalanceFactor(p->right) == 1)
			RLRotation(p);

		return p;
	}

	TreeNode* RDelete(TreeNode* p, int key)
	{
		TreeNode* t = p;

		if (!t)
			return NULL;

		if (t->left == NULL && t->right == NULL)
		{
			if (key != t->data)
				return t;
			else
			{
				delete t;
				return NULL;
			}
		}
		if (key < t->data)
			t->left = RDelete(t->left, key);
		else if (key > t->data)
			t->right = RDelete(t->right, key);
		else
		{
			if (height(t->left) > height(t->right))
			{
				TreeNode* q = getInorderPredecessor(t->left);
				if (q)
					t->data = q->data;
				
				t->left = RDelete(t->left, q->data);
			}
			else
			{
				TreeNode* q = getInOrderSuccessor(t->right);
				if (q)
					t->data = q->data;

				t->right = RDelete(t->right, q->data);
			}
		}


		if (BalanceFactor(t) == 2 && BalanceFactor(t->left) == 1)
			LLRotation(t);
		else if (BalanceFactor(t) == -2 && BalanceFactor(t->right) == -1)
			RRotation(t);
		else if (BalanceFactor(t) == 2 && BalanceFactor(t->left) == -1)
			LRRotation(t);
		else if (BalanceFactor(t) == -2 && BalanceFactor(t->right) == 1)
			RLRotation(t);
		else if (BalanceFactor(t) == 2 && BalanceFactor(t->left) == 0)//L0 Rotation -- we can also do LR here
			LLRotation(t);
		else if (BalanceFactor(t) == -2 && BalanceFactor(t->right) == 0)//R0 Rotation - we can also do RL here
			RRotation(t);

		return t;
	}

public:
	AVLTree() { root = NULL; }
	~AVLTree()
	{

	}

	void insert(int key)
	{
		root = RInsert(root, key);
	}

	void Delete(int key)
	{
		root = RDelete(root, key);
	}

	int search(int key)
	{
		TreeNode* p = root;
		while (p != NULL)
		{
			if (key == p->data)
				return key;

			if (key < p->data)
				p = p->left;
			else if (key > p->data)
				p = p->right;
		}

		return -1;
	}
};
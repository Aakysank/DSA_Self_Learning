#pragma once
#include <string>
using namespace std;
struct TrieNode
{
	TrieNode* childNodes[26];
	bool end;

	TrieNode()
	{
		for (int i = 0; i < 26; i++)
			childNodes[i] = NULL;

		end = false;
	}
};

class Trie
{
	TrieNode* root;
public:

	Trie()
	{
		root = NULL;
	}

	void insert(string s)
	{
		if (root == NULL)
			root = new TrieNode;

		TrieNode* p = root;
		for (auto ch : s)
		{
			if (p->childNodes[ch - 'a'] == NULL)
				p->childNodes[ch - 'a'] = new TrieNode;

			p = p->childNodes[ch - 'a'];
		}

		p->end = 1;
	}

	bool search(string s)
	{
		if (root == NULL)
			return false;

		TrieNode* p = root;
		for (auto ch : s)
		{
			if (p->childNodes[ch - 'a'] == NULL)
				return false;

			p = p->childNodes[ch - 'a'];
		}

		return (p && p->end == true);
	}
};
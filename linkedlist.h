#pragma once
#include <gtest/gtest.h>
struct Node
{
	int data;
	Node* next;
};

class singleLinkedList
{
	Node* _head;
	int length;

public:
	singleLinkedList()
	{
		_head = NULL;
		length = 0;
	}

	~singleLinkedList()
	{
		removeAll();
	}
	void insertAtHead(int data)
	{
		Node* t = new Node;
		t->data = data;
		t->next = NULL;

		if (_head)
		{
			t->next = _head;
			_head = t;
		}
		else
			_head = t;

		length++;
	}

	void insertAtTail(int data)
	{
		Node* p = _head;
		Node* t = new Node;
		t->data = data;
		t->next = NULL;

		if (!p)
			_head = t;
		else
		{
			while (p && p->next)
				p = p->next;

			p->next = t;
		}

		length++;
	}

	void insertAt(int pos, int data)
	{
		if (pos >= length || pos < 0)
			return;

		Node* p = _head, *q = NULL;
		for (int i = 0; i < pos && p; i++)
		{
			q = p;
			p = p->next;
		}

		Node* t = new Node;
		t->data = data;

		if (q)
		{
			q->next = t;
			t->next = p;
		}

		length++;
	}

	int deleteAt(int pos)
	{
		int x = -1;
		if (pos - 1 >= length || pos < 0)
			return x;

		Node* p = _head, * q = NULL;
		for (int i = 0; i < pos && p; i++)
		{
			q = p;
			p = p->next;
		}

		if (q)
		{
			q->next = p->next;
			
			x = p->data;
			delete p;
			p = NULL;
		}
		else if (p && p == _head)
		{
			q = p->next;
			if (p)
				delete p;
			
			_head = q;
		}

		length--;
		return x;
	}

	void removeAll()
	{
		Node* p = _head;
		while (p != NULL)
		{
			Node *q = p;

			delete q;
			q = NULL;
			
			p = p->next;
			_head = p;
			length--;
		}
		
		if (_head)
		{
			delete _head;
			_head = NULL;
		}
	}

	void reverseLinks()
	{
		Node* p = _head, *q = NULL, *r = NULL;
		while (p != NULL)
		{
			r = q;
			q = p;

			p = p->next;

			if (q)
				q->next = r;

			if (p && p->next == NULL)
				_head = p;
		}
	}

	int get(int pos)
	{
		int x = -1;
		if (pos - 1 >= length || pos < 0)
			return x;

		Node* p = _head;
		for (int i = 0; i < pos && p; i++)
			p = p->next;

		if (p)
			return p->data;

		return x;
	}

	int size() { return length; }

	void insertSorted(int data)
	{
		
		Node* t = new Node;
		t->data = data;
		t->next = NULL;

		if (_head == NULL)
		{
			_head = t;
			length++;
			return;
		}
		else
		{
			Node* p = _head, *q = NULL;
			while (p != NULL && p->data < data)
			{
				q = p;
				p = p->next;
			}

			if (q)
			{
				Node* temp = q->next;
				q->next = t;
				t->next = temp;
			}
			else
			{
				q = t;
				q->next = _head;
				_head = q;
			}

		}

		length++;
	}
};

/*TEST(SingleLinkedListTest, InsertAtHeadTest)
{
	singleLinkedList slist;
	slist.insertAtHead(5);
	slist.insertAtHead(10);
	slist.insertAtHead(15);

	EXPECT_EQ(15, slist.get(0));
	EXPECT_EQ(10, slist.get(1));
	EXPECT_EQ(5, slist.get(2));
}

TEST(SingleLinkedListTest, InsertAtTailTest)
{
	singleLinkedList slist;
	slist.insertAtTail(5);
	slist.insertAtTail(10);
	slist.insertAtTail(15);

	EXPECT_EQ(5, slist.get(0));
	EXPECT_EQ(10, slist.get(1));
	EXPECT_EQ(15, slist.get(2));
}

TEST(SingleLinkedListTest, LengthTest)
{
	singleLinkedList slist;
	for (int i = 1; i <= 5; i++)
	{
		int val = 1 * 4;
		slist.insertAtTail(val);
	}

	EXPECT_EQ(5, slist.size());

	slist.deleteAt(0);
	EXPECT_EQ(4, slist.size());

	slist.removeAll();
	EXPECT_EQ(0, slist.size());
}

TEST(SingleLinkedListTest, ReversingLinks)
{
	int larray[4] = { 5, 10, 15, 20 };
	singleLinkedList slist;
	for (int i = 0; i < 4; i++)
		slist.insertAtTail(larray[i]);

	for (int i = 0; i < slist.size(); i++)
		EXPECT_EQ(larray[i], slist.get(i));

	slist.reverseLinks();
	for (int i = 0, j = slist.size()-1; i < slist.size(), j >= 0; i++, j--)
		EXPECT_EQ(larray[j], slist.get(i));
}
*/



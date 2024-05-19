#pragma once
#include<gtest/gtest.h>
struct DLLNode
{
	int data;
	DLLNode* next;
	DLLNode* prev;

	DLLNode()
	{
		data = -1;
		next = nullptr;
		prev = nullptr;
	}
};

class DLList
{
private:
	DLLNode* _head;
	int length;

public:
	DLList()
	{
		_head = nullptr;
		length = 0;
	}

	~DLList()
	{
		removeAll();
	}

	void insertAtHead(int data)
	{
		DLLNode* t = new DLLNode;
		t->prev = nullptr;
		t->data = data;
		t->next = nullptr;

		if (!_head)
			_head = t;
		else
		{
			t->next = _head;
			_head->prev = t;

			_head = t;
		}

		length++;
		return;
	}

	void insertAtTail(int data)
	{
		DLLNode* t = new DLLNode;
		t->prev = nullptr;
		t->data = data;
		t->next = nullptr;

		if (!_head)
			_head = t;
		else
		{
			DLLNode* p = _head;

			//Go to the last node of the list
			while (p && p->next)
				p = p->next;

			//do the double linking.
			p->next = t;
			t->prev = p;
		}

		length++;
	}

	void insertAtPos(int pos, int data)
	{
		if (pos >= length || pos < 0)
			return;

		DLLNode* p = _head;
		for (int i = 0; i < pos && p; i++)
			p = p->next;

		DLLNode* t = new DLLNode;
		t->prev = nullptr;
		t->data = data;
		t->next = nullptr;

		if (p)
		{
			DLLNode* q = p->prev;
			if (q)
				q->next = t;

			t->prev = q;
			t->next = p;
			p->prev = t;
		}

		length++;
	}

	int deleteAtPos(int pos)
	{
		int x = -1;
		if (pos >= length || pos < 0)
			return x;

		DLLNode* p = _head;
		for (int i = 0; i < pos && p; i++)
			p = p->next;

		if (p)
		{
			DLLNode* q = p->prev;
			DLLNode* n = p->next;

			if (q)
				q->next = n;
			
			n->prev = q;

			if (p == _head)
				_head = n;

			x = p->data;

			delete p;
			p = nullptr;
			
			length--;
			return x;
		}
	}

	int get(int pos)
	{
		int x = -1;
		if (pos >= length || pos < 0)
			return x;

		DLLNode* p = _head;
		for (int i = 0; i < pos && p; i++)
			p = p->next;

		if (p)
			x = p->data;

		return x;
	}

	void removeAll()
	{
		DLLNode* p = _head;
		while (p != nullptr)
		{
			DLLNode* q = p;

			delete q;
			q = nullptr;

			p = p->next;
			_head = p;
			length--;
		}

		if (_head)
		{
			delete _head;
			_head = nullptr;
		}
	}

	int size() { return length; }

	void reverseLinks()
	{
		DLLNode* p = _head, * q = NULL, *r = NULL;
		while (p != NULL)
		{
			r = q;
			q = p;
			p = p->next;

			if (q)
			{
				q->next = r;
				if (r)
					r->prev = q;

				q->prev = p;
			}

			if (p && p->next == NULL)
				_head = p;
		}

		return;
	}
};
TEST(DoublyLinkedList, InsertAtHeadTest)
{
	DLList dlist;
	dlist.insertAtHead(5);
	dlist.insertAtHead(10);
	dlist.insertAtHead(15);

	EXPECT_EQ(15, dlist.get(0));
	EXPECT_EQ(10, dlist.get(1));
	EXPECT_EQ(5, dlist.get(2));
}

TEST(DoublyLinkedList, InsertAtTailTest)
{
	DLList dlist;
	dlist.insertAtTail(5);
	dlist.insertAtTail(10);
	dlist.insertAtTail(15);

	EXPECT_EQ(5, dlist.get(0));
	EXPECT_EQ(10, dlist.get(1));
	EXPECT_EQ(15, dlist.get(2));
}

TEST(DoublyLinkedList, LengthTest)
{
	DLList dlist;
	for (int i = 1; i <= 5; i++)
	{
		int val = 1 * 4;
		dlist.insertAtTail(val);
	}

	EXPECT_EQ(5, dlist.size());

	dlist.deleteAtPos(0);
	EXPECT_EQ(4, dlist.size());

	dlist.removeAll();
	EXPECT_EQ(0, dlist.size());
}

TEST(DoublyLinkedList, ReversingLinks)
{
	int larray[4] = { 5, 10, 15, 20 };
	DLList dlist;
	for (int i = 0; i < 4; i++)
		dlist.insertAtTail(larray[i]);

	for (int i = 0; i < dlist.size(); i++)
		EXPECT_EQ(larray[i], dlist.get(i));

	dlist.reverseLinks();
	for (int i = 0, j = dlist.size() - 1; i < dlist.size(), j >= 0; i++, j--)
		EXPECT_EQ(larray[j], dlist.get(i));
}
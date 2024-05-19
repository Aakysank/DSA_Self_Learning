#pragma once
#include "linkedlist.h"
class Stack
{
private:
	singleLinkedList st;
public:
	Stack(): st(){

	}
	~Stack()
	{
		removeAll();
	}

	void push(int data){
		st.insertAtHead(data);
	}

	int top(){
		return st.get(0);
	}

	int pop(){
		return st.deleteAt(0);
	}

	int size() { return st.size(); }

	void removeAll() { st.removeAll(); }
};
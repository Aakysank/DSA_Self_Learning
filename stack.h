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

/*bool isValidParantheses(std::string parantheses)
{
	if (!parantheses.size())
		return false;

	Stack myStack;
	std::set<char> openBrackets = { '{', '(', '[' };
	for (int i = 0; i < parantheses.size(); i++)
	{
		if (openBrackets.find(parantheses[i]) != openBrackets.end())
			myStack.push(parantheses[i]);
		else
		{
			if (myStack.size() == 0)
				return false;

			if ((myStack.top() == '(' && parantheses[i] == ')')
				|| (myStack.top() == '{' && parantheses[i] == '}')
				|| (myStack.top() == '[' && parantheses[i] == ']'))
			{
				myStack.pop();
			}
			else
				return false;
		}
	}

	return true;
}
TEST(StackTest, ValidParanthesesTest)
{
	std::string parantheses1 = { "{())]}" }, parantheses2 = {"{()[]}"};
	EXPECT_TRUE(isValidParantheses(parantheses1) == false);
	EXPECT_TRUE(isValidParantheses(parantheses2) == true);
}*/
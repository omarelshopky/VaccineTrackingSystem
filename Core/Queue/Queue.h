#pragma once
template <class T>
class Queue
{
	T* arr;
	int count, capcity;
	int Front, Back;

public:
	Queue();
	int size();
	void push(T);
	void pop();
	T front();
	T back();
	bool empty();
	bool full();
	~Queue();
};



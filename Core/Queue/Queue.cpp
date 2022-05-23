#include "Queue.h"
//#include <iostream>
#include <assert.h>

template <class T>
Queue<T>::Queue()
{
	capcity = 5;
	count = 0;
	Front = Back = -1;
	arr = new T[capcity];
}

template <class T>
int Queue<T>::size()
{
	return count;
}

template <class T>
void Queue<T>::push(T val)
{
	assert(!full());
	if (count == 0)
		Front = 0;
	Back = (Back + 1) % capcity;
	arr[Back] = val;
	count++;
}

template <class T>
void Queue<T>::pop()
{
	assert(!empty());
	if (count == 1)
		Front = Back = -1;
	else
		Front = (Front + 1) % capcity;
	count--;
}

template <class T>
T Queue<T>::front()
{
	assert(!empty());
	return arr[Front];
} 

template <class T>
T Queue<T>::back()
{
	assert(!empty());
	return arr[Back];
}

template <class T>
bool Queue<T>::full()
{
	return (count == capcity);
}

template <class T>
bool Queue<T>::empty()
{
	return (count == 0);
}


template <class T>
Queue<T>::~Queue(void)
{
	delete[] arr;
}

#include "vector.h"
#include <assert.h>
#include <iostream>

template <class T>
vector<T>::vector()
{
	vectorSize = 5;
	arr = new T[vectorSize];
	count = 0;
}

template <class T>
int vector<T>::size()
{
	return count;
}

template <class T>
void vector<T>::push_back(T val)
{
	if (count == vectorSize)
		Expand();
	arr[count] = val;
	count++;
}

template <class T>
void vector<T>::Expand()
{
	vectorSize *= 2; //define new capacity
	T* tmp = new T[vectorSize];
	for (int i = 0; i < count; i++)
		tmp[i] = arr[i];
	delete arr; //release old space
	arr = tmp;
}

template <class T>
T vector<T>::At(int pos)
{
	assert(pos < count);
	return arr[pos];
}

template <class T>
void vector<T>::insertAt(int pos, T val)
{
	assert(pos < count);
	if (count == vectorSize)
		Expand();
	//shift elements to the right
	for (int i = count; i > pos; i--)
		arr[i] = arr[i - 1];
	//insert value at required position
	arr[pos] = val;
	count++;
}

template <class T>
void vector<T>::deleteAt(int pos)
{
	assert(pos < count);
	//shift elements to the left
	for (int i = pos; i < count - 1; i++)
		arr[i] = arr[i + 1];
	count--;
}

template <class T>
vector<T>::~vector(void)
{
	delete[] arr;
}

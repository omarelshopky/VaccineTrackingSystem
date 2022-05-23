#pragma once
template <class T>
class vector
{
	T* arr;
	int vectorSize, count;
public:
	vector();
	int size();
	void push_back(T);
	void Expand();
	T At(int);
	void insertAt(int, T);
	void deleteAt(int);
	~vector(void);
};


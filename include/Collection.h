#pragma once

#include<iostream>
#include<exception>

using namespace std;

template <class T>
class ICollection {
public:
	virtual void push(T v) = 0;
	virtual T pop() = 0;
	virtual bool isEmpty() = 0;
	virtual bool isFull() = 0;
};

template <class T>
class Queue: public ICollection<T> {
	T* pQueue;
	int n;
	int last, first;

	int next(int i);
public:
	Queue(int _n = 100);
	Queue(const Queue<T>& s);
	Queue<T>& operator=(const Queue<T>& s);

	void push(T v);
	T pop();
	bool isFull();
	bool isEmpty();
};


template <class T>
class Stack: public ICollection<T> {
	T* pStack;
	int n;
	int top;
public:
	Stack(int _n = 100);
	Stack(const Stack<T>& s);
	Stack<T>& operator=(const Stack<T>& s);

	void push(T v);
	T pop();
	bool isFull();
	bool isEmpty();
};


template <class T>
int Queue<T>::next(int i)
{
	return (i + 1) % n;
}

template <class T>
Queue<T>::Queue(int _n) :n(_n)
{
	pQueue = new T[n];
	first = 0;
	last = n - 1;
}

template <class T>
void Queue<T>::push(T v)
{
	if (isFull()){ throw logic_error("queue_overflow"); }
	last = next(last);
	pQueue[last] = v;
}

template <class T>
T Queue<T>::pop()
{
	if (isEmpty()) { throw logic_error("queue_is_empty"); }
	T v = pQueue[first];
	first = next(first);
	return v;
}

template <class T>
bool Queue<T>::isFull()
{
	return next(next(last)) == first;
}

template <class T>
bool Queue<T>::isEmpty()
{
	return next(last) == first;
}

template <class T>
Stack<T>::Stack(int _n): n(_n)
{
	if (_n < 0) throw logic_error("negative_number_of_elements");
	top = -1;
	pStack = new T[n];
}

template <class T>
Stack<T>::Stack(const Stack<T>& s)
{
	n = s.n;
	top = s.top;
	pStack = new T[n];
	for (int i = 0; i < n; i++)
	{
		pStack[i] = s.pStack[i];
	}
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& s)
{
	if (this == &s) return *this;
	delete[] pStack;
	n = s.n;
	pStack = new T[n];
	top = s.top;
	for (int i = 0; i <= top; i++)
	{
		pStack[i] = s.pStack[i];
	}
	return *this;
}

template <class T>
void Stack<T>::push(T v)
{
	if (isFull()) { throw logic_error("stack_overflow"); }
	else {
		top++;
		pStack[top] = v;
	}
}

template <class T>
T Stack<T>::pop()
{
	if (isEmpty()) { throw logic_error("stack_is_empty"); }
	T v;
	v = pStack[top];
	top--;
	return v;
}

template <class T>
bool Stack<T>::isFull()
{
	return (n - 1 == top);
}

template <class T>
bool Stack<T>::isEmpty()
{
	return (top == -1);
}
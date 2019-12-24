/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dsaLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DSALIB_H
#define DSA191_A1_DSALIB_H
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

class DSAException {
    int     _error;
    string  _text;
public:

    DSAException() : _error(0), _text("Success") {}
    DSAException(int err) : _error(err), _text("Unknown Error") {}
    DSAException(int err, const char* text) : _error(err), _text(text) {}

    int getError() { return _error; }
    string& getErrorText() { return _text; }
};

#pragma region Classes

template <class T>
struct L1Item {
    T data;
    L1Item<T> *pNext;
    L1Item() : pNext(NULL) {}
    L1Item(T &a) : data(a), pNext(NULL) {}
	L1Item(T& a, L1Item<T>* p) :data(a),pNext(p){}
};

template <class T>
class L1List {
    L1Item<T>   *_pHead,*_pTail;// The head pointer of linked list
    size_t      _size;// number of elements in this list
public:
    L1List() : _pHead(nullptr), _size(0),_pTail(nullptr){}
	~L1List() { clean();};

    void    clean()
	{
		while (_pHead)
		{
			L1Item<T>* p = _pHead;
			_pHead = _pHead->pNext;
			delete p;
		}
		_size = 0;
	}
    bool    isEmpty() {
        return _pHead == NULL;
    }
    size_t  getSize() {
        return _size;
    }

    T&      at(int i);// give the reference to the element i-th in the list
    T&      operator[](int i);// give the reference to the element i-th in the list

    bool    find(T& a, int& idx);// find an element similar to a in the list. Set the found index to idx, set idx to -1 if failed. Return true if success.
    int     insert(int i, T& a);// insert an element into the list at location i. Return 0 if success, -1 otherwise
    int     remove(int i);// remove an element at position i in the list. Return 0 if success, -1 otherwise.

    int     push_back(T& a);// insert to the end of the list
    int     insertHead(T& a);// insert to the beginning of the list

    int     removeHead();// remove the beginning element of the list
    int     removeLast();// remove the last element of the list

    void    reverse();

    void traverse(void (*op)(T&)) {
		L1Item<T>* curr = _pHead;
		while (curr)
		{
			op(curr->data);
			curr = curr->pNext;
		}
    }
    int  traverse(int (*op)(T&, void*&), void* &pParam) {
        // TODO: Your code goes here
		L1Item<T>* curr = _pHead;
		int* pOutput=new int[14000],outputSize=0;
		while (curr)
		{
			int temp=op(curr->data,pParam);
			if (temp != -1)
				pOutput[outputSize++] = temp;
			curr = curr->pNext;
		}
		//pOutput[0] = outputSize;
		delete[] pParam;
		pParam = pOutput;
		return outputSize;
    }
	string traverseFind(string (*op)(T&, void*&), void*& pParam) {
		L1Item<T>* curr = _pHead;
		string* pOutput = new string[10];
		while (curr) {
			string temp = op(curr->data, pParam);
			if (temp != "")return temp;
			curr = curr->pNext;
		}
		return "not found";
	}
	int  traverseFindPos(int (*op)(T&, void*&), void*& pParam) {
		L1Item<T>* curr = _pHead;
		int count=0;
		while (curr) {
			int temp = op(curr->data, pParam);
			if (temp != -1)return count;
			count++;
			curr = curr->pNext;
		}
		return -1;
	}
	int traverseFindMax(int (*op)(T&)) {
		L1Item<T>* p = _pHead;
		int maxID = 0,temp;
		while (p) {
			temp = op(p->data);
			if (maxID < temp)maxID = temp;
			p = p->pNext;
		}
		return maxID;
	}
};
#pragma endregion
template <class T>
int L1List<T>::push_back(T &a) {
	L1Item<T>* n =new L1Item<T>(a);	//allocate new node
	//L1Item<T>* curr;	
	if (_pHead)							//if the list has alredy have element
	{
		/*curr = _pHead;
		while (curr->pNext != NULL)
			curr = curr->pNext;
		curr->pNext = n;*/
		_pTail->pNext = n;
		_pTail = n;
		_size++;
		return 0;
	}
	_pHead = n;
	_pTail = _pHead;
	_size++;
    return 0;
}

/// Insert item to the front of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::insertHead(T &a) {
	L1Item<T>* n = new L1Item<T>(a);
	n->pNext = _pHead;
	_pHead = n;
	_pTail = _pHead;
	_size++;
    return 0;
}

/// Remove the first item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeHead() {
	if (_pHead) {
		L1Item<T>* p;
		p = _pHead;
		_pHead = p->pNext;
		delete p;
		_size--;
		return 0;
	}
    return -1;
}

/// Remove the last item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeLast() {
	if (_pHead) {
		L1Item<T>* pCurr=_pHead, * pPre=pCurr->pNext;
		while (pCurr->pNext) {
			pPre = pCurr;
			pCurr = pCurr->pNext;
		}
		pPre->pNext = NULL;
		_pTail = pPre;
		delete pCurr;
		_size--;
		return 0;
	}
    return -1;
}

template<class T>
T& L1List<T>::operator[](int i)
{
	L1Item<T>* p = _pHead;
	while (i) {
		p->pNext;
		i--;
	}
	return p->data;
}

template<class T>
bool   L1List<T>::find(T& a, int& idx)
{
	idx = 0;
	L1Item<T>* p = _pHead;
	while (p) {
		if (p->data == a)return true;
		p = p->pNext;
		idx++;
	}
	idx = -1;
	return false;
}

template<class T>
T& L1List<T>::at(int i) {
	L1Item<T>* p = _pHead;
	while (i > 0) {
		p->pNext;
		i--;
	}
	return p->data;
}

template<class T>
int L1List<T>::insert(int i, T& a) {
	if (i) {
		L1Item<T>* pPre = _pHead, * pCurr = pPre->pNext;
		while (i > 1 && pCurr)
		{
			pPre = pCurr;
			pCurr=pCurr->pNext;
			i--;
		}
		if (i == 1) {
			pPre->pNext = new L1Item<T>(a, pCurr);
			_size++;
			return 0;
		}
		return -1;
	}
	else _pHead->pNext = new L1Item<T>(a, _pHead);
	_size++;
	return 0;
}

template<class T>
int L1List<T>::remove(int i) {
	if (_size == 0) return -1;
	if (i)
	{
		L1Item<T>* pPre = _pHead, * pCurr = pPre->pNext;
		while (i > 1 && pCurr)
		{
			pPre = pCurr;
			pCurr = pCurr->pNext;
			i--;
		}
		if (pCurr) {
			pPre->pNext = pCurr->pNext;
			delete pCurr;
			_size--;
			return true;
		}
		return false;
	}

	L1Item<T>* p = _pHead;
	_pHead = _pHead->pNext;
	delete p;
	_size--;
	return 0;
}
#endif //DSA191_A1_DSALIB_H

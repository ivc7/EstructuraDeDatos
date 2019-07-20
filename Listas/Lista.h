#pragma once
#include<cstddef>
#include<iostream>

template<class  T>
class Lista{
private:
#include "Node.h"
public:
	Lista() :head(NULL) {}
	void push_front(const T& d);
	void print()const;
	void push_back(const T& d);
private:
	Node* head;

};
template<class T>
void Lista<T>::push_front(const T& d) {
	head = new Node(d,head);
}


template<class T>
void Lista<T>::print()const {
	Node* actual = head;
	while (actual != NULL) {
		std::cout << actual->dato << " ";
		actual = actual->next;
	}
}

template<class T>
void Lista<T>::push_back(const T& d){
	if (head == NULL)
		head = new Node(d);
	else
	{
		Node *ptrTmp = head;
		while (ptrTmp->next != NULL)
			ptrTmp = ptrTmp->next;
		ptrTmp->next = new Node(d);
	}
}

/*
 1)adicionar los demás métodos Lista
 (recursivamente).
 2) Implementar una lista que inserte los elementos
 ordenadamente
 3) implementar el constuctor de copia de la lista
 4) pila en base a lista
 5)cola en base a lista


*/









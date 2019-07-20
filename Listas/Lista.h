#pragma once
#include<cstddef>
#include<iostream>

template<class  T>
class Lista{
private:
#include "Node.h"
public:
	// Constructor copia:
  Lista(const Lista<T> &l);
	Lista() :head(NULL) {}
	void push_order(const T& d);
	void push_front(const T& d);
	void print()const;
	void push_back(const T& d);
public:
	Node* head;

};

/*Copy*/
template<class  T>
Lista<T>::Lista(const Lista<T> &l){
//std::cout<<"wiii";
//l.print();

	Node* origen = l.head;
	Node* destino = NULL;
	while (origen != NULL) {
		//std::cout << origen->dato << " ";
		destino=new Node(origen	->dato,destino);
		origen = origen->next;
	}
}

/*push_order*/
template<class T>
void Lista<T>::push_order(const T& d){
std::cout<<d<<"/n";

	if (head == NULL)
		head = new Node(d);
	else
	{
		Node *ptrTmp = head;
		while (ptrTmp->next != NULL){
		  std::cout<<d<<'\n';
			if(ptrTmp->dato<=d &&  ptrTmp->next->dato>=d){
				Node* sig=ptrTmp->next;
				ptrTmp->next=new Node(d,sig);
				return;
			}
			ptrTmp = ptrTmp->next;
		}

		ptrTmp->next = new Node(d);
	}
}


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
 1)adicionar los dem�s m�todos Lista
 (recursivamente).
 2) Implementar una lista que inserte los elementos
 ordenadamente
 3) implementar el constuctor de copia de la lista
 4) pila en base a lista
 5)cola en base a lista


*/

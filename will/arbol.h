#include <cstddef>
#include <iostream>
#include <queue>
#include <fstream>
template<typename T>
struct NodeBT {
	T dato;
	NodeBT<T>* izq;
	NodeBT<T>* der;
	NodeBT(T d, NodeBT<T>* i = NULL, NodeBT<T>* r = NULL):
	dato(d),izq(i),der(r){ }

};

template<typename T>
class ArbolBS {
	NodeBT<T>* root;
	void Add(T d, NodeBT<T>*& p);
	void print(NodeBT<T>* p)const;
public:
	ArbolBS():root(NULL){}
	void Add(T d) { Add(d, root); }
	void print() { print(root); }
	void printForLevel()const;
	void toGraphViz() const;
};

template<typename T>
void ArbolBS<T>::Add(T d, NodeBT<T> *& p) {
	if (!p) {
		p = new NodeBT<T>(d);
		return;
	}
	if (d < p->dato)
		Add(d, p->izq);
	else if (p->dato < d)
		Add(d, p->der);
	else return;
}
template<typename T>
void ArbolBS<T>::print(NodeBT<T>* p)const {
	if (!p) return;
	print(p->izq);
	std::cout << p->dato << " ";
	print(p->der);
	
}
template<typename T>
void ArbolBS<T>::printForLevel()const {
	std::queue< NodeBT<T>* > q;
	NodeBT<T>* actual = root;
	q.push(actual);
	while (!q.empty()) {
		actual = q.front();
		std::cout << actual->dato << " ";
		q.pop();
		if (actual->izq) q.push(actual->izq);
		if (actual->der) q.push(actual->der);
	}
}

template <typename T>
void ArbolBS<T>::toGraphViz()const {
	std::ofstream outFile("D://will//nuevo1.dot");
	std::queue< NodeBT<T>* > q;
	NodeBT<T>* actual = root;
	q.push(actual);
	outFile << "digraph G {"<<std::endl;
	while (!q.empty()) {
		actual = q.front();

		q.pop();
		if (actual->izq) {
			outFile << actual->dato << "->" << actual->izq->dato << ";" << std::endl;
			q.push(actual->izq);
		}
		if (actual->der) {
			outFile << actual->dato << "->" << actual->der->dato << ";" << std::endl;
			q.push(actual->der);
		}
	}
	outFile << std::endl << "}";
}
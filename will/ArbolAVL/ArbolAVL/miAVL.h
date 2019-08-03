#include <cstddef>
#include <stack>
#include <iostream>
#include <fstream>
template <class T>
struct NodoAVL{
	T dato;
	NodoAVL<T>* izq;
	NodoAVL<T>* der;
	enum tipo_balance {IZQ_PESADO=-1,BALANCEADO=0,DER_PESADO=1};
	tipo_balance balance;
	NodoAVL(T d, NodoAVL* i = NULL, NodoAVL* r = NULL){
		dato = d;
		izq = i;
		der = r;
		balance = BALANCEADO;
	}
};

template <class T>
class AVL{
	NodoAVL<T>* root;
	void add(T d, NodoAVL<T>* &p);
	bool crecioAltura;
	void RII(NodoAVL<T>* &p);
	void RDD(NodoAVL<T>* &p);
	void RID(NodoAVL<T>* &p);
	void RDI(NodoAVL<T>* &p);
	void print(NodoAVL<T>* r);
public:
	AVL():root(NULL){}
	void add(T d){ add(d,root);}
	void print(){ print(root); };
	//tarea
	//to_graphViz
	//eliminar nodo

	//red-Black
	//wearcaya@hotmail.com
	//asunto: maestr�a......
};

template<class T>
void AVL<T>::RII(NodoAVL<T>* &p){
	NodoAVL<T>* q = p->izq;
	p->izq = q->der;
	q->der = p;
	p = q;
}

template<class T>
void AVL<T>::RDD(NodoAVL<T>* &p){
	NodoAVL<T>* q = p->der;
	p->der = q->izq;
	q->izq = p;
	p = q;
}

template<class T>
void AVL<T>::RID(NodoAVL<T>* &p){
	NodoAVL<T>* p_A = p;
	NodoAVL<T>* q = p->izq;
	if (q->balance == NodoAVL<T>::DER_PESADO){
		NodoAVL<T>* r = q->der;
		if (r->balance == NodoAVL<T>::IZQ_PESADO){
			q->balance = NodoAVL<T>::BALANCEADO;
			r->balance = NodoAVL<T>::BALANCEADO;
			p_A->balance = NodoAVL<T>::DER_PESADO;
		}
		else if (r->balance==NodoAVL<T>::BALANCEADO){
			q->balance = NodoAVL<T>::BALANCEADO;
			r->balance = NodoAVL<T>::BALANCEADO;
			p_A->balance = NodoAVL<T>::BALANCEADO;
		}
		else{
			q->balance = NodoAVL<T>::IZQ_PESADO;
			r->balance = NodoAVL<T>::BALANCEADO;
			p_A->balance = NodoAVL<T>::BALANCEADO;
		}
		RDD(p->izq);
	}
	else{
		q->balance = NodoAVL<T>::BALANCEADO;
		p_A->balance = NodoAVL<T>::BALANCEADO;
	}
	RII(p);
}

template<class T>
void AVL<T>::RDI(NodoAVL<T>* &p){
	NodoAVL<T>* p_A = p;
	NodoAVL<T>* q = p->der;
	if (q->balance == NodoAVL<T>::IZQ_PESADO){
		NodoAVL<T>* r = q->izq;
		if (r->balance == NodoAVL<T>::DER_PESADO){
			q->balance = NodoAVL<T>::BALANCEADO;
			r->balance = NodoAVL<T>::BALANCEADO;
			p_A->balance = NodoAVL<T>::IZQ_PESADO;
		}
		else if (r->balance == NodoAVL<T>::BALANCEADO){
			q->balance = NodoAVL<T>::BALANCEADO;
			r->balance = NodoAVL<T>::BALANCEADO;
			p_A->balance = NodoAVL<T>::BALANCEADO;
		}
		else{
			q->balance = NodoAVL<T>::DER_PESADO;
			r->balance = NodoAVL<T>::BALANCEADO;
			p_A->balance = NodoAVL<T>::BALANCEADO;
		}
		RII(p->der);
	}
	else{
		q->balance = NodoAVL<T>::BALANCEADO;
		p_A->balance = NodoAVL<T>::BALANCEADO;
	}
	RDD(p);
}
template<class T>
void AVL<T>::add(T d, NodoAVL<T>* & p){
	if (p == NULL){
		p = new NodoAVL<T>(d);
		crecioAltura = true;
		return;
	}
	if (p->dato == d) return;
	if (p->dato > d){
		add(d, p->izq);
		if (crecioAltura){
			NodoAVL<T>* local_root = p;
			switch (local_root->balance){
			case NodoAVL<T>::BALANCEADO:
				local_root->balance = NodoAVL<T>::IZQ_PESADO;
				break;
			case NodoAVL<T>::DER_PESADO:
				local_root->balance = NodoAVL<T>::BALANCEADO;
				crecioAltura = false;
				break;
			case NodoAVL<T>::IZQ_PESADO:
				RID(p);
				crecioAltura = false;
				break;
			}
		}
	}
	else{
		//simEtrico
		add(d, p->der);
		if (crecioAltura){
			NodoAVL<T>* local_root = p;
			switch (local_root->balance){
			case NodoAVL<T>::BALANCEADO:
				local_root->balance = NodoAVL<T>::DER_PESADO;
				break;
			case NodoAVL<T>::IZQ_PESADO:
				local_root->balance = NodoAVL<T>::BALANCEADO;
				crecioAltura = false;
				break;
			case NodoAVL<T>::DER_PESADO:
				RDI(p);//ojo
				crecioAltura = false;
				break;
			}
		}
	}
}

template<class T>
void AVL<T>::print(NodoAVL<T>* r){
	std::ofstream myfile;
	myfile.open ("/Users/ivan/Desarrollo/ED/will/ArbolAVL/ArbolAVL/example.dot");
	myfile << "digraph G{\n node [shape=circle, color=blue]\n";

	std::stack<NodoAVL<T>*> s;
	NodoAVL<T>* actual = r;
	while (!s.empty() || actual) {
		if (actual) {
			if(actual->izq){
				myfile << actual->dato << "->" << actual->izq->dato<<";"<<"\n";
		  }
			s.push(actual);
			actual = actual->izq;
		}
		else {
			actual = s.top();
			s.pop();
			if(actual->der) {
			  myfile << actual->dato << "->" << actual->der->dato<<";"<<"\n";
			}
			std::cout << actual->dato << " ";
			actual = actual->der;
		}
	}
	myfile << "}\n";
	myfile.close();
}

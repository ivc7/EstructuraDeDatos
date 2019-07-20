#include <cstddef>
#include <iostream>
#include <queue>
#include <fstream>
template<typename T>
struct NodeBT{
  T dato;
  NodeBT<T>* izq;
  NodeBT<T>* der;
  NodeBT(T d,NodeBT<T>* i=NULL,NodeBT<T>* r=NULL):
   dato(d),izq(i),der(r){}
};

template<typename T>
class ArbolBS{
  NodeBT<T>* root;
  void Add(T d,NodeBT<T>*& p);
  void print(NodeBT<T>* p)const ;
public:
  ArbolBS():root(NULL){}
  void Add(T d){Add(d,root);}
  void print(){print(root);}
  void printForLevel()const;
};

template<typename T>
void ArbolBS<T>::Add(T d, NodeBT<T> *& p){
  if(!p){
    p=new NodeBT<T>(d);
    return;
  }
  if(d<p->dato)
    Add(d,p->izq);
  else if(p->dato < d)
      Add(d,p->der);
  else return;//si es igual
}

template<typename T>
void ArbolBS<T>::print(NodeBT<T>* p)const{
  if(!p)return ;
  print(p->izq);
  std::cout<<p->dato<<" ";
  print(p->der);

}

template<typename T>
void ArbolBS<T>::printForLevel()const{
  std::ofstream myfile;
  myfile.open ("/Users/ivan/Desarrollo/ED/Graph/example.dot");
  myfile << "digraph G{\n node [shape=box, color=blue]\n";

  std::queue<NodeBT<T>* > q;
  NodeBT<T>* actual=root;
  q.push(actual);
  while(!q.empty()){
    actual= q.front();
    std::cout<<actual->dato<<" ";

    q.pop();
    if(actual->izq){
      myfile << actual->dato << "->" << actual->izq->dato<<";"<<"\n";
      q.push(actual->izq);
    }
    if(actual->der) {
myfile << actual->dato << "->" << actual->der->dato<<";"<<"\n";
      q.push(actual->der);
    }
  }
  myfile << "}\n";
  myfile.close();

}

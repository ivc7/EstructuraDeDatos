#include "arbol.h"

int main(){
/*  ArbolBS<char> abc;
  abc.Add('H');
  abc.Add('D');
  abc.Add('Q');
  abc.Add('B');
  abc.Add('J');
  abc.Add('F');
  abc.Add('S');
  abc.Add('X');
  abc.printForLevel();
*/

ArbolBS<int> avl;
avl.Add(10);
avl.Add(17);
avl.Add(24);
avl.Add(19);
avl.Add(26);
avl.Add(22);
avl.printForLevel();

/*
  ArbolBS<int> abi;
  for(size_t i=0;i<3000;i++){
    abi.Add(rand()%3000);
  }
  abi.printForLevel();
*/
  return 0;
}

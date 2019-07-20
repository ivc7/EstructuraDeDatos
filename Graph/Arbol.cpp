#include "arbol.h"

int main(){
  ArbolBS<char> abc;
  abc.Add('H');
  abc.Add('D');
  abc.Add('Q');
  abc.Add('B');
  abc.Add('J');
  abc.Add('F');
  abc.Add('S');
  abc.Add('X');
  abc.printForLevel();

  ArbolBS<int> abi;
  for(size_t i=0;i<30;i++){
    abi.Add(rand()%100);
  }
  abi.printForLevel();

  return 0;
}

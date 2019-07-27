
#include "arbol.h"

int main()
{
	ArbolBS<char> abc;
	abc.Add('H');
	abc.Add('D');
	abc.Add('Q');
	abc.Add('B');
	abc.Add('J');
	abc.Add('F');
	abc.Add('S');
	abc.print();
	std::cout << std::endl;
	abc.printForLevel();
	std::cout << std::endl;
	abc.toGraphViz();
    return 0;
}


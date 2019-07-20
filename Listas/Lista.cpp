#include<string>
#include"Lista.h"
void func(Lista<int> &a) { Lista<int> b(a); b.push_back(100);b.print();
std::cout << "\n"; }
int main()
{
/*
	Lista<int> li;
	li.push_front(1);
	li.push_front(3);
	li.push_front(5);
	li.push_back(10);

	li.print();
	func(li);
	std::cout << "\n";
	li.print();
	std::cout << "\n";
	Lista<std::string> ls;
	ls.push_front("Ana");
	ls.push_front("Jhon");
	ls.push_front("Beto");
	ls.push_back("HELLO");
	ls.print();
*/
 //Order
	Lista<int> lo;
	lo.push_order(1);
	lo.push_order(5);
	lo.push_order(10);
	lo.push_order(7);
	lo.push_order(11);

	lo.print();
std::cout << "\n";

    return 0;
}

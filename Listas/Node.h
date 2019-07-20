
struct Node
{
	T dato;
	Node* next;
	Node(const T& d, Node* ptrNext = NULL):
		dato(d), next(ptrNext) {}
};

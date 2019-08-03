#include <stdio.h>
#include <stdlib.h>
#include <cstddef>
#include <stack>
#include <iostream>
#include <fstream>

template <typename T>
struct Tree{
    T key;
    Tree<T> *left;
    Tree<T> *right;
    int height;
} ;


template <typename T>
int height(Tree<T> *t)
{
    if (t == NULL)
        return 0;
    return t->height;
}

template <typename T>
int getBalance(Tree<T> *t)
{
    if(t==NULL)
        return 0;
    return height(t->left)-height(t->right);
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

template <typename T>
Tree<T>* newNode(int key)
{
    Tree<T>* node = (Tree<T>*)malloc(sizeof(Tree<T>));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}

template <typename T>
Tree<T>* insert(Tree<T>* node, int key)
{
    /* 1.  Perform the normal BST rotation */
    if (node == NULL)
        return(newNode<T>(key));

    if (key < node->key)
        node->left  = insert(node->left, key);
    else
        node->right = insert(node->right, key);

    /* 2. Update height of this ancestor node */
    node->height = max(height(node->left), height(node->right)) + 1;
    return node;
}

template <typename T>
void print_preorder(Tree<T> * tTree,std::ofstream &myfile)
{

    if(tTree)
    {
    	std::cout<<tTree->key;

        if(tTree->left){
             myfile << tTree->key<< "->" << tTree->left->key<<";"<<"\n";
        }

        if(tTree->right){
           myfile << tTree->key << "->" << tTree->right->key<<";"<<"\n";
        }

//        myfile << tTree->key << "->" << tTree->right->key<<";"<<"\n";
        print_preorder(tTree->left, myfile);
        print_preorder(tTree->right, myfile);
    }

}

template <typename T>
void print_preorder(Tree<T> * tTree)
{

    if(tTree)
    {
        std::cout<<tTree->key;
        print_preorder(tTree->left);
        print_preorder(tTree->right);
    }

}

template <typename T>
void deleteTree(Tree<T> * tTree)
{
    if (tTree)
    {
        deleteTree(tTree->left);
        deleteTree(tTree->right);
        free(tTree);
    }
}

template <typename T>
Tree<T>* del(Tree<T> *tTree, int delItem) /* delete( main body) */
{
    if(!(tTree))
        return tTree;
    if(delItem < tTree->key)
        tTree->left = del(tTree->left, delItem);
    else
        if(delItem > tTree->key)
            tTree->right = del(tTree->right, delItem);
        else
        {
            Tree<T> *oTree = tTree;
            if((tTree->left) && (tTree->right))
            {
                Tree<T> *parent = tTree->right;
                tTree = parent->left;
                if (tTree)
                {
                    while(tTree->left)
                    {
                        parent = tTree;
                        tTree = tTree->left;
                    }
                    parent->left = tTree->right;
                    tTree->right = oTree->right;
                }
                else
                    tTree = parent;
                tTree->left = oTree->left;
            }
            else
                if(tTree->left)
                    tTree = tTree->left;
                else
                    tTree = tTree->right;
            free(oTree);
        }
    return tTree;
}

template <typename T>
Tree<T>* rotateLeft(Tree<T>* t)
{
    Tree<T> *y = t->right;
    Tree<T> *T2 = y->left;

    // Perform rotation
    y->left = t;
    t->right = T2;


    // Update heights
    t->height = max(height(t->left), height(t->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    // Return new root
    return y;
}

template <typename T>
Tree<T>* rotateRight(Tree<T>* t)
{
    Tree<T> *x = t->left;
    Tree<T> *T2 = x->right;

    // Perform rotation
    x->right = t;
    t->left = T2;

    // Update heights
    t->height = max(height(t->left), height(t->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    // Return new root
    return x;
}

template <typename T>
Tree<T> *balanceNode(Tree<T> *t)
{
    if (!t) return t;
    int balance = getBalance(t);
    if (balance > 1 && getBalance(t->left) >= 0)   /* rotateReight */
        return rotateRight(t);
    if (balance < -1 && getBalance(t->right) <= 0) /* rotateLeft */
        return rotateLeft(t);
    if (balance > 1 && getBalance(t->left) < 0)    /* rotateLeftReight */
    {
        t->left = rotateLeft(t->left);
        return rotateRight(t);
    }
    if (balance < -1 && getBalance(t->right) > 0)  /* rotateReightLeft */
    {
        t->right = rotateRight(t->right);
        return rotateLeft(t);
    }
    return t;
}

int mainNumeros(void)
{
    Tree<int> *Tree;
    Tree = NULL;
    int i, a[]={7,3,9,10,8,1,4,2,6,5};
    for(i=0;i<10;i++) /* construct tree */
        Tree = insert(Tree,a[i]);
    /* Printing nodes of tree */
    printf("Pre Order Display\n");
    print_preorder(Tree);

    printf("\nBalanced Tree\n");
    Tree=balanceNode(Tree);
    std::ofstream myfile;
    myfile.open ("entrada.dot");
    myfile << "digraph A{\n ";

    print_preorder(Tree,myfile);

    myfile << "}\n";
    myfile.close();

    system("/usr/local/bin/dot -Tpdf entrada.dot -o entrada.pdf");


    while(1)
    {
        printf("\nEnter an Item that You Want to Delete: ");
        scanf("%d",&i);
        printf("\n");
        Tree = del(Tree,i);
        printf("After Delete\n");
        /*  Pre-order displays root node, left node and then right node. */
        print_preorder(Tree);
        Tree = balanceNode(Tree);
        printf("\nAfter Balance\n");
        print_preorder(Tree);

        std::ofstream myfile;
        myfile.open ("elimina.dot");
        myfile << "digraph "<<i<<"{\n ";

        print_preorder(Tree,myfile);

        myfile << "}\n";
        myfile.close();

        system("/usr/local/bin/dot -Tpdf elimina.dot -o elimina.pdf");
    }

    printf("\n");

    deleteTree(Tree);
    printf("\n");
    return 0;
}

int mainLetras(void)
{
    Tree<char> *Tree;
    Tree = NULL;
    int i, a[]={'a','b','c','d','e','f'};
    for(i=0;i<6;i++) /* construct tree */
        Tree = insert(Tree,a[i]);
    /* Printing nodes of tree */
    printf("Pre Order Display\n");
    print_preorder(Tree);

    printf("\nBalanced Tree\n");
    Tree=balanceNode(Tree);
    std::ofstream myfile;
    myfile.open ("entrada.dot");
    myfile << "digraph A{\n ";

    print_preorder(Tree,myfile);

    myfile << "}\n";
    myfile.close();

    system("/usr/local/bin/dot -Tpdf entrada.dot -o entrada.pdf");


    while(1)
    {
        printf("\nEnter an Item that You Want to Delete: ");
        scanf("%c",&i);
        printf("\n");
        Tree = del(Tree,i);
        printf("After Delete\n");
        /*  Pre-order displays root node, left node and then right node. */
        print_preorder(Tree);
        Tree = balanceNode(Tree);
        printf("\nAfter Balance\n");
        print_preorder(Tree);

        std::ofstream myfile;
        myfile.open ("elimina.dot");
        myfile << "digraph "<<i<<"{\n ";

        print_preorder(Tree,myfile);

        myfile << "}\n";
        myfile.close();

        system("/usr/local/bin/dot -Tpdf elimina.dot -o elimina.pdf");
    }

    printf("\n");

    deleteTree(Tree);
    printf("\n");
    return 0;
}

int main(void){
	mainNumeros();
	//mainLetras();
}

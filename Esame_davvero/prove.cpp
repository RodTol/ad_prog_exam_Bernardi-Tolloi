#include"node.h"
#include"iterator.h"
#include "bst.h"
#include<iostream>



int main () {

    node<int> nodo1{8};

    node<int> nodo2{6, &nodo1, 0};
    node<int> nodo3{7, &nodo2, 1};
    

   
    std::cout << "nodo 1\n" << nodo1 << std::endl;
    std::cout << "nodo 2\n" << nodo2 << std::endl;
    std::cout << "nodo 3\n" << nodo3 << std::endl;
    std::cout << "memoria di nodo 1\n" << &(nodo1) << std::endl;
    std::cout << "memoria di nodo 2\n" << &(nodo2) << std::endl;
    std::cout << "memoria di nodo 3\n" << &(nodo3) << std::endl;

    _iterator<int> i{&nodo3};
    _iterator<int> j;
   
    std::cout << "iterator i " << i << std::endl;
     j=++i;
    std::cout << "iterator j " << j << std::endl;

   
}
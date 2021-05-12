#include"node.hpp"
#include"iterator.hpp"
#include "bst.hpp"
#include<iostream>



int main () {

    node<int> nodo1{8};
    node<int> nodo2{6};
    node<int> nodo3{10};
    node<int> nodo4{7};

    
    nodo1.set_left_child(&nodo2);
    nodo1.set_right_child(&nodo3);

    nodo2.set_right_child(&nodo4);

    std::cout << "nodo 1\n" << nodo1 << std::endl;
    std::cout << "memoria di nodo 1\n" << &(nodo1) << std::endl;
    
    std::cout << "nodo 2\n" << nodo2 << std::endl;
    std::cout << "memoria di nodo 2\n" << &(nodo2) << std::endl;
    
    std::cout << "nodo 3\n" << nodo3 << std::endl;
    std::cout << "memoria di nodo 3\n" << &(nodo3) << std::endl;
    
    std::cout << "nodo 4\n" << nodo4 << std::endl;
    std::cout << "memoria di nodo 4\n" << &(nodo4) << std::endl;
        
    _iterator<int> i{&nodo3};
    _iterator<int> j;
   
    std::cout << "iterator i " << i << std::endl;
    j=++i;
    std::cout << "iterator j " << j << std::endl;

   
}
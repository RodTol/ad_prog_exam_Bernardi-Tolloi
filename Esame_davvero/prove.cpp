#include"node.hpp"
#include"iterator.hpp"
#include"bst.hpp"
#include<iostream>
#include <functional>
#include <utility>


int main () {

    using pair = std::pair<int,int>;

    /*node<int> nodo1{8};

    nodo1.create_left_child(6);
    nodo1.create_right_child(10);
    
    (*(nodo1.left)).create_right_child(7);

    std::cout << "nodo 1\n" << nodo1 << std::endl;
    std::cout << "memoria di nodo 1\n" << &(nodo1) << std::endl;
    
    std::cout << "nodo 2\n" << (*(nodo1.left)) << std::endl;
    std::cout << "memoria di nodo 2\n" << &(*(nodo1.left)) << std::endl;
    
    std::cout << "nodo 3\n" << nodo3 << std::endl;
    std::cout << "memoria di nodo 3\n" << &(*(nodo1.right)) << std::endl;
    
    std::cout << "nodo 4\n" << nodo4 << std::endl;
    std::cout << "memoria di nodo 4\n" << &(nodo4) << std::endl;
    
    _iterator<int> i{&nodo1};
    _iterator<int> j;
   
    std::cout << "iterator i " << i << std::endl;
    j=++i;
    std::cout << "iterator j " << j << std::endl; 
    */

    pair pair1{8,2};
    pair pair2{6,2};
    pair pair3{7,2};
    pair pair4{10,2};

    bst< int, int, std::less<int> > albero {pair1};
    (*(albero.head)).create_left_child(pair2); 
    (*(albero.head)).create_right_child(pair4);

    (*((*(albero.head)).left)).create_right_child(pair3); 

    std::cout << "nodo 1\n" << *(albero.head) << std::endl;
    std::cout << "memoria di nodo 1\n" << &((*(albero.head))) << std::endl;
    
    std::cout << "nodo 2\n" << (*((*(albero.head)).left)) << std::endl;
    std::cout << "memoria di nodo 2\n" << &(*((*(albero.head)).left)) << std::endl;

    std::cout << "memoria di nodo 4\n" << &(*((*(albero.head)).right)) << std::endl;

    _iterator<node<pair>, int> i{albero.head.get()};
    _iterator<node<pair>,int> j;
   
    std::cout << "iterator i " << i << std::endl;
    j=++i;
    std::cout << "iterator j " << j << std::endl; 
   
    std::cout << "begin \n" << albero.begin() << std::endl;
    std::cout << "tail \n" << albero.tail() << std::endl;
    std::cout << "end \n" << albero.end() << std::endl;

    bst<int, int, std::less<int>> albero2;
    std::cout << "begin  2\n" << albero2.begin() << std::endl;
    std::cout << "find nodo = 11\n" << albero.find(11) << std::endl;
}


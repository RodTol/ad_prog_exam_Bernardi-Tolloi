#include"node.hpp"
#include"iterator.hpp"
#include"bst.hpp"
#include<iostream>
#include <functional>
#include <utility>


int main () {

    using pair = std::pair<const int,int>;

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
   const int a{8};
   const pair pair1{a,2};
   const pair pair2{6,5};
   const pair pair3{10,2};
   const pair pair4{7,2};
   const pair pair5{9,2};
   const pair pair6{1,2};
   const pair pair7{2,2};
/*
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

    albero.insert(pair1);
    std::cout << "insert di pair1\n" << albero.insert(pair1).first << " " << albero.insert(pair1).second << std::endl;
*/
/*
    bst<const int, int, std::less<int> > albero3 {};
    albero3.insert(pair1);
    albero3.insert(pair2);
    albero3.insert(pair3);
    albero3.insert(pair4);
    //albero3.insert(pair5);
    albero3.emplace(13,2);

    std::cout << "Head\n" << *(albero3.head) << std::endl;
    std::cout << "Memoria di nodo 1\n" << &((*(albero3.head))) << std::endl;

    std::cout << "Nodo 2\n" << (*((*(albero3.head)).left)) << std::endl;
    std::cout << "Memoria di nodo 2\n" << &( *( (*(albero3.head)).left ) ) << std::endl;

    std::cout << "Nodo 3\n" << *( *( (*(albero3.head)).left ) ).right << std::endl;
    std::cout << "Memoria di nodo 3\n" << &(*( *( (*(albero3.head)).left ) ).right) << std::endl;

   
    std::cout << "Nodo 5\n" << *(*((*(albero3.head)).right)).right << std::endl;
    std::cout << "Memoria di nodo 5\n" << &(*(*((*(albero3.head)).right)).right) << std::endl;


    std::cout << "Value del nodo 6 " << albero3[6] << std::endl;
    std::cout << "Value del nodo 24" << albero3[24] << std::endl;

    std::cout << "Prova di insert\n" << albero3.insert(pair5).first << "  " << albero3.insert(pair5).second << std::endl;

    std::cout << "Nodo 4\n" << (*((*(albero3.head)).right)) << std::endl;
    std::cout << "Memoria di nodo 4\n" << &(*((*(albero3.head)).right)) << std::endl;

    std::cout << "Albero 3 \n" << albero3 << std::endl;

    albero3.clear();
 */  
    bst<const int, int, std::less<int> > albero1 {};
    albero1.insert(pair1);
    albero1.insert(pair2);
    albero1.insert(pair3);
    albero1.insert(pair4);
    albero1.insert(pair5);
    albero1.insert(pair6);
    albero1.insert(pair7);
    std::cout << "Albero 1 \n" << albero1 <<std::endl;
    std::cout << "Dimensioni albero 1\n " << albero1.size() << std::endl;

    albero1.begin();
    albero1.balance();
    
}


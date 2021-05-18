#include"node.hpp"
#include"iterator.hpp"
#include"bst.hpp"
#include<iostream>
#include <functional>
#include <utility>

int main () {
    using pair = std::pair<const int,int>;
    pair pair1{8,1};
    pair pair2{10,2};
    pair pair3{14,3};
    pair pair4{13,4};
    pair pair5{3,5};
    pair pair6{1,6};
    pair pair7{6,7};
    pair pair8{4,8};
    pair pair9{7,9};
    pair pair10{22200, 5};

    bst<int, int, std::less<int> > albero;
    albero.insert(pair1);
    albero.insert(pair2);
    albero.insert(pair3);
    albero.insert(pair4);
    albero.insert(pair5);
    albero.insert(pair6);
    albero.insert(pair7);
    albero.insert(pair8);
    albero.insert(pair9);

    std::cout<< "Albero \n" << albero;
    std::cout<< "Head of tree \n" << *albero.head.get() << std::endl;

    /*albero.erase(3);

    std::cout<< "Albero after removal \n" << albero;
    std::cout<< "New 3\n" << (*(*albero.head.get()).left) << std::endl;
    std::cout<< "New 4\n" << *(albero.find(4).current) << std::endl;
    std::cout<< "LEft of new 4\n" << *(albero.find(4).current->left) << std::endl;*/

    node<pair> nodo_copia {(*albero.head.get()), nullptr};

    std::cout<< "nodo_copia\n" << nodo_copia << std::endl;
    std::cout<< "figlio dx e sx di nodo copia\n" << *nodo_copia.right << "\n" << *nodo_copia.left <<std::endl;

    //bst<int, int, std::less<int> > albero2 {albero};
    bst<int, int, std::less<int> > albero2;
    //bst<int, int, std::less<int> > albero2 {std::move(albero)};

    albero2 = std::move(albero);
    
    std::cout<< "Albero \n" << albero2;
    std::cout<< "Head of tree \n" << *albero2.head.get() << std::endl;
    std::cout<< "New 6\n" << *(albero2.find(6).current) << std::endl;
    std::cout<< "Left of new 6 (è 4)\n" << *(albero2.find(6).current->left) << std::endl;

    std::cout<< "Albero \n" << albero;



    
    
}
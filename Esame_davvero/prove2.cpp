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

    albero.erase(8);

    std::cout<< "Albero after removal \n" << albero;
    std::cout<< "New head of tree\n" << *albero.head.get() << std::endl;
    
    
}
/*
Author: Rodolfo Tolloi, Giulia Bernardi.

Purpouse:   VA SCRITTO !!!!!!!!!!!!!!!11.

Date: May, 2021.
*/

#include"node.h"

template<typename type_of_attr>
class iterator {

    /*raw pointer to the starting node*/
    node<type_of_attr>* start;

public:
    /*custom costr*/
    iterator(node<type_of_attr> input):
        start{&input}
    {
      std::cout << "iterator custom constructor" << std::endl;
    };

    /*default cost and destr*/
    iterator() = default;
    ~iterator() = default;
};

//METTERE OPERATORE ++


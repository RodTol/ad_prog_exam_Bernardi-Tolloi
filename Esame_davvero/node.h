/*
Author: Rodolfo Tolloi, Giulia Bernardi.

Purpouse: create a custom class named node which 
implements a node for a binary search tree (BST). 
Each node has two unique pointers, named right and
left, and can have only one father's node.

Date: May, 2021.
*/

#include<utility>
#include<memory>
#include<iostream>

template <typename T>
class node {

    /*pointers to children*/ 
    std::unique_ptr<node> right;
    std::unique_ptr<node> left;

    /*attribute of the node (which can be of any type
    including a pair)*/
    T attr;


    public :

        /*constructor default*/
        node() = default;

        /*custom constructor*/
        node(const T& input) :
         attr{input},
         right{nullptr},
         left{nullptr}  
         {
             std::cout << "node custom constructor" << std::endl;
         }
            
        /*destructor*/
        ~node () = default;
        
        /*put to*/
        friend
        std::ostream& operator<<(std::ostream& os, const node& x) {
         os << x.attr << " " << &(x.right) << " " << &(x.left);
         return os;
        }
};


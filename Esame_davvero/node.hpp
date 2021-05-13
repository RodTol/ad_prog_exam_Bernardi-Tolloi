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
struct node {

    /*attribute of the node (which can be of any type
    including a pair)*/
    T attr;

    /*pointers to children*/ 
    std::unique_ptr<node> right;
    std::unique_ptr<node> left;

    /*raw pointer to parent*/
    node* parent;

    /*constructor default*/
    node() = default;
    
    /*custom constructor without parent node*/
    node(const T& input) :
    attr{input},
    right{nullptr},
    left{nullptr},
    parent{nullptr}
    {
        std::cout << "node custom constructor no parent" << std::endl;
    }

    /*custom constructor with parent node*/
    node(const T& input, node* input_pointer) :
    attr{input},
    right{nullptr},
    left{nullptr},
    parent{input_pointer} {}
        
    /*destructor*/
    ~node () = default;

    /*Funzioni: */
    // DA VEDERE SE LASCIARE FORWARD
    void create_left_child(T child_attr) {
        left = std::make_unique<node>(std::forward<T>(child_attr), this);
    }
    
    void create_right_child(T child_attr) {
        right = std::make_unique<node>(std::forward<T>(child_attr), this); 
    }


    //OCHO AL PUT TO CHE VA BENE SOLO PER LE PAIR

    friend
    /*put to da rimuovere perche lo metteremo in bst*/
    std::ostream& operator<<(std::ostream& os, const node& x) {
        os << x.attr.first << " " << x.left.get() << " " << x.right.get() << " " << x.parent << "\n"; 
    return os;
    }
};



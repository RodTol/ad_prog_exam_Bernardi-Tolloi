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
    node(const T& input, node<T>* input_pointer, int i) :
    attr{input},
    right{nullptr},
    left{nullptr},
    parent{input_pointer}
    {

        if (i == 0)
        {
            std::cout << "node custom constructor parent left" << std::endl;
            input_pointer->left.reset(this);
        }
        else
        {
            std::cout << "node custom constructor parent right" << std::endl;
            input_pointer->right.reset(this);
        }
        
    }
        
    /*destructor*/
    ~node () = default;

    void set_left_child(node* child) {
        left.reset(child);
        child -> parent = this;
    }
    
    void set_right_child(node* child) {
        right.reset(child);
        child -> parent = this;
    }

    friend
    /*put to*/
    std::ostream& operator<<(std::ostream& os, const node& x) {
        os << x.attr << " " << x.left.get() << " " << x.right.get() << " " << x.parent << "\n"; 
    return os;
    }
};



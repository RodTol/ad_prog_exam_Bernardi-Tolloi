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

    /*Attribute of the node (which can be of any type
    including a pair)*/
    T attr;

    /*Pointers to children*/ 
    std::unique_ptr<node> right;
    std::unique_ptr<node> left;

    /*Raw pointer to parent*/
    node* parent;

    /*Constructor default*/
    node() = default;
    /*Destructor*/
    ~node () = default;
    
    /*Custom constructor without parent node*/
    explicit node(const T& input) noexcept :
    attr{input},
    right{nullptr},
    left{nullptr},
    parent{nullptr} {} 

    /*Custom constructor with parent node* from input*/
    node(const T& input, node* input_pointer) noexcept:
    attr{input},
    right{nullptr},
    left{nullptr},
    parent{input_pointer} {}

    /*copy ctor (it copies starting node and all of his children, but no parent)*/
    node(const node& node_to_copy, node* new_parent):
    attr{node_to_copy.attr},
    right{nullptr},
    left{nullptr},
    parent{new_parent} {
        if (node_to_copy.right) {
            right = std::make_unique<node>(*node_to_copy.right, this);
        }
        if (node_to_copy.left) {
            left = std::make_unique<node>(*node_to_copy.left, this);
        }
    }


    /*Functions: */
    /*This function create a left child of a node of our choice*/
    void create_left_child(T child_attr) {
        left = std::make_unique<node>(std::forward<T>(child_attr), this);
    }
    /*This function create a right child of a node of our choice*/
    void create_right_child(T child_attr) {
        right = std::make_unique<node>(std::forward<T>(child_attr), this); 
    }

    friend
    /*custom overloading of the put to operator for the nodes. This function
    was created with a debugging purpouse, and can be used only if the attr
    of the nodes is of type pair.*/
    std::ostream& operator<<(std::ostream& os, const node& x) {
        os << x.attr.first << " " << x.left.get() << " " << x.right.get() << " " << x.parent << "\n"; 
    return os;
    }
};



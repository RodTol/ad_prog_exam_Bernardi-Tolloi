/**
*Author: Rodolfo Tolloi, Giulia Bernardi.
*
*Purpouse: create a custom struct named node which 
*implements a node for a binary search tree (BST). 
*Each node has two unique pointers, named right and
*left, and can have only one father node.
*
*Date: May, 2021.
*/

#include<utility>
#include<memory>
#include<iostream>

template <typename T>
struct node {

    /**Attribute of the node
    */
    T attr;

    /**Unique pointer to right child*/ 
    std::unique_ptr<node> right;

    /**Unique pointer to left child*/
    std::unique_ptr<node> left;

    /**Raw pointer to parent*/
    node* parent;

    /**Default constructor*/
    node() = default;
    /**Default destructor*/
    ~node () = default;
    
    /**Custom constructor without input parent node* */
    explicit node(const T& input) noexcept :
    attr{input},
    right{nullptr},
    left{nullptr},
    parent{nullptr} {} 

    /**Custom constructor with input parent node* */
    node(const T& input, node* input_pointer) noexcept:
    attr{input},
    right{nullptr},
    left{nullptr},
    parent{input_pointer} {}

    /**Copy custom constructor. It creates a new node with the attribute of the starting node,
    * but with the parent equal to an input pointer. The process is then iterated for all of its
    * children, such that at the end, a deep copy of its subtree is performed. */
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

    /**This function creates a left child for the node based on an input attribute*/
    void create_left_child(T child_attr) {
        left = std::make_unique<node>(std::forward<T>(child_attr), this);
    }
    /**This function create a right child for a input node*/
    void create_right_child(T child_attr) {
        right = std::make_unique<node>(std::forward<T>(child_attr), this); 
    }

    friend
    /**Custom overloading of the put to operator for the node struct. This function
    * was created with a debugging purpouse, and can be used only if the attr
    * of the nodes is of type pair.*/
    std::ostream& operator<<(std::ostream& os, const node& x) {
        
        os << "Key " << x.attr.first << "\n";

        if (x.left.get())
        {
           os << "Left child " << (*x.left.get()).attr.first << "\n";
        }
        else {
            os << "No left child\n"; 
        }
        
        if (x.right.get())
        {
            os << "Right child " <<  (*x.right.get()).attr.first << "\n";
        }
        else {
            os << "No right child\n"; 
        }
        
        if (x.parent)
        {
           os << "Parent node " <<  (*x.parent).attr.first << "\n"; 
        }
        else {
            os << "No parent node\n"; 
        }
    return os;
    }
};



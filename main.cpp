/*
Author: Rodolfo Tolloi, Giulia Bernardi.

Purpouse:   VA SCRITTO !!!!!!!!!!!!!!!11.

Date: May, 2021.
*/

#include"include/node.hpp"
#include"include/iterator.hpp"
#include"include/bst.hpp"
#include<iostream>
#include <functional>
#include <utility>
#include <vector>

int main() {

    try{

        using pair = std::pair<int,int>;
        using bst = bst<int, int, std::less <int> >;

        std::cout << "The tree is of dimension 13" << std::endl;
        std::vector<int> keys {7,5,3,1,4,6,12,9,8,10,15,13,17};
        std::vector<int> values {1,2,3,4,5,6,7,8,9,10,11,12,13};
        std::vector<pair> attributes;
        bst tree;


        for (int i = 0; i < 7; i++)
        {
            attributes.push_back(std::make_pair( keys[i],values[i] ));   
        }
        
        for (auto i = 0; i < 7; i++)
        {
            tree.insert(attributes[i]);
        }
        
        for (auto i = 7; i < 13; i++)
        {
            tree.emplace(keys[i], values[i]);
        }
        std::cout << "The tree is initialized as shown in the picture of the readme file\n";
        std::cout << tree << std::endl;

        std::cout << "I try to insert a node with key = 6\n";
        tree.emplace(6,6);
        
        bst tree_copy {tree};
        std::cout << "I created a tree using the copy constructor. The result is:\n";
        std::cout << tree_copy << std::endl;

        tree_copy.erase(12);
        std::cout << "I erased the node with key = 12 from tree_copy, to show\nwe performed a deep copy.\n";
        std::cout << tree_copy << std::endl;
        std::cout << "This is tree\n";
        std::cout << tree << std::endl;

        bst tree_copy_2;
        tree_copy_2 = tree;
        std::cout << "I create a identical bst using the copy assignment" << std::endl;
        std::cout << tree_copy_2 << std::endl;

        tree_copy_2.erase(12);
        std::cout << "I erased the node with key = 12 from tree_copy_2, to show\nwe performed a deep copy.\n";
        std::cout << tree_copy_2 << std::endl;
        std::cout << "This is tree\n";
        std::cout << tree << std::endl;

        tree = std::move(tree_copy);
        std::cout << "I moved tree_copy on tree with a std::move assignment\n";
        std::cout << tree << std::endl;
        std::cout << "This is the tree_copy after the move\n";
        std::cout << tree_copy << std::endl;

        std::cout << "The leftmost of tree is\n";
        std::cout << *tree.begin().current << std::endl;

        std::cout << "The rightmost of tree is\n";
        std::cout << *tree.tail().current << std::endl;

        std::cout << "The end of tree is\n";
        std::cout << tree.end() << std::endl;

        std::cout << "I use the find operator to search a node with key = 32\n";
        std::cout << tree.find(32) << std::endl;
        std::cout << "The function returns nothing. Instead if I search for key = 7\n";
        std::cout << *tree.find(7).current << std::endl;
        std::cout << "We can see that the right child of the node with key= 7 has changed after the erase\n";

        std::cout << "I use the subscripting operator for finding the value of the node with key = 15\n";
        std::cout << tree[15] << std::endl;

        std::cout << "At the current state, the head node and its two children are:\n";
        std::cout << "Head node\n" << *tree.head.get() << std::endl;
        std::cout << "Right child of head node\n" << *( *tree.head.get() ).right << std::endl;
        std::cout << "Left child of head node\n" << *( *tree.head.get() ).left << std::endl;

        tree.balance();
        std::cout << "After the balance, the head node and its two children are:\n";
        std::cout << "Head node\n" << *tree.head.get() << std::endl;
        std::cout << "Right child of head node\n" << *( *tree.head.get() ).right << std::endl;
        std::cout << "Left child of head node\n" << *( *tree.head.get() ).left << std::endl;

        std::cout << "At last I perform a clear on tree, removing it of all its elements\n";
        tree.clear();
        std::cout << tree << std::endl;

    }
    catch(const std::exception& e){
        std::cerr<<e.what()<<std::endl;
        return 1;
    }
    catch(...) {
        std::cerr<<"Unknown exception."<<std::endl;
        return 2;
    }

}



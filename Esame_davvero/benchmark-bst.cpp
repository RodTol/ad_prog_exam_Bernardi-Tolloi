/*
Author: Rodolfo Tolloi, Giulia Bernardi.

Purpouse:   VA SCRITTO !!!!!!!!!!!!!!!11.

Date: May, 2021.
*/


#include"node.hpp"
#include"iterator.hpp"
#include"bst.hpp"
#include<iostream>
#include <functional>
#include <utility>
#include<map>
#include<algorithm>
#include<random>
#include<ctime>
#include<chrono>

int random_seed (int i);

/*void print_map(const std::map<int, int>& m)
{
    for (const auto& [key, value] : m) {
        std::cout << key << " = " << value << "; ";
    }
    std::cout << "\n";
}*/

int main () {
    bst<int, int, std::less<int> > bst_test;
    std::map <int, int> map_test;
    int dimension;
    std::vector<int> nodes_key;
    std::vector<std::pair <int, int> > nodes_pair;

    using std::chrono::microseconds;

    /*It's common pratice to initialize the seed for rand
    to the current unix timestamp*/
    srand(time(0));

    std::cout<< "Number of nodes" << std::endl;
    std::cin >> dimension;

   

    for (auto i = 0; i < dimension; ++i)
    {
        nodes_key.push_back(i+1);
    }

    /*std::cout << "Nodes before shuffle\n" ;
    for (auto i = 0; i < dimension; i++)
    {
       std::cout  << nodes_key[i] << " "; 

    }
    std::cout << std::endl;*/


    std::random_shuffle(nodes_key.begin(), nodes_key.end(), random_seed);

    /*std::cout << "Nodes after shuffle\n" ;
    for (auto i = 0; i < dimension; i++)
    {
       std::cout  << nodes_key[i] << " "; 

    }*/

    for (auto i = 0; i < dimension; i++)
    {
       nodes_pair.push_back(std::make_pair(nodes_key[i], i+1));
    }
    
    for (auto i = 0; i < dimension; i++)
    {
        bst_test.insert(nodes_pair[i]);
        map_test.insert(nodes_pair[i]);
    }

    /*std::cout << "bst_test\n";
    std::cout << bst_test << std::endl;
    std::cout << "map_test\n";
    print_map(map_test);*/

    auto t1 = std::chrono::high_resolution_clock::now();
    for (auto i = 0; i < dimension; i++)
    {
        bst_test.find(i+1);
    }
    auto t2 = std::chrono::high_resolution_clock::now();

    auto interval1 = std::chrono::duration_cast<microseconds> (t2-t1);
    std::cout << "Time for finding all the key for unbalanced bst tree\n";
    std::cout << interval1.count() << " microseconds" << std::endl;

    bst_test.balance();
    auto t3 = std::chrono::high_resolution_clock::now();
    for (auto i = 0; i < dimension; i++)
    {
        bst_test.find(i+1);
    }
    auto t4 = std::chrono::high_resolution_clock::now();

    auto interval2 = std::chrono::duration_cast<microseconds> (t4-t3);
    std::cout << "Time for finding all the key for balanced bst tree\n";
    std::cout << interval2.count() << " microseconds" << std::endl;
    
    auto t5 = std::chrono::high_resolution_clock::now();
    for (auto i = 0; i < dimension; i++)
    {
        map_test.find(i+1);
    }
    auto t6 = std::chrono::high_resolution_clock::now();

    auto interval3 = std::chrono::duration_cast<microseconds> (t6-t5);
    std::cout << "Time for finding all the key for map tree\n";
    std::cout << interval3.count() << " microseconds" << std::endl;

}

/*random generator between 0 and i*/
int random_seed(int i) {

    return std::rand()%i;
}


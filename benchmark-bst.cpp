/*
*Author: Rodolfo Tolloi, Giulia Bernardi.
*
*Purpouse:   this program performs a benchmark between our 
* implementation of BST and the standard function std::map.
*
*Date: May, 2021.
*/


#include"include/node.hpp"
#include"include/iterator.hpp"
#include"include/bst.hpp"
#include<iostream>
#include <functional>
#include <utility>
#include<map>
#include<algorithm>
#include<random>
#include<ctime>
#include<chrono>
#include<fstream>

int random_seed (int i);


int main () {
    bst<int, int, std::less<int> > bst_test;
    std::map <int, int> map_test;
    std::vector<int> nodes_key;
    std::vector<std::pair <int, int> > nodes_pair;

    using std::chrono::microseconds;

    /*It's common pratice to initialize the seed for rand
    to the current unix timestamp*/
    srand(time(0));

    int n;
    std::cout << "How many tests ? Put an int " << std::endl;
    std::cin >> n;

    std::vector<int> dimension {};

    for (auto i = 0; i < n; i++)
    {
        int tmp;
        std::cout<< "Dimension of the tree, test number " << i << std::endl;
        std::cin >> tmp;
        dimension.push_back(tmp);
    }  
    
    for (auto n_run = 0; n_run < n; n_run++)
    {
    
        for (auto i = 0; i < dimension[n_run]; ++i)
        {
            nodes_key.push_back(i+1);
        }

        std::random_shuffle(nodes_key.begin(), nodes_key.end(), random_seed);

        for (auto i = 0; i < dimension[n_run]; i++)
        {
            nodes_pair.push_back(std::make_pair(nodes_key[i], i+1));
        }
    
        for (auto i = 0; i < dimension[n_run]; i++)
        {
        bst_test.insert(nodes_pair[i]);
        map_test.insert(nodes_pair[i]);
        }

        auto t1 = std::chrono::high_resolution_clock::now();
        for (auto i = 0; i < dimension[n_run]; i++)
        {
            bst_test.find(i+1);
        }
        auto t2 = std::chrono::high_resolution_clock::now();

        auto interval1 = std::chrono::duration_cast<microseconds> (t2-t1);
        std::cout << "Time for finding all the key for unbalanced bst tree\n";
        std::cout << interval1.count() << " microseconds" << std::endl;

        bst_test.balance();
        auto t3 = std::chrono::high_resolution_clock::now();
        for (auto i = 0; i < dimension[n_run]; i++)
        {
            bst_test.find(i+1);
        }
        auto t4 = std::chrono::high_resolution_clock::now();

        auto interval2 = std::chrono::duration_cast<microseconds> (t4-t3);
        std::cout << "Time for finding all the key for balanced bst tree\n";
        std::cout << interval2.count() << " microseconds" << std::endl;
    
        auto t5 = std::chrono::high_resolution_clock::now();
        for (auto i = 0; i < dimension[n_run]; i++)
        {
            map_test.find(i+1);
        }
        auto t6 = std::chrono::high_resolution_clock::now();

        auto interval3 = std::chrono::duration_cast<microseconds> (t6-t5);
        std::cout << "Time for finding all the key for map tree\n";
        std::cout << interval3.count() << " microseconds" << std::endl;

        std::ofstream myFile("benchmark_results.txt", std::ios::app);
        myFile << "Number of nodes =  " << dimension[n_run] <<std::endl;
        myFile << "bst  " << interval1.count() << std::endl;
        myFile << "bst balanced  " << interval2.count() << std::endl;
        myFile << "map  " << interval3.count() << std::endl;
        myFile.close();

        bst_test.clear();
        nodes_key.clear();
        nodes_pair.clear();
    }
}

/*random generator between 0 and i*/
int random_seed(int i) {

    return std::rand()%i;
}


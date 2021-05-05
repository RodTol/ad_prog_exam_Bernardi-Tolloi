#include <iostream>
#include <vector>
#include <numeric>
#include <fstream>
#include <algorithm>

int main(){
	int mid_length;

	double mean;
	double median;
	double sum;
	
	std::vector<double> temp;
	
	std::ifstream temp_file("temperatures.txt");
	if (temp_file) {        
    		double value;

    		// read the elements in the file into a vector  
    		while ( temp_file >> value ) {
        		temp.push_back(value);
    		}
	}
	
	sum = std::accumulate(temp.begin(), temp.end(), decltype(temp)::value_type(0));
	
	mean = sum/temp.size();
	std::cout << "The mean is " << mean << std::endl;
	
	
	std::sort(temp.begin(), temp.end());
	mid_length = int(temp.size()/2);
	
	median = temp[mid_length];
	std::cout << "The median is " << median << std::endl;
                               

}

#include <iostream>
#include <array>
#include <utility>

std::array<double,16> transpose(std::array<double,16> Matrix);
int main(){

	//Matrice 4x4	
	std::array<double,16> Matrix;
	std::cout << "Insert the values of the 4x4 matrix row-wise: "<< std::endl;
	for(int i=0;i<16;++i){
		std::cin >> Matrix[i];
	}
	std::cout << "\nEntered Matrix: " << std::endl;
	for (int j=0;j<16;++j){
			std::cout << Matrix[j];
			if (((j+1)%4==0)&&(j!=0)){std::cout << "\n";}
	}

	std::array<double,16> t_Matrix;	
	t_Matrix = transpose(Matrix);
	std::cout << "\nTransposed Matrix: " << std::endl;
	for (int j=0;j<16;++j){
			std::cout << t_Matrix[j];
			if (((j+1)%4==0)&&(j!=0)){std::cout << "\n";}
	}
}

std::array<double,16> transpose(std::array<double,16> Matrix){

	
	for (int i=0;i<4;++i){
		for (int j=i;j<4;++j){
			std::swap(Matrix[4*i+j],Matrix[4*j+i]);
		}
	}
	return Matrix;	
}


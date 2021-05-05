#include <iostream>
#include <string>
#include <vector>

int main(){	
	
	std::size_t size;
	std::string str;
	std::vector<std::string> words;
	
	std::cout << "How many words do you want to insert? " << std::endl;
	std::cin >> size;
	
	std::cout << "Insert the sequence of words: " << std::endl;
	for (int i=0;i<size;++i){
		std::cin >> str;
		words.push_back(str);
	}
	
	std::vector<bool> flag(size,false); 
	
	for (int i=0;i<size;++i){
		for (int j=0;j<size;++j){
			if((words[i]==words[j])&&(flag[i]==false)&&(flag[j]==false)&&(i!=j)){
				flag[j] = true;
			}
		}
	}
	
	std::cout << "The words without repetitions are:" << std::endl;
	for (int i=0;i<size;++i){
		if (flag[i]==false){
			std::cout << words[i] << "\n";
		}
	}
}

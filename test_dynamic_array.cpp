#include <iostream>
#include "dynamic_array.h"


void print(const DynamicArray<int>& vec) {
	std::cout << "Size: " << vec.size() << ". Entries: ";
	for (size_t i = 0; i < vec.size(); ++i) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;	
}

int main() {
	// Initializer-list assignment constructor.
	DynamicArray<int> vec = {1,2,3,4,5};
	print(vec);
	
	int arr[] = {5,4,3,2,1};
	// Range-based constructor.
	DynamicArray<int> vec2(arr, arr + sizeof(arr)/sizeof(int));
	print(vec2);

	// Copy assignement.
	DynamicArray<int> vec3 = vec;
	vec3.push_back(6);
	vec3.push_back(7);
	print(vec3);
	std::cout<< "Front: " << vec3.front() << ". Back: " << vec3.back() << std::endl;

	vec3.pop_back();
	vec3.pop_back();
	vec3.pop_back();
	print(vec3);

	vec3.resize(10);
	print(vec3);
	
	vec.push_back(6);
	vec.push_back(7);
	vec.push_back(8);
	vec.push_back(9);
	vec.push_back(10);
	vec.push_back(11);
	print(vec);
	
	return 0;
}

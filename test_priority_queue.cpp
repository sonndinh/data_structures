#include <iostream>
#include <functional>
#include <utility>
#include "priority_queue.h"


template <typename T, typename Compare>
void print(PriorityQueue<T, Compare>& queue) {
	int size = queue.size();
	for (int i = 0; i < size; ++i) {
		std::cout << queue.top() << " ";
		queue.pop();
	}
	std::cout << std::endl;	
}

struct CustomLess {
	bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) const {
		return a.first < b.first;
	}
};

int main() {
	int arr[]  = {3,5,6,1,6,7,1,6,63,8,2,3};
	PriorityQueue<int> min_queue(arr, arr + sizeof(arr)/sizeof(int));
	
	std::cout << "Ascending order: ";
	print(min_queue);

	PriorityQueue<int, std::greater<int>> max_queue(arr, arr + sizeof(arr)/sizeof(int));
	std::cout << "Descending order: ";
	print(max_queue);

	PriorityQueue<std::pair<int, int>, CustomLess> custom_queue;
	custom_queue.push({3,0});
	custom_queue.push({1,0});
	custom_queue.push({-1,0});
	custom_queue.push({10,0});
	custom_queue.push({7,0});
	custom_queue.push({4,0});
	custom_queue.push({2,0});
	custom_queue.push({9,0});
	std::cout << "Custom queue - ascending order: ";

	int size = custom_queue.size();
	for (int i = 0; i < size; ++i) {
		const std::pair<int, int>& t = custom_queue.top();
		std::cout << "[" << t.first << "," << t.second << "] ";
		custom_queue.pop();
	}
	std::cout << std::endl;	
	
	return 0;
}

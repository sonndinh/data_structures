#include <vector>

using namespace std;

// Implement a max-priority queue using a max-binary heap.
template <typename T>
class PriorityQueue {
public:
	PriorityQueue() {
		arr = new T[INIT_CAP];
		capacity = INIT_CAP;
		heap_size = 0;
	}

	PriorityQueue(const PriorityQueue& rhs) {
		size = rhs.size();
		capacity = size;
		arr = new T[size];
		for (size_t i = 0; i < size; i++) {
			
		}
	}

	PriorityQueue(PriorityQueue&& rhs) {
	}

	~PriorityQueue() {
		delete[] arr;
	}

	// Return the number of elements in queue.
	size_t size() {
		return heap_size;
	}

	bool empty() {
		return heap_size == 0;
	}

	// Return reference to the maximum entry.
	const T& top() {
	}

	// Remove the top entry from the queue.
	void pop() {
	}

	// Insert a new entry.
	void push(const T& t) {
	}

private:
	size_t parent(size_t i) {
	}

	size_t left(size_t i) {
	}

	size_t right(size_t i) {
	}
	
	void heapify(size_t i) {
	}

	void build_heap() {
	}
	
private:
	T *arr[];
	size_t capacity;
	size_t heap_size;
	static const size_t INIT_CAP = 64;
};

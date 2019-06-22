#include <functional> // std::less
#include <vector>

// Implement using binary heap. Default is min-priority queue.
// STL vector is used as the internal store.
template <typename T, typename Compare = std::less<T>>
class PriorityQueue {
public:
	// Default constructor.
	PriorityQueue(const Compare& comp = Compare()) : comp_(comp) {}

	// Initialize through iterator.
	template <typename InputIterator>
	PriorityQueue(InputIterator first, InputIterator last, const Compare& comp = Compare()) : data_(first, last), comp_(comp) {
		build_heap();
	}
	
	// Copy constructor.
	PriorityQueue(const PriorityQueue& rhs, const Compare& comp = Compare()) : data_(rhs.data_), comp_(comp) {}

	// Move constructor.
	PriorityQueue(PriorityQueue&& rhs, const Compare& comp = Compare()) : data_(rhs.data_), comp_(comp) {}

	~PriorityQueue() {}

	// Return the number of elements in queue.
	size_t size() const {
		return data_.size();
	}

	bool empty() const {
		return data_.empty();
	}

	// Return a constant reference to the top entry.
	const T& top() const {
		return data_.front();
	}

	// Remove the top entry from the heap.
	void pop();

	// Insert a new entry.
	void push(const T& t);

private:
	// Return index of the parent index for entry i.
	size_t parent(size_t i) const {
		return (i - 1)/2;
	}

	// Return index of the left child for entry i.
	size_t left(size_t i) const {
		return (2*i + 1);
	}

	size_t right(size_t i) const {
		return (2*i + 2);
	}

	// Assuming the left and right subtrees satisfy heap property.
	void heapify(size_t i);

	// Build heap from an array of entries.
	void build_heap();
	
private:
	// The top element is always the first element.
	std::vector<T> data_;

	// A functor for comparing two elements.
	Compare comp_;
};


template <typename T, typename Compare>
void PriorityQueue<T, Compare>::pop() {
	// Do nothing if the heap is empty.
	if (data_.empty())
		return;
	
	int last = data_.size() - 1;
	std::swap(data_[0], data_[last]);
	data_.pop_back();
	heapify(0);
}

template <typename T, typename Compare>
void PriorityQueue<T, Compare>::push(const T& t) {
	data_.push_back(t);
	
	// Float the new entry upward the tree.
	int curr = data_.size() - 1;
	while (curr > 0 && comp_(data_[curr], data_[parent(curr)])) {
		std::swap(data_[curr], data_[parent(curr)]);
		curr = parent(curr);
	}
}

template <typename T, typename Compare>
void PriorityQueue<T, Compare>::heapify(size_t i) {
	size_t l = left(i);
	size_t r = right(i);
	size_t top = i;
	
	if (l < data_.size() && comp_(data_[l], data_[i])) {
		top = l;
	}
	
	if (r < data_.size() && comp_(data_[r], data_[top])) {
		top = r;
	}
	
	if (top != i) {
		std::swap(data_[i], data_[top]);
		heapify(top);
	}
}

template <typename T, typename Compare>
void PriorityQueue<T, Compare>:: build_heap() {
	int size = data_.size();
	for (int i = (size - 2)/2; i >= 0; --i) {
		heapify(i);
	}
}

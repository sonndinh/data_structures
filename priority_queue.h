#include <functional>
#include <vector>

// Implement using binary heap. Default is min-priority queue.
// STL vector is used as the internal store.
template <typename T, typename Compare = std::less<T>>
class PriorityQueue {
public:
	PriorityQueue(const Compare& comp = Compare()) : comp_(comp) {}

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

	// Return a reference to the top entry.
	T& top() const {
		return data_.front();
	}

	// Remove the top entry from the heap.
	void pop() {
		// Do nothing if the heap is empty.
		if (data_.empty())
			return;

		int last = data_.size() - 1;
		swap(data_[0], data_[last]);
		data_.pop_back();
		heapify(0);
	}

	// Insert a new entry.
	void push(const T& t) {
		data_.push_back(t);
		int last = data_.size() - 1;
		swap(data_[0], data_[last]);
		heapify(0);
	}

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
	void heapify(size_t i) {
		size_t l = left(i);
		size_t r = right(i);
		size_t largest = i;
		
		if (l < data_.size() && comp_(data_[i], data_[l])) {
			largest = l;
		}
		if (r < data_.size() && comp_(data_[largest], data_[r])) {
			largest = r;
		}

		if (largest != i) {
			swap(data_[i], data_[largest]);
			heapify(largest);
		}
	}

	// Build heap from an array of entries.
	void build_heap() {
		int size = data_.size();
		for (int i = (size - 2)/2; i >= 0; --i) {
			heapify(i);
		}
	}
	
private:
	// The top element is always the first element.
	std::vector<T> data_;

	// A functor for comparing two elements.
	Compare comp_;
};

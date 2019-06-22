#include <initializer_list>


// Implementation of dynamic-sized array, similar to STL vector.
template <typename T>
class DynamicArray {
public:
	// Default constructor.
	DynamicArray() {
		size_ = 0;
		capacity_ = DEFAULT_CAP;
		arr_ = new T[capacity_];
	}

	// Copy constructor.
	DynamicArray(const DynamicArray& that) {
		size_ = that.size();
		capacity_ = that.capacity();
		arr_ = new T[capacity_];
		
		for (int i = 0; i < size_; ++i) {
			*(arr_ + i) = that[i];
		}
	}

	// Move constructor.
	DynamicArray(DynamicArray&& that) {
		size_ = that.size();
		capacity_ = that.capacity();
		arr_ = that.arr_;
		that.arr_ = nullptr;
	}

	// Construct from initializer list.
	DynamicArray(std::initializer_list<T> il) {}

	// Construct from input iterators.
	template <InputIterator>
	DynamicArray(InputIterator first, InputIterator last) {}

	// Destructor.
	~DynamicArray() {
		if (arr_)
			delete[] arr_;
	}

	// Copy assign.
	DynamicArray& operator= (const DynamicArray& that) {
		size_ = that.size();
		capacity_ = that.capacity();
		arr_ = new T[capacity_];

		for (size_t i = 0; i < size_; ++i) {
			*(arr_ + i) = that[i];
		}
		return *this;
	}

	// Move assign.
	DynamicArray& operator= (DynamicArray&& that) {
		size_ = that.size();
		capacity_ = that.capacity();
		arr_ = that.arr_;
		that.arr_ = nullptr;
		return *this;
	}

	// Initializing assign.
	DynamicArray& operator= (std::initializer_list<T> il) {}

	// Return the number of entries.
	size_t size() const {
		return size_;
	}

	// Return whether the array is empty.
	bool empty() const {
		return (size_ == 0);
	}

	// Resize with a new size.
	void resize(size_t k) {
	}

	// Return the capacity.
	size_t capacity() const {
		return capacity_;
	}

	// Insert a new entry to the back.
	// Double the capacity if full.
	void push_back();

	// Remove the last entry.
	// Shink by half if there are less than a quarter of capacity occupied.
	void pop_back();

	// Return the first entry.
	T& front() const {
		return *arr_;
	}

	// Return the last entry.
	T& back() const {
		return *(arr_ + size_ - 1);
	}

	// Access entry at index pos. No bound checking.
	T& operator[] (size_t pos);

	// Similar but return constant reference.
	const T& operator[] (size_t pos) const;
	
private:
	static const size_t DEFAULT_CAP = 64;
	T *arr_;
	size_t size_;
	size_t capacity_;
};

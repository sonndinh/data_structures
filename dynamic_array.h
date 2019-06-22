#include <iostream>
#include <initializer_list>
#include <iterator> // std::distance


// Implementation of dynamic-sized array, similar to STL vector.
template <typename T>
class DynamicArray {
public:
	// Default constructor.
	DynamicArray() {
		size_ = 0;
		capacity_ = DEFAULT_CAP;
		arr_ = new T[capacity_]{};
	}

	// Copy constructor.
	DynamicArray(const DynamicArray& that) {
		size_ = that.size();
		capacity_ = that.capacity();
		arr_ = new T[capacity_]{};
		
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
	DynamicArray(std::initializer_list<T> il) {
		size_ = il.size();
		capacity_ = 2 * size_;
		arr_ = new T[capacity_]{};

		size_t i = 0;
		for (typename std::initializer_list<T>::iterator it = il.begin(); it != il.end(); ++it) {
			*(arr_ + i) = *it;
			++i;
		}
	}

	// Construct from input iterators.
	template <typename InputIterator>
	DynamicArray(InputIterator first, InputIterator last) {
		size_ = std::distance(first, last);
		capacity_ = 2 * size_;
		arr_ = new T[capacity_]{};

		size_t i = 0;
		for (InputIterator it = first; it != last; ++it) {
			*(arr_ + i) = *it;
			++i;
		}
	}

	// Destructor.
	~DynamicArray() {
		if (arr_)
			delete[] arr_;
	}

	// Copy assign.
	DynamicArray& operator= (const DynamicArray& that) {
		size_ = that.size();
		capacity_ = that.capacity();
		arr_ = new T[capacity_]{};

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
	DynamicArray& operator= (std::initializer_list<T> il) {
		size_ = il.size();
		capacity_ = 2 * size_;
		arr_ = new T[capacity_]{};

		size_t i = 0;
		for (typename std::initializer_list<T>::iterator it = il.begin(); it != il.end(); ++it) {
			*(arr_ + i) = *it;
			++i;
		}		
	}

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
		if (k < size_) {
			for (size_t i = k; i < size_; ++i) {
				arr_[i].~T();
			}
		} else if (k > size_ && k < capacity_) {
			for (size_t i = size_; i < k; ++i) {
				new (arr_ + i) T{};
			}
		} else if (k >= capacity_) {
			capacity_ = k + 1;
			copy_to_new_array();
		}
		size_ = k;
	}

	// Return the capacity.
	size_t capacity() const {
		return capacity_;
	}

	// Insert a new entry to the back.
	// Double the capacity if full.
	void push_back(const T& t) {
		arr_[size_++] = t;

		// Double the capacity.
		if (size_ == capacity_) {
			double_capacity();
		}
	}

	// Similar but with an rvalue.
	void push_back(T&& t) {
		arr_[size_++] = t;

		if (size_ == capacity_) {
			double_capacity();
		}
	}

	// Remove the last entry.
	// Shrink by half if there are less than a quarter of capacity occupied.
	void pop_back() {
		if (size_ == 0)
			return;

		--size_;
		arr_[size_].~T();

		// Shrink the capacity by half.
		if (size_ < capacity_/4) {
			halve_capacity();
		}
	}

	// Return the first entry.
	T& front() const {
		return *arr_;
	}

	// Return the last entry.
	T& back() const {
		return *(arr_ + size_ - 1);
	}

	// Access entry at index pos. No bound checking.
	T& operator[] (size_t pos) {
		return arr_[pos];
	}

	// Similar but return constant reference.
	const T& operator[] (size_t pos) const {
		return arr_[pos];
	}

private:
	void double_capacity() {
		capacity_ *= 2;
		copy_to_new_array();
	}
	
	void halve_capacity() {
		capacity_ /= 2;
		copy_to_new_array();
	}

	void copy_to_new_array() {
		T *temp = new T[capacity_]{};
		for (size_t i = 0; i < size_; ++i) {
			temp[i] = arr_[i];
			// NOTE: should I expicitly call destructor for each entry in arr_.
			arr_[i].~T();
		}
		delete[] arr_;
		arr_ = temp;		
	}
	
private:
	static const size_t DEFAULT_CAP = 4;
	T *arr_;
	size_t size_;
	size_t capacity_;
};

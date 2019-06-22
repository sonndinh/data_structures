#include <cstdlib>
#include <string>


template <typename T>
class CircularQueue {	
public:
    CircularQueue(int size) {
		arr = new T[size];
		head = 0;
		tail = 0;
		capacity = size;
		counter = 0;
    }
	
    ~CircularQueue() {
		delete[] arr;
    }

	size_t size() {
		return counter;
	}

	bool empty() {
		return counter == 0;
	}
	
	// Return reference to the next item.
	const T& top() {
		if (counter == 0) {
			throw std::length_error("ERROR: Queue is empty!");
		}
		return *(arr + head);
	}
	
	// Remove the top item from the queue.
	void pop() {
		if (counter == 0) {
			throw std::length_error("ERROR: Queue is empty!");
		}
		head++;
		head = head % capacity;
		counter--;
    }
	
    void push(const T& msg) {
        if (tail == head && counter > 0) {
			throw std::length_error("ERROR: Queue is full!");
        }		
        arr[tail] = msg;
        tail++;
        tail = tail % capacity;
        counter++;
    }

private:
	T *arr;
    int head;
    int tail;
    int capacity;
    int counter;	
};

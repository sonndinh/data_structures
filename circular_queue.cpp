#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

// A circular buffer.
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
			throw length_error("ERROR: Queue is empty!");
		}
		return *(arr + head);
	}
	
	// Remove the top item from the queue.
	void pop() {
		if (counter == 0) {
			throw length_error("ERROR: Queue is empty!");
		}
		head++;
		head = head % capacity;
		counter--;
    }
	
    void push(const T& msg) {
        if (tail == head && counter > 0) {
			throw length_error("ERROR: Queue is full!");
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


struct Message {
	string data;
};

const unsigned CAPACITY = 10;
int main() {
	CircularQueue<struct Message> buffer(CAPACITY);
	
	for (int i = 0; i < CAPACITY+1; i++) {
		string str = "Hello world " + to_string(i);
		struct Message msg = {str};
		try {
			buffer.push(msg);
		} catch (exception &ex) {
			cout << ex.what() << endl;
		}
	}
	
	for (int i = 0; i < CAPACITY+1; i++) {
		try {
			const struct Message& msg = buffer.top();
			cout << "Message: " << msg.data << endl;
			buffer.pop();
		} catch (exception &ex) {
			cout << ex.what() << endl;
		}
	}
	
	return 0;
}

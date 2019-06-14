#include "circular_queue.h"


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

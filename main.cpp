/*
 * main.cpp
 *
 *  Created on: Jul 13, 2015
 *      Author: Greg Silverman
 */
namespace std {
}
;
using namespace std;

#include <iostream>
#include <utility>

class CircularArray {
private:
	int *data;
	int size;
	int readPos;
	int entries;
public:
	CircularArray(int p_size) {
		size = p_size;
		data = new int[size];
		readPos = 0;
		entries = 0;

	}
	bool put(int p_value) {
		if (entries < size) {
			++entries;
			data[entries % size] = p_value;
			return true;
		} else {
			return false;
		}
	}
	pair<int, bool> get() {
		if (entries == 0) {
			return pair<int, bool>(0, false);
		} else {
			pair<int, bool> rc(data[readPos++], true);
			readPos = (readPos + 1) % size;
			--entries;
			return rc;
		}
	}
};

int main() {
	cout << boolalpha;
	CircularArray ca(1);
	cout << ca.put(1) << endl;
	cout << ca.put(2) << endl;
	cout << ca.get().first << "," << ca.get().second << endl;
	cout << ca.get().first << "," << ca.get().second << endl;
	return 0;
}

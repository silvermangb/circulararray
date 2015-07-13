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
#include <vector>
#include <stdexcept>
#include <sstream>

class CircularArray {
private:
	int *_data;
	int _size;
	int _readPos;
	int _entries;
public:
	~CircularArray() {
		delete [] _data;
	}
	CircularArray(int p_size) {
		_size = p_size;
		_data = new int[_size];
		_readPos = 0;
		_entries = 0;

	}
	bool put(int p_value) {
		if (_entries < _size) {
			_data[(_readPos+_entries) % _size] = p_value;
			++_entries;
			return true;
		} else {
			return false;
		}
	}
	pair<int, bool> get() {
		if (_entries == 0) {
			return pair<int, bool>(0, false);
		} else {
			pair<int, bool> rc(_data[_readPos++], true);
			_readPos %= _size;
			--_entries;
			return rc;
		}
	}
	int capacity() {
		return this->_size;
	}
	int size() {
		return this->_entries;
	}
};

using TestSignature = void (*)();

vector<TestSignature> tests;

void
test0
  ()
{
	CircularArray ca(16);
	int falseCount = 0;
	int trueCount = 0;
	for(int i=0;i<2*ca.capacity();++i) {
		if(ca.put(i)) {
			++trueCount;
		} else {
			++falseCount;
		}
	}
	if(falseCount!=trueCount) {
		throw "error";
	}
	falseCount = 0;
	trueCount  = 0;
	for(int i=0;i<2*ca.capacity();++i) {
		pair<int,bool> rc = ca.get();
		if(rc.second) {
			++trueCount;
			if(rc.first!=i) {
				throw "error";
			}
		} else {
			++falseCount;
		}
	}
	if(trueCount!=falseCount) {
		throw "error";
	}
}

void
test1
  ()
{
	CircularArray ca(4);
	bool putRc;
	pair<int,bool> getRc;
	for(int i=0;i<2*ca.capacity();++i) {
		putRc = ca.put(i);
		if(!putRc) {
			throw "error";
		}
		getRc = ca.get();
		if(!getRc.second) {
			throw "error";
		}
		if(getRc.first!=i) {
			throw "error";
		}
	}
}

void
test2
  ()
{
	CircularArray ca(8);
	pair<int,bool> getRc;
	for(int i=0;i<8;++i) {
		ca.put(i);
	}
	int getValue = -1;
	for(int i=0;i<4;++i) {
		getRc = ca.get();
		if((getValue+1)!=getRc.first) {
			ostringstream oss;
			oss << __LINE__ << " " << (getValue+1) << "!=" << getRc.first << endl;
			throw runtime_error(oss.str());
		}
		getValue = getRc.first;
	}
	for(int i=8;i<(8+4);++i) {
		ca.put(i);
	}
	for(int i=0;i<ca.size();++i) {
		getRc = ca.get();
		if((getValue+1)!=getRc.first) {
			ostringstream oss;
			oss << __LINE__ << " " << (getValue+1) << "!=" << getRc.first << endl;
			throw runtime_error(oss.str());
		}
		getValue = getRc.first;
	}
}
int main() {
	cout << boolalpha;
	tests.push_back(test0);
	tests.push_back(test1);
	tests.push_back(test2);
	int successes = 0;
	int failures = 0;
	for(size_t i=0;i<tests.size();++i) {
		try
		{
			tests[i]();
			++successes;
		} catch(...) {
			cout << i << " failed" << endl;
			++failures;
		}
	}
	cout << successes << " successes " << "," << failures << " failures"<<endl;
	return 0;
}

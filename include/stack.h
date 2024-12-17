#ifndef __Stack_H__
#define __Stack_H__

#include <iostream>
#include <vector>

using namespace std;

template <class T>
class Stack
{
protected:
	vector<T> data;

public:
	void push(const T& val) {
		data.push_back(val);
	}
	void pop() {
		if (empty())
			throw "1";
		data.pop_back();
	}
	
	T& top(){
		if (empty())
			throw "1";
		return data.back();
	}

	bool empty() {
		return data.empty();
	}

	size_t size() {
		return data.size();
	}

};

#endif

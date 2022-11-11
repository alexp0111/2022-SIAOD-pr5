#ifndef TI
#define TI

#include <iostream>
using namespace std;

struct Item {
	int key;
	int address;

	Item(int key, int address) {
		this->key = key;
		this->address = address;
	}

	Item() {
		this->key = -1;
		this->address = -1;
	}

	int getKey() {
		return this->key;
	}

	int getAddress() {
		return this->address;
	}

	int setKey(int key) {
		this->key = key;
	}

	int setAddress(int address) {
		this->address = address;
	}

	Item& operator=(const Item& a)
	{
		this->key = a.key;
		this->address = a.address;
		return *this;
	}
};

#endif

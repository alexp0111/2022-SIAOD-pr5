#ifndef RC
#define RC

#include <iostream>
#include <string>
#include <istream>
using namespace std;

struct Record {
	int numOfTST;
	char nameOfTST[30];
	int arrOfTST[4];


	Record(int numOfTST, char nameOfTST[30], int arrOfTST[4]) {
		this->numOfTST = numOfTST;
		strncpy_s(this->nameOfTST, nameOfTST, 30);
		for (int i = 0; i < 4; i++) this->arrOfTST[i] = arrOfTST[i];
	}

	Record() {
		this->numOfTST = -1;
		strncpy_s(this->nameOfTST, "", 30);
		for (int i = 0; i < 4; i++) this->arrOfTST[i] = -1;
	}

	Record& operator=(const Record& a)
	{
		this->numOfTST = a.numOfTST;
		strncpy_s(this->nameOfTST, a.nameOfTST, 30);
		for (int i = 0; i < 4; i++) this->arrOfTST[i] = a.arrOfTST[i];
		return *this;
	}
};


#endif

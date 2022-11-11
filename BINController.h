#ifndef BINC
#define BINC

#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <regex>
#include "BSTTree.h"
#include "Record.h"

using namespace std;

void getItem(Record);

void getItem(Record tt) {
	if (tt.numOfTST == -1) return;

	cout << tt.numOfTST << endl;
	cout << tt.nameOfTST << endl;
	for (int i = 0; i < 4; i++) cout << tt.arrOfTST[i] << endl;
}

int convertTXTtoBIN(ifstream&, ofstream&);
void outputBIN(ifstream&);
void showItemByNum(ifstream&, int);
void addItemToTheEnd(fstream&, int&);
int chToNum(char[]);
bool isNum(char[]);
void sww();

void sww() {
	cout << "Something went wrong while working on file" << endl;
}

int convertTXTtoBIN(ifstream& ft, ofstream& fb) {
	Record x;

	int counter = 0;

	while (!ft.eof())
	{
		ft >> x.numOfTST;
		ft.get();
		ft.getline(x.nameOfTST, 30);
		for (int i = 0; i < 4; i++) ft >> x.arrOfTST[i];

		counter++;
		fb.write((char*)&x, sizeof(Record));
	}
	
	return counter;
}

void outputBIN(ifstream& fb) {
	Record x;

	fb.read((char*)&x, sizeof(Record));
	while (!fb.eof())
	{
		getItem(x);
		fb.read((char*)&x, sizeof(Record));
	}
}

void showItemByNum(ifstream& fb, int ind) {
	Record x;
	fb.seekg(ind * sizeof(Record), ios::beg);
	fb.read((char*)&x, sizeof(Record));
	cout << "X: " << x.numOfTST << endl;
	getItem(x);
}

void addItemToTheEnd(fstream& f, int& size) {
	Record x;
	char input[6][30];
	bool flag = true;

	cout << "Enter data: " << endl;

	for (int i = 0; i < 6; i++)
	{
		char tmp = '\0';
		if (i != 1) {
			cin.get(tmp);
			cin.getline(input[i], 30);
		}
		else {
			cin.getline(input[i], 30);
		}

		if (tmp != '\0' && tmp != '\n') {
			memmove(input[i]+1, input[i], sizeof(input[i]));
			input[i][0] = tmp;
		}


		if ((i != 1) && (!isNum(input[i])))
		{
			cout << "Incorrect input" << endl;
			return;
		}
	}

	x.numOfTST = chToNum(input[0]);
	strncpy_s(x.nameOfTST, input[1], 30);
	for (int i = 0; i < 4; i++) x.arrOfTST[i] = chToNum(input[2+i]);

	size++;

	f.write((char*)&x, sizeof(Record));
}

int chToNum(char input[]) {
	int i = 0, res = 0;
	string tmp = "";
	while (input[i] != '\0')
	{
		tmp += input[i]; i++;
	}
	return stoi(tmp.c_str());
}

bool isNum(char input[]) {
	int i = 0;
	while (input[i] != '\0')
	{
		if (!(((int)input[i] > 47) && ((int)input[i] < 58)))
			return false;
		i++;
	}
	return true;
}

#endif

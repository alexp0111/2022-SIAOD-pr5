#include <iostream>
#include "BSTTree.h"
#include "RBTTree.h"
#include "BINController.h"

// TODO: While adding new element -> add it to tree (without calling another function)
// TODO: Do not forget to add [count timer]


void info() {
	cout << "Практическая работа №5 ИКБО-06-21 Петровский А.А. Вариант 16" << endl << endl;
	cout << "Меню\n";
	cout << "1) Конвертировать текстовый файл в бинарный" << endl;
	cout << "2) Создать дерево по бинарному файлу" << endl;
	cout << "3) Вывести дерево" << endl;
	cout << "4) Добавить элемент в файл" << endl;
	cout << "5) Удалить элемент дерева по ключу" << endl;
	cout << "6) Вывести запись по адресу в файле" << endl;
	cout << "7) Вывести запись по ключу в дереве" << endl;
	cout << "8**) ТЕСТ: Сформировать файл с кол-вом записей" << endl;
	cout << "0) Выход" << endl;
	cout << "Ваш выбор: ";
}

int main()
{
	setlocale(0, "Russian");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 8);

	// Deciding type of tree
	system("cls");
	int type = 0;
	cout << "Enter 1, to work with BST. Enter 2 to work with RBT: ";
	cin >> type;
	//
	BSTTree bsttree;
	RBTTree rbtree;
	system("cls");

	//
	string filenameTXT = "Data.txt", filenameBIN = "Conv.bin";
	int numberOfItems = 0;
	//

	int flag = 100;
	while (flag != 0) {
		system("cls");
		SetConsoleTextAttribute(hConsole, 8);
		info();
		cin >> flag;
		system("cls");

		cout << "Практическая работа №4 ИКБО-06-21 Петровский А.А. Вариант 16" << endl << endl;

		switch (flag)
		{
		case 1: {
			ifstream fin;
			ofstream foutb;

			fin.open(filenameTXT, ios::in);
			foutb.open(filenameBIN, ios::out | ios::binary);

			if ((!foutb.is_open()) || (!fin.is_open())) { sww(); return 1; }

			numberOfItems = convertTXTtoBIN(fin, foutb);

			fin.clear();
			foutb.clear();

			if (foutb.good() && fin.good()) {
				fin.close();
				foutb.close();
			}

			if (numberOfItems == -1) {
				sww();
				system("pause");
				break;
			}
			else {
				cout << "Done" << endl;
			}

			system("pause");
			break;
		}
		case 2: {
			ifstream fin;
			fin.open(filenameBIN, ios::in | ios::binary);
			if (!fin.is_open()) { sww(); return 1; }
			//
			if (type == 1) {
				bsttree.root = nullptr;
				bsttree.buildTreeFromFile(fin);
			}
			else {
				rbtree.root = nullptr;
				rbtree.buildTreeFromFile(fin);
			}

			//
			fin.clear();

			if (fin.good()) {
				fin.close();
			}
			else sww();

			system("pause");
			break;
		}
		case 3: {
			cout << "Tree" << endl;
			if (type == 1)
				bsttree.print(bsttree.root, 0);
			else rbtree.print(rbtree.root, 0);

			system("pause");
			break;
		}
		case 4: {
			//Add to file

			fstream f;
			f.open(filenameBIN, ios::app | ios::out | ios::binary);

			if (!f) { sww(); return 1; }

			addItemToTheEnd(f, numberOfItems);

			f.clear();

			if (f.good()) {
				f.close();
			}
			else sww();

			system("pause");
			break;
		}
		case 5: {
			// Delete by key
			int key = 0;
			cout << "Enter key: ";
			cin >> key;

			if (type == 1) bsttree.deleteByKey(key);
			else rbtree.deleteByKey(key);

			system("pause");
			break;
		}
		case 6: {
			// Output record by address in file
			int address;
			cout << "Enter address (Order number): ";
			cin >> address;

			ifstream fin;
			fin.open(filenameBIN, ios::in | ios::binary);

			if (!fin.is_open()) { sww(); return 1; }

			showItemByNum(fin, address);

			if (fin.good()) {
				fin.clear();
				fin.close();
			}
			else sww();

			system("pause");
			break;
		}
		case 7: {
			// Output record by key in tree
			int key;
			cout << "Enter key: ";
			cin >> key;

			ifstream fin;
			fin.open(filenameBIN, ios::in | ios::binary);

			if (!fin.is_open()) { sww(); return 1; }

			Item item;
			if (type == 1)
			item = bsttree.getItemByKey(key, bsttree.root);
			else item = rbtree.getItemByKey(key, rbtree.root);

			showItemByNum(fin, item.address);

			fin.clear();

			if (fin.good()) {
				fin.close();
			}
			else sww();

			system("pause");
			break;
		}
		case 8: { // Big file forming
			int NUM_OF_RECORDS = 100000;

			bsttree.root = nullptr;
			rbtree.root = nullptr;
			char input[] = { 'q', 'w', 'e', 'r', 't', 'y' };
			fstream f;
			f.open(filenameBIN, ios::out | ios::binary);

			f.clear();

			for (int i = 0; i < NUM_OF_RECORDS; i++)
			{
				Record x;

				x.numOfTST = NUM_OF_RECORDS -i;
				strncpy_s(x.nameOfTST, input, 6);
				x.arrOfTST[0] = i % 10;
				x.arrOfTST[1] = i % 20;
				x.arrOfTST[2] = i % 30;
				x.arrOfTST[3] = i % 40;

				Item tmp = Item(x.numOfTST, i);
				if (type == 1) {
					bsttree.push(tmp);
				}
				else {
					rbtree.InsertInRBTree(tmp);
				}

				f.write((char*)&x, sizeof(Record));
			}

			f.clear();

			if (f.good()) {
				f.close();
			}
			else sww();

			system("pause");
			break;
		}
		default:
			break;
		}
	}
}

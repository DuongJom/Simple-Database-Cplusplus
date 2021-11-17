#include<iostream>
#include<string.h>
#include "Table.cpp"
#define MAX 100
using namespace std;

class Database {
public:
	char databaseName[50];
	int numberOfTable;
	Table tables[MAX];

	Database() {}

	Database(char _databaseName[], int _numOfTable, Table _tables[]) {
		strcpy_s(databaseName, sizeof(databaseName) / sizeof(char), _databaseName);
		numberOfTable = _numOfTable;
		for (int i = 0; i < _numOfTable; i++) {
			tables[i] = _tables[i];
		}
	}

	bool checkDatabaseExist(char tableName[], Table _tables[], int n) {
		for (int i = 0; i < n; i++) {
			if (strcmp(_tables[i].tableName, tableName) == 0) {
				return true;
			}
		}
		return false;
	}

	void inputDatabase() {
		cout << "Enter database name: ";
		cin >> databaseName;
		cout << "Enter number of table: ";
		cin >> numberOfTable;
		for (int i = 0; i < numberOfTable; i++) {
			if (i > 0)
				cout << endl;
			tables[i].inputTable();
		}
	}

	void showDatabase() {
		cout << "Database: " << databaseName << endl;
		for (int i = 0; i < numberOfTable; i++) {
			tables[i].showTable();
		}
	}
};


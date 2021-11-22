#pragma once
#include "Table.h"
class Database {
public:
	char dbName[50];
	int numberOfTable;
	Table tables[10];

	Database() {
		strcpy_s(dbName, sizeof(dbName) / sizeof(char), "");
		numberOfTable = 0;
	}

	void inputDatabase() {
		cout << "Enter database name: ";
		cin >> dbName;
	}

	void addNewTable(Table table) {
		tables[numberOfTable++] = table;
		cout << "Complete successfully!" << endl;
	}

	bool checkTableExist(char table[]) {
		for (int i = 0; i < numberOfTable; i++) {
			if (strcmp(tables[i].tableName, table) == 0) {
				return true;
			}
		}
		return false;
	}

	void showTable(bool isFull) {
		cout << "Database name: " << dbName << endl;
		cout << "Executing query: " << endl;
		cout << "\tSHOW TABLES;" << endl;
		if (isFull == true) {
			for (int i = 0; i < numberOfTable; i++) {
				tables[i].showTable();
			}
		}
		else {
			char tableName[50];
		re_enter:
			cout << "Enter table name: ";
			cin >> tableName;

			if (checkTableExist(tableName) == false) {
				cout << "Invalid table!! Please type again!!" << endl;
				goto re_enter;
			}

			for (int i = 0; i < numberOfTable; i++) {
				if (strcmp(tables[i].tableName, tableName) == 0) {
					tables[i].showTable();
				}
			}
		}
		cout << "Complete successfully!" << endl;
	}

	int selectedIndexTable(char tableName[]) {
		for (int i = 0; i < numberOfTable; i++) {
			if (strcmp(tables[i].tableName, tableName) == 0) {
				return i;
			}
		}
		return -1;
	}

	void dropTable(char table[]) {
		if (checkTableExist(table) == false) {
			cout << "Invalid table!!" << endl;
		}
		else {
			int index = selectedIndexTable(table);
			for (int i = 0; i < numberOfTable; i++) {
				if (i == index) {
					for (int j = index; j < numberOfTable; j++) {
						tables[j] = tables[j + 1];
					}
				}
			}
			cout << "Complete successfully!" << endl;
		}
	}

	void showDatabase() {
		cout << "Database name: " << dbName << endl;
		for (int i = 0; i < numberOfTable; i++) {
			tables[i].showTable();
		}
		cout << "Complete successfully!" << endl;
	}
};
#include<iostream>
#include<string.h>
#include "Field.cpp"
#define MAX 100
using namespace std;

class Table {
public:
	char tableName[50];
	int numberOfField;
	Field fields[MAX];
	char primaryKey[50];
	int numberOfRecords;

	Table() {}

	Table(char _tableName[], int _numOfField, Field _fields[], char _key[]) {
		strcpy_s(tableName, sizeof(tableName)/sizeof(char), _tableName);
		numberOfField = _numOfField;
		for (int i = 0; i < _numOfField; i++) {
			fields[i] = _fields[i];
		}
		strcpy_s(primaryKey, sizeof(primaryKey)/sizeof(char), _key);
	}

	bool checkExistPrimaryKey(char key[], Field fields[], int n) {
		for (int i = 0; i < n; i++) {
			if (strcmp(fields[i].columnName, key) == 0) {
				return true;
			}
		}
		return false;
	}

	void inputTable() {
		cout << "\tEnter table name: ";
		cin >> tableName;
		cout << "\tEnter number of field: ";
		cin >> numberOfField;
		for (int i = 0; i < numberOfField; i++) {
			if (i > 0) {
				cout << endl;
			}
			fields[i].iuputField();
		}
		char key[50];
	re_enter:
		cout << "\tEnter primary key: ";
		cin >> key;
		if (checkExistPrimaryKey(key, fields, numberOfField) == true) {
			strcpy_s(primaryKey, sizeof(primaryKey) / sizeof(char), key);
		}
		else {
			cout << "Column name invalid!" << endl;
			goto re_enter;
		}
	}

	void showTable() {
		cout << tableName << "\n(\n";
		for (int i = 0; i < numberOfField; i++) {
			if (i == 0) {
				cout << "\n\t";
				fields[i].showField();
				if (strcmp(fields[i].columnName, primaryKey) == 0) {
					printf("%-15s", " PRIMARY KEY,");
				}
				else
					cout << ",";
			}
			else if (i > 0 && i < numberOfField - 1) {
				cout << "\n\t";
				fields[i].showField();
				if (strcmp(fields[i].columnName, primaryKey) == 0) {
					printf("%-15s", " PRIMARY KEY,");
				}
				else
					cout << ",";
			}
			else {
				cout << "\n\t";
				fields[i].showField();
				if (strcmp(fields[i].columnName, primaryKey) == 0) {
					printf("%-15s", " PRIMARY KEY");
				}
				cout << "\n)\n";
			}
		}
	}

	void insert() {
		cout << "Enter number of records: ";
		cin >> numberOfRecords;

		for (int i = 0; i < numberOfRecords; i++) {
			for (int j = 0; j < numberOfField; j++) {
				cout << "\tEnter " << fields[j].columnName << ": ";
				cin.getline(fields[j].value[i], 50);
			}
		}
	}

	void selectAll() {
		for (int i = 0; i < numberOfRecords; i++) {
			for (int j = 0; j < numberOfField; j++) {
				printf("|%20s", fields[j].value[i]);
			}
			cout << "|" << endl;
		}
	}
};
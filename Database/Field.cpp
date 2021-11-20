#include<iostream>
#include<string.h>
#define MAX 100
using namespace std;

class Field {
public:
	char columnName[50];
	char dataType[50];
	bool isNull;
	char* value[MAX];

	Field() {}

	Field(char _columnName[], char _dataType[], bool _isNull) {
		strcpy_s(columnName, sizeof(columnName)/sizeof(char), _columnName);
		strcpy_s(dataType, sizeof(dataType)/sizeof(char), _dataType);
		isNull = _isNull;
	}

	void iuputField() {
		cout << "\t\tEnter column name: ";
		cin >> columnName;
		cout << "\t\tEnter data type: ";
		cin >> dataType;
		cout << "\t\tEnter type of null(0: NOT NULL; 1: NULL): ";
		cin >> isNull;
	}

	void showField() {
		printf("%-15s\t%-15s\t", columnName, dataType);
		if (isNull == true) {
			printf("%-15s", "NULL");
		}
		else {
			printf("%-15s", "NOT NULL");
		}
	}
};
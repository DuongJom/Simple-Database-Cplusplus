#pragma once
#include <string.h>
#include <iostream>
using namespace std;

class Field {
public:
	char columnName[20];
	char dataType[20];
	int isNull;
	char value[10][100];
	int numberOfDataType = 9;
	char DATATYPE[10][50] = {
		"INT","DOUBLE","FLOAT","DECIMAL(18,0)","NUMERIC(15,0)",
		"VARCHAR(50)","NVARCHAR(50)",
		"DATE","DATETIME"
	};

	Field() {
		strcpy_s(columnName, sizeof(columnName) / sizeof(char), "");
		strcpy_s(dataType, sizeof(dataType) / sizeof(char), "VARCHAR(50)");
		isNull = 1;
	}

	bool checkValidDataType(char dataType[]) {
		for (int i = 0; i < numberOfDataType; i++) {
			if (strcmp(dataType, DATATYPE[i]) == 0) {
				return true;
			}
		}
		return false;
	}

	char* findSameDataType(char type[]) {
		int n = strlen(type);
		int count = 0;
		if (n > 4) {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < numberOfDataType; j++) {
					if (type[i] == DATATYPE[j][i]) {
						count++;
					}
					if (count == 5) {
						return DATATYPE[j];
					}
				}
			}
		}
		else if (n == 4) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < numberOfDataType; j++) {
					if (type[i] == DATATYPE[j][i]) {
						count++;
					}
					if (count == 4) {
						return DATATYPE[j];
					}
				}
			}
		}
		else {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < numberOfDataType; j++) {
					if (type[i] == DATATYPE[j][i]) {
						count++;
					}
					if (count == 3) {
						return DATATYPE[j];
					}
				}
			}
		}
		return DATATYPE[6];
	}

	void inputField() {
		cout << "\t\tEnter column name: ";
		cin >> columnName;
	re_enter_dt:
		cout << "\t\tEnter data type: ";
		cin >> dataType;
		if (checkValidDataType(dataType) == false) {
			cout << "Invalid data type!" << endl;
			cout << "Do you want " << findSameDataType(dataType) << " type?" << endl;
			goto re_enter_dt;
		}
	re_enter_null:
		cout << "\t\tEnter type of null(0: NOT NULL, 1: NULL): ";
		cin >> isNull;
		if (isNull != 0 && isNull != 1) {
			cout << "Invalid type of null! Please type again!!" << endl;
			goto re_enter_null;
		}
	}
};
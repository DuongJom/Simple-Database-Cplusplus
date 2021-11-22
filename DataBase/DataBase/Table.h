#pragma once
#include "Field.h"
class Table {
public:
	char tableName[20];
	int numberOfField;
	//Maximum: 10 fields
	Field field[10];
	char primaryKey[20];
	int numberOfRecords;

	Table() {
		strcpy_s(tableName, sizeof(tableName) / sizeof(char), "");
		numberOfField = 0;
		numberOfRecords = 0;
	}

	bool checkKeyExist(char key[]) {
		for (int i = 0; i < numberOfField; i++) {
			if (strcmp(field[i].columnName, key) == 0) {
				return true;
			}
		}
		return false;
	}

	void inputTable() {
		cout << "\tEnter table name: ";
		cin >> tableName;
		do {
			cout << "\tEnter number of fields: ";
			cin >> numberOfField;
			if (numberOfField <= 0 || numberOfField > 10) {
				cout << "Invalid number of field!" << endl;
			}
		} while (numberOfField <= 0 || numberOfField > 10);
		for (int i = 0; i < numberOfField; i++) {
			field[i].inputField();
			cout << endl;
		}
	re_enter:
		cout << "\tEnter primary key: ";
		cin >> primaryKey;
		if (checkKeyExist(primaryKey) == false) {
			cout << "Invalid column!! Please type again!!" << endl;
			goto re_enter;
		}
		for (int i = 0; i < numberOfField; i++) {
			if (strcmp(field[i].columnName, primaryKey) == 0) {
				field[i].isNull = 0;
			}
		}
	}

	void showTable() {
		cout << "Table name: " << tableName << endl;
		printf("+---------------+--------------------+---------------+-----------+\n");
		printf("|%-15s|%-20s|%-15s|%6s%5s|\n", "Primary Key", "Column name", "Data type", "Null", " ");
		printf("+---------------+--------------------+---------------+-----------+\n");
		for (int i = 0; i < numberOfField; i++) {
			if (strcmp(field[i].columnName, primaryKey) == 0) {
				printf("|%8s%7s|%-20s|%-15s|%6s%5s|\n", "PK", " ", field[i].columnName, field[i].dataType, field[i].isNull == 0 ? "N" : "Y", " ");
			}
			else {
				printf("|%8s%7s|%-20s|%-15s|%6s%5s|\n", "-", " ", field[i].columnName, field[i].dataType, field[i].isNull == 0 ? "N" : "Y", " ");
			}
		}
		printf("+---------------+--------------------+---------------+-----------+\n");
	}

	bool checkNumber(char value[], Field f) {
		int n = strlen(value);
		if (strcmp(f.dataType, "INT") == 0) {
			for (int i = 0; i < n; i++) {
				if (value[i] < '0' || value[i]>'9') {
					return false;
				}
			}
		}
		else if (strcmp(f.dataType, "DOUBLE") == 0 || strcmp(f.dataType, "FLOAT") == 0) {
			for (int i = 0; i < n; i++) {
				if ((value[i] < '0' || value[i]>'9') && value[i] != '.') {
					return false;
				}
			}
		}
		return true;
	}

	bool checkNullValue(char value[]) {
		if (strcmp(value, "") == 0) {
			return false;
		}
		return true;
	}

	void insertIntoTable() {
		for (int i = numberOfRecords; i < numberOfRecords + 1; i++) {
			for (int j = 0; j < numberOfField; j++) {
			re_enter:
				cout << "\tEnter " << field[j].columnName << ": ";
				cin.getline(field[j].value[i], sizeof(field[j].value[i]) / sizeof(char));
				if (field[j].isNull == 0) {
					if (checkNullValue(field[j].value[i]) == false) {
						cout << "Can't insert NULL value!! Please type again!!" << endl;
						goto re_enter;
					}
				}
				if (checkNumber(field[j].value[i], field[j]) == false) {
					cout << "Invalid value!! Please type again!!" << endl;
					goto re_enter;
				}
			}
		}
		cout << endl;
		cout << "Complete successfully!!" << endl;
		numberOfRecords++;
	}

	void selectAll() {
		cout << "Executing query:" << endl;
		cout << "\tSELECT *" << endl;
		cout << "\tFROM " << tableName << endl;

		for (int i = 1; i <= 21 * numberOfField + (numberOfField + 1); i++) {
			printf("%s", "+");
		}
		cout << endl;
		for (int i = 0; i < numberOfField; i++) {
			if (i < numberOfField - 1) {
				printf("|%-21s", field[i].columnName);
			}
			else {
				printf("|%-21s|\n", field[i].columnName);
			}
		}
		for (int i = 1; i <= 21 * numberOfField + (numberOfField + 1); i++) {
			printf("%s", "+");
		}
		cout << endl;
		if (numberOfRecords != 0) {
			for (int i = 0; i < numberOfRecords; i++) {
				for (int j = 0; j < numberOfField; j++) {
					if (j < numberOfField - 1) {
						printf("|%-21s", field[j].value[i]);
					}
					else {
						printf("|%-21s|\n", field[j].value[i]);
					}
				}
			}
		}
		else {
			for (int i = 0; i < numberOfField; i++) {
				if (i < numberOfField - 1) {
					printf("|%-21s", " ");
				}
				else {
					printf("|%-21s|\n", " ");
				}
			}
		}

		for (int i = 1; i <= 21 * numberOfField + (numberOfField + 1); i++) {
			printf("%s", "+");
		}
		cout << endl;
		cout << "Complete successfully!" << endl;
	}

	void selectAny() {
		int nSelectedColumn;
		char xSelectedColumn[50][50];
		char xFilterColumn[50];
		char xValueFilter[50];

		do {
			cout << "Enter number of selected column: ";
			cin >> nSelectedColumn;
			if (nSelectedColumn <= 0 || nSelectedColumn > numberOfField) {
				cout << "Invalid number selected column!! Please type again!!" << endl;
			}
		} while (nSelectedColumn <= 0 || nSelectedColumn > numberOfField);
		cin.ignore();

		for (int i = 0; i < nSelectedColumn; i++) {
		re_enter_select:
			if (i == 0) {
				cout << "\tEnter the 1st selected column name: ";
			}
			else {
				cout << "\tEnter the " << i + 1 << "th selected column name: ";
			}
			cin >> xSelectedColumn[i];
			if (checkKeyExist(xSelectedColumn[i]) == false) {
				cout << "Invalid column!! Please type again!!" << endl;
				goto re_enter_select;
			}
		}

	re_enter_filter:
		cout << "Enter filter column: ";
		cin >> xFilterColumn;
		if (checkKeyExist(xFilterColumn) == false) {
			cout << "Invalid column!! Please type again!!" << endl;
			goto re_enter_filter;
		}
		cin.ignore();

		cout << "Enter filter value: ";
		cin.getline(xValueFilter, sizeof(xValueFilter) / sizeof(char));

		cout << "Executing query:" << endl;
		cout << "\tSELECT ";
		for (int i = 0; i < nSelectedColumn; i++) {
			if (i < nSelectedColumn - 1) {
				cout << xSelectedColumn[i] << ", ";
			}
			else {
				cout << xSelectedColumn[i] << endl;
			}
		}
		cout << "\tFROM " << tableName << endl;
		cout << "\tWHERE " << xFilterColumn << " = '" << xValueFilter << "'" << endl;

		int index = selectedIndex(xFilterColumn, xValueFilter);

		for (int i = 1; i <= 21 * nSelectedColumn + (nSelectedColumn + 1); i++) {
			printf("%s", "+");
		}
		cout << endl;
		for (int i = 0; i < nSelectedColumn; i++) {
			if (i < nSelectedColumn - 1) {
				printf("|%-21s", xSelectedColumn[i]);
			}
			else {
				printf("|%-21s|\n", xSelectedColumn[i]);
			}
		}
		for (int i = 1; i <= 21 * nSelectedColumn + (nSelectedColumn + 1); i++) {
			printf("%s", "+");
		}
		cout << endl;
		if (index == -1) {
			for (int i = 0; i < nSelectedColumn; i++) {
				if (i < nSelectedColumn - 1) {
					printf("|%-21s", " ");
				}
				else {
					printf("|%-21s|\n", " ");
				}
			}
		}
		else {
			for (int i = 0; i < numberOfRecords; i++) {
				if (i == index) {
					printf("|");
					for (int j = 0; j < nSelectedColumn; j++) {
						for (int k = 0; k < numberOfField; k++) {
							if (strcmp(field[k].columnName, xSelectedColumn[j]) == 0) {
								printf("%-21s|", field[k].value[i]);
							}
						}
					}
					printf("\n");
				}
			}
		}

		for (int i = 1; i <= 21 * nSelectedColumn + (nSelectedColumn + 1); i++) {
			printf("%s", "+");
		}
		cout << endl;
		cout << "Complete successfully!";
	}

	int selectedIndex(char column[], char condition[]) {
		for (int i = 0; i < numberOfRecords; i++) {
			for (int j = 0; j < numberOfField; j++) {
				if (strcmp(field[j].columnName, column) == 0 && strcmp(field[j].value[i], condition) == 0) {
					return i;
				}
			}
		}
		return -1;
	}

	void deleteWithCondition() {
		char column[50], condition[50];
	re_enter:
		cout << "Enter column name: ";
		cin >> column;
		if (checkKeyExist(column) == false) {
			cout << "Invalid column!! Please type again!!" << endl;
			goto re_enter;
		}
		cin.ignore();
		cout << "Enter condition value: ";
		cin.getline(condition, sizeof(condition) / sizeof(char));
		cout << "Executing query:" << endl;
		cout << "\tDELETE" << endl;
		cout << "\tFROM " << tableName << endl;
		cout << "\tWHERE " << column << " = " << condition << endl;

		int index = selectedIndex(column, condition);

		if (index == -1) {
			cout << "No data deleted!" << endl;
		}
		else {
			for (int i = index; i < numberOfRecords; i++) {
				for (int j = 0; j < numberOfField; j++) {
					strcpy_s(field[j].value[i], sizeof(field[j].value[i]) / sizeof(char), field[j].value[i + 1]);
				}
			}
			numberOfRecords--;
		}
		cout << "Complete successfully!" << endl;
	}

	void updateRecord() {
		char column[50], value[50], condColumn[11], condValue[50];
		//input field to get record
	re_enter_cond_col:
		cout << "Enter condition column: ";
		cin >> condColumn;
		if (checkKeyExist(condColumn) == false) {
			cout << "Invalid cloumn!! Please type again!!" << endl;
			goto re_enter_cond_col;
		}
		cin.ignore();
		cout << "Enter condition value: ";
		cin.getline(condValue, sizeof(condValue) / sizeof(char));
		//input value to update record
	re_enter_update_col:
		cout << "Enter column name: ";
		cin >> column;
		if (checkKeyExist(column) == false) {
			cout << "Invalid cloumn!! Please type again!!" << endl;
			goto re_enter_update_col;
		}
		cin.ignore();
		cout << "Enter new value: ";
		cin.getline(value, sizeof(value) / sizeof(char));

		cout << "Executing query:" << endl;
		cout << "\tUPDATE" << endl;
		cout << "\tSET " << column << " = " << value << endl;
		cout << "\tWHERE " << condColumn << " = " << condValue << endl;

		int index = selectedIndex(condColumn, condValue);

		if (index == -1) {
			cout << "No data updated!" << endl;
		}
		else {
			for (int i = 0; i < numberOfRecords; i++) {
				if (i == index) {
					for (int j = 0; j < numberOfField; j++) {
						if (strcmp(field[j].columnName, column) == 0) {
							strcpy_s(field[j].value[i], sizeof(field[j].value[i]) / sizeof(char), value);
						}
					}
				}
			}
			cout << "Complete successfully!" << endl;
		}
	}

	//ALTER TABLE(ADD COLUMN)
	void addColumn(Field f) {
		if (checkKeyExist(f.columnName) == true) {
			cout << "Column has already exist in table!! Please type again!!" << endl;
		}
		else {
			field[numberOfField++] = f;
			cout << "Complete successfully!" << endl;
		}
	}
	//DROP COLUMN
	void dropColumn(char column[]) {
		if (checkKeyExist(column) == false) {
			cout << "Invalid column!!" << endl;
		}
		else {
			for (int i = numberOfField - 1; i >= 0; i--) {
				if (strcmp(field[i].columnName, column) == 0) {
					for (int j = i; j < numberOfField; j++) {
						field[j] = field[j + 1];
					}
					numberOfField--;
				}
			}
			cout << "Complete successfully!" << endl;
		}
	}
	//DELETE ALL DATA IN TABLE
	void deleteAllData() {
		cout << "Executing query:" << endl;
		cout << "\tDELETE" << endl;
		cout << "\tFROM " << tableName << endl;
		int i = 0;
		while (numberOfRecords > 0) {
			for (int j = 0; j < numberOfField; j++) {
				strcpy_s(field[j].value[i], sizeof(field[j].value[i]) / sizeof(char), field[j].value[i + 1]);
			}
			i++;
			numberOfRecords--;
		}
		cout << "Complete successfully!" << endl;
	}
};
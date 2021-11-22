#include <iostream>
#include<string.h>
#include "Database.h"
#define MAX 2
using namespace std;

int menu() {
	cout << "+------------------+ MENU +------------------------+" << endl;
	cout << "|             1. LIST DATABASES                    |" << endl;
	cout << "|             2. CREATE DATABASE                   |" << endl;
	cout << "|             3. SELECT DATABASE                   |" << endl;
	cout << "|             4. SHOW INFOMATION DATABASE          |" << endl;
	cout << "|             5. DROP DATABASE                     |" << endl;
	cout << "|             6. SELECT TABLE                      |" << endl;
	cout << "|             7. CREATE TABLE                      |" << endl;
	cout << "|             8. SHOW TABLE                        |" << endl;
	cout << "|             9. DROP TABLE                        |" << endl;
	cout << "|            10. ADD COLUMN INTO TABLE             |" << endl;
	cout << "|            11. DROP COLUMN                       |" << endl;
	cout << "|            12. INSERT DATA                       |" << endl;
	cout << "|            13. SELECT DATA                       |" << endl;
	cout << "|            14. FILTER DATA                       |" << endl;
	cout << "|            15. DELETE SOME DATA                  |" << endl;
	cout << "|            16. DELETE ALL DATA                   |" << endl;
	cout << "|            17. UPDATE DATA                       |" << endl;
	cout << "|            18. EXIT                              |" << endl;
	cout << "+--------------------------------------------------+" << endl;
	int choice;
	cout << "Enter the choice of menu: ";
	cin >> choice;
	return choice;
}

int selectedIndexDatabase(Database dbs[], int n, char dbName[]) {
	for (int i = 0; i < n; i++) {
		if (strcmp(dbs[i].dbName, dbName) == 0) {
			return i;
		}
	}
	return -1;
}

int getTableByName(Table tables[], int n, char tableName[]) {
	for (int i = 0; i < n; i++) {
		if (strcmp(tables[i].tableName, tableName) == 0) {
			return i;
		}
	}
	return -1;
}

int main()
{
	Database databases[MAX], dbUsing;
	Table tableUsing;
	int nDatabases = 0;
	int checked = 0;
	int index;
	char dbName[50];
	char tableName[50];

	while (checked == 0) {
		int choice = menu();
		switch (choice) {
		case 1:
		{
			cout << "Executing query:" << endl;
			cout << "\tSHOW DATABASES;" << endl;
			cout << "\n+---------------+" << endl;
			printf("|%-15s|\n", "DATABASES");
			cout << "+---------------+" << endl;
			for (int i = 0; i < nDatabases; i++) {
				printf("|%-15s|\n", databases[i].dbName);
			}
			cout << "+---------------+" << endl;
			cout << "Complete successfully!" << endl;
			break;
		}
		case 2:
		{
			Database db;
			db.inputDatabase();
			cout << "Executing query:" << endl;
			cout << "\tCREATE DATABASE "<<db.dbName<<";"<< endl;
			databases[nDatabases++] = db;
			cout << "Complete successfully!" << endl;
			break;
		}
		case 3:
		{
			cout << "Enter database name: ";
			cin >> dbName;
			index = selectedIndexDatabase(databases, nDatabases, dbName);
			if (index == -1) {
				cout << "Can't find " << dbName << " database!" << endl;
			}
			else {
				dbUsing = databases[index];
				cout << "Executing query:" << endl;
				cout << "\tUSE " << dbUsing.dbName << ";" << endl;
				cout << "Complete successfully!" << endl;
			}
			break;
		}
		case 4:
		{
			if (strcmp(dbUsing.dbName, "") == 0) {
				cout << "Please select database!" << endl;
			}
			else {
				cout << "Executing query:" << endl;
				cout << "\tSHOW TABLES;" << endl;
				dbUsing.showDatabase();
			}
			break;
		}
		case 5:
		{
			if (strcmp(dbUsing.dbName, "") == 0) {
				cout << "Please select database!" << endl;
			}
			else {
				cout << "Enter database name: ";
				cin >> dbName;
				index = selectedIndexDatabase(databases, nDatabases, dbName);
				if (index == -1) {
					cout << "Can't find " << dbName << " database!" << endl;
				}
				else {
					cout << "Executing query: " << endl;
					cout << "\tDROP " << databases[index].dbName << ";" << endl;
					for (int i = 0; i < nDatabases; i++) {
						for (int j = index; j < nDatabases; j++) {
							databases[j] = databases[j + 1];
						}
					}
					nDatabases--;
					cout << "Complete successfully!" << endl;
				}
			}
			break;
		}
		case 6:
		{
			if (strcmp(dbUsing.dbName, "") == 0) {
				cout << "Please select database!" << endl;
			}
			else {
				cout << "Enter table name: ";
				cin >> tableName;
				index = getTableByName(dbUsing.tables, dbUsing.numberOfTable, tableName);
				if (index == -1) {
					cout << tableName << " not exist in database!" << endl;
				}
				else {
					cout << "Executing query: " << endl;
					cout << "\tUSE " << dbUsing.tables[index].tableName << ";" << endl;
					tableUsing = dbUsing.tables[index];
					cout << "Complete successfully!" << endl;
				}
			}
			break;
		}
		case 7:
		{
			if (strcmp(dbUsing.dbName, "") == 0) {
				cout << "Please select database!" << endl;
			}
			else {
				cout << "Executing query:" << endl;
				cout << "\tUSE " << dbUsing.dbName << endl;
				cout << "\tGO" << endl;
				cout << "Complete successfully!" << endl;
				Table table;
				table.inputTable();
				cout << "Executing query:" << endl;
				cout << "\tCREATE TABLE " << table.tableName << endl;
				cout << "\t(" << endl;
				for (int i = 0; i < table.numberOfField; i++) {
					if (i < table.numberOfField - 1) {
						if (strcmp(table.field[i].columnName, table.primaryKey) == 0) {
							printf("\t\t%-15s%-15s%-10s%-15s,\n", table.field[i].columnName, table.field[i].dataType, table.field[i].isNull == 0 ? "NOT NULL" : "NULL", "PRIMARY KEY");
						}
						else {
							printf("\t\t%-15s%-15s%-10s,\n", table.field[i].columnName, table.field[i].dataType, table.field[i].isNull == 0 ? "NOT NULL" : "NULL");
						}
					}
					else {
						if (strcmp(table.field[i].columnName, table.primaryKey) == 0) {
							printf("\t\t%-15s%-15s%-10s%-15s\n", table.field[i].columnName, table.field[i].dataType, table.field[i].isNull == 0 ? "NOT NULL" : "NULL", "PRIMARY KEY");
						}
						else {
							printf("\t\t%-15s%-15s%-10s\n", table.field[i].columnName, table.field[i].dataType, table.field[i].isNull == 0 ? "NOT NULL" : "NULL");
						}
					}
				}
				cout << "\t)" << endl;
				dbUsing.addNewTable(table);
			}
			break;
		}
		case 8:
		{
			if (strcmp(dbUsing.dbName, "") == 0) {
				cout << "Please select database!" << endl;
			}
			else {
				cout << "Do you want to show all tables in database " << dbUsing.dbName << "?(Yes/No)" << endl;
				cout << ">> ";
				char answer[4];
				cin >> answer;

				if (strcmp(answer, "Yes") == 0 || strcmp(answer, "yes") == 0 || strcmp(answer, "Y") == 0 || strcmp(answer, "y") == 0) {
					cout << "Executing query: " << endl;
					cout << "\tSHOW TABLES;" << endl;
					dbUsing.showTable(true);
				}
				else {
					dbUsing.showTable(false);
				}
			}
			break;
		}
		case 9:
		{
			char table[50];
			if (strcmp(dbUsing.dbName, "") == 0) {
				cout << "Please select database!" << endl;
			}
			else {
				cout << "Enter table name: ";
				cin >> table;
				cout << "Executing query: " << endl;
				cout << "\tDROP " << table << ";" << endl;
				dbUsing.dropTable(table);
			}
			break;
		}
		case 10:
		{
			if (strcmp(dbUsing.dbName, "") == 0) {
				cout << "Please select database!" << endl;
			}
			else {
				Field f;
				f.inputField();
				cout << "Executing query: " << endl;
				cout << "\tALTER TABLE " << tableUsing.tableName << endl;
				cout << "\tADD " << f.columnName << " " << f.dataType << " " << (f.isNull == 0 ? "NOT NULL" : "NULL") << ";" << endl;
				index = getTableByName(dbUsing.tables, dbUsing.numberOfTable, tableUsing.tableName);
				dbUsing.tables[index].addColumn(f);
				tableUsing = dbUsing.tables[index];
			}
			break;
		}
		case 11:
		{
			if (strcmp(dbUsing.dbName, "") == 0) {
				cout << "Please select database!" << endl;
			}
			else {
				char column[50];
				cout << "Enter column name: ";
				cin >> column;
				cout << "Executing query: " << endl;
				cout << "\tALTER TABLE " << tableUsing.tableName << endl;
				cout << "\tDROP COLUMN " << column << ";" << endl;
				index = getTableByName(dbUsing.tables, dbUsing.numberOfTable, tableUsing.tableName);
				dbUsing.tables[index].dropColumn(column);
				tableUsing = dbUsing.tables[index];
			}
			break;
		}
		case 12:
		{
			if (strcmp(dbUsing.dbName, "") == 0) {
				cout << "Please select database!" << endl;
			}
			else {
				if (strcmp(tableUsing.tableName, "") == 0) {
					cout << "Please select table!" << endl;
				}
				else {
					int n;
					cout << "Enter number of records: ";
					cin >> n;
					cin.ignore();
					for (int i = 0; i < n; i++) {
						tableUsing.insertIntoTable();
					}
				}
			}
			break;
		}
		case 13:
		{
			if (strcmp(dbUsing.dbName, "") == 0) {
				cout << "Please select database!" << endl;
			}
			else {
				if (strcmp(tableUsing.tableName, "") == 0) {
					cout << "Please select table!" << endl;
				}
				else {
					tableUsing.selectAll();
				}
			}
			break;
		}
		case 14:
		{
			if (strcmp(dbUsing.dbName, "") == 0) {
				cout << "Please select database!" << endl;
			}
			else {
				if (strcmp(tableUsing.tableName, "") == 0) {
					cout << "Please select table!" << endl;
				}
				else {
					tableUsing.selectAny();
				}
			}
			break;
		}
		case 15:
		{
			if (strcmp(dbUsing.dbName, "") == 0) {
				cout << "Please select database!" << endl;
			}
			else {
				if (strcmp(tableUsing.tableName, "") == 0) {
					cout << "Please select table!" << endl;
				}
				else {
					tableUsing.deleteWithCondition();
				}
			}
			break;
		}
		case 16:
		{
			if (strcmp(dbUsing.dbName, "") == 0) {
				cout << "Please select database!" << endl;
			}
			else {
				if (strcmp(tableUsing.tableName, "") == 0) {
					cout << "Please select table!" << endl;
				}
				else {
					tableUsing.deleteAllData();
				}
			}
			break;
		}
		case 17:
		{
			if (strcmp(dbUsing.dbName, "") == 0) {
				cout << "Please select database!" << endl;
			}
			else {
				if (strcmp(tableUsing.tableName, "") == 0) {
					cout << "Please select table!" << endl;
				}
				else {
					tableUsing.updateRecord();
				}
			}
			break;
		}
		case 18:
			checked = -1;
			break;
		default:
			cout << "Invalid menu!" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
	return 0;
}
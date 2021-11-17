#include<iostream>
#include<string.h>
#include "Database.cpp"
using namespace std;

int main() {

	Database database;
	database.inputDatabase();

	cout << "_________________________________________________________________________________________" << endl;
	database.showDatabase();
	return 0;
}
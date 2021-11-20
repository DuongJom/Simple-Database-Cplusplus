#include <iostream>
#include<string.h>
using namespace std;

class Field{
    public:
        char columnName[20];
        char dataType[20];
        bool isNull;
        char value[10][100];

        Field(){
            strcpy(columnName,"");
            strcpy(dataType,"CHAR(10)");
            isNull=true;
        }

        void inputField(){
            cout<<"\t\tEnter column name: ";
            cin>>columnName;
            cout<<"\t\tEnter data type: ";
            cin>>dataType;
            cout<<"\t\tEnter type of null(0: NOT NULL, 1: NULL): ";
            cin>>isNull;
        }

        void showField(){
            printf("\t%-10s%-15s",columnName,dataType);
            if(isNull==true){
                printf("%-10s","NULL");
            }
            else{
                printf("%-10s","NOT NULL");
            }
        }

};

class Table{
public:
    char tableName[20];
    int numberOfField;
    //Maximum: 10 fields
    Field field[10];
    char primaryKey[20];
    int numberOfRecords;

    Table(){
        strcpy(tableName,"");
        numberOfField=0;
        numberOfRecords=0;
    }

    void inputTable(){
        cout<<"\tEnter table name: ";
        cin>>tableName;
        do{
            cout<<"\tEnter number of fields: ";
            cin>>numberOfField;
            if(numberOfField<=0||numberOfField>10){
                cout<<"Invalid number of field!"<<endl;
            }
        }while(numberOfField<=0||numberOfField>10);
        for(int i=0;i<numberOfField;i++){
            field[i].inputField();
            cout<<endl;
        }
        cout<<"\tEnter primary key: ";
        cin>>primaryKey;
    }

    void showTable(){
        cout<<tableName<<endl<<"("<<endl;
        for(int i=0;i<numberOfField;i++){
            if(i<numberOfField-1){
                if(strcmp(field[i].columnName,primaryKey)==0){
                    field[i].showField();
                    cout<<"PRIMARY KEY,"<<endl;
                }
                else{
                    field[i].showField();
                    cout<<","<<endl;
                }
            }
            else{
                if(strcmp(field[i].columnName,primaryKey)==0){
                    field[i].showField();
                    cout<<"PRIMARY KEY"<<endl;
                }
                else{
                    field[i].showField();
                    cout<<endl;
                }
            }
        }
        cout<<")"<<endl;
    }

    void insertIntoTable(){
        cout<<"Enter number of records: ";
        cin>>numberOfRecords;
        cin.ignore();
        for(int i=0;i<numberOfRecords;i++){
            for(int j=0;j<numberOfField;j++){
                cout<<"\tEnter "<<field[j].columnName<<": ";
                cin.getline(field[j].value[i],sizeof(field[j].value[i])/sizeof(char));
            }
        }
    }

    void selectAll(){
        for(int i=1;i<=21*numberOfField+(numberOfField+1);i++){
            printf("%s","+");
        }
        cout<<endl;
        for(int i=0;i<numberOfField;i++){
            if(i<numberOfField-1){
                printf("|%-21s",field[i].columnName);
            }
            else{
                printf("|%-21s|\n",field[i].columnName);
            }
        }
        for(int i=1;i<=21*numberOfField+(numberOfField+1);i++){
            printf("%s","+");
        }
        cout<<endl;
        for(int i=0;i<numberOfRecords;i++){
            for(int j=0;j<numberOfField;j++){
                if(j<numberOfField-1){
                    printf("|%-21s",field[j].value[i]);
                }
                else{
                    printf("|%-21s|\n",field[j].value[i]);
                }
            }
        }
        for(int i=1;i<=21*numberOfField+(numberOfField+1);i++){
            printf("%s","+");
        }
        cout<<endl;
    }

    int selectedIndex(char column[], char condition[]){
        for(int i=0;i<numberOfRecords;i++){
            for(int j=0;j<numberOfField;j++){
                if(strcmp(field[j].columnName,column)==0 && strcmp(field[j].value[i],condition)==0){
                        return i;
                }
            }
        }
        return -1;
    }

    void deleteWithCondition(){
        char column[50], condition[50];

        cout<<"Enter column name: ";
        cin>>column;
        cin.ignore();
        cout<<"Enter condition value: ";
        cin.getline(condition,sizeof(condition)/sizeof(char));
        cout<<"Executing query:"<<endl;
        cout<<"\tDELETE"<<endl;
        cout<<"\tFROM "<<tableName<<endl;
        cout<<"\tWHERE "<<column<<" = "<<condition<<endl;

        int index = selectedIndex(column,condition);

        if(index==-1){
            cout<<"No data deleted!"<<endl;
        }
        else{
            for(int i=index;i<numberOfRecords;i++){
                for(int j=0;j<numberOfField;j++){
                    strcpy(field[j].value[i],field[j].value[i+1]);
                }
            }
            numberOfRecords--;
            cout<<"Complete successfully!"<<endl;
        }
    }

    void updateRecord(){
        char column[50],value[50],condColumn[11],condValue[50];
        //input field to get record
        cout<<"Enter condition column: ";
        cin>>condColumn;
        cin.ignore();
        cout<<"Enter condition value: ";
        cin.getline(condValue,sizeof(condValue)/sizeof(char));
        //input value to update record
        cout<<"Enter column name: ";
        cin>>column;
        cin.ignore();
        cout<<"Enter new value: ";
        cin.getline(value,sizeof(value)/sizeof(char));

        cout<<"Executing query:"<<endl;
        cout<<"\tUPDATE"<<endl;
        cout<<"\tSET "<<column<<" = "<<value<<endl;
        cout<<"\tWHERE "<<condColumn<<" = "<<condValue<<endl;

        int index = selectedIndex(condColumn,condValue);

        if(index==-1){
            cout<<"No data updated!"<<endl;
        }
        else{
            for(int i=0;i<numberOfRecords;i++){
                if(i==index){
                    for(int j=0;j<numberOfField;j++){
                        if(strcmp(field[j].columnName,column)==0){
                            strcpy(field[j].value[i],value);
                        }
                    }
                }
            }
            cout<<"Complete successfully!"<<endl;
        }
    }

    //ALTER TABLE(ADD COLUMN)
    void alterTable(){
        Field f;
        f.inputField();
        field[numberOfField++]=f;
    }
    //DROP COLUMN
    void dropColumn(){
        char column[50];
        cout<<"Enter column name: ";
        cin>>column;
        for(int i=numberOfField-1;i>=0;i--){
            if(strcmp(field[i].columnName,column)==0){
                for(int j=i;j<numberOfField;j++){
                    field[j] = field[j+1];
                }
                numberOfField--;
            }
        }
    }
    //DELETE ALL DATA IN TABLE
    void deleteAllData(){
        int i=0;
        while(numberOfRecords>0){
            for(int j=0;j<numberOfField;j++){
                strcpy(field[j].value[i],field[j].value[i+1]);
            }
            i++;
            numberOfRecords--;
        }
        cout<<"Complete successfully!"<<endl;
    }
};

int main()
{
    Table table;
    cout<<"---------------------------------INPUT TABLE-------------------------------"<<endl;
    table.inputTable();
    cout<<"\n---------------------------------SHOW TABLE-------------------------------"<<endl;
    table.showTable();
    cout<<"\n----------------------------INSERT DATA INTO TABLE------------------------"<<endl;
    table.insertIntoTable();
    cout<<"\n----------------------------DELETE DATA IN TABLE--------------------------"<<endl;
    table.deleteWithCondition();
    cout<<"\n----------------------------SELECT DATA IN TABLE--------------------------"<<endl;
    table.selectAll();
    cout<<"\n----------------------------UPDATE DATA IN TABLE--------------------------"<<endl;
    table.updateRecord();
    cout<<"\n----------------------------SELECT DATA IN TABLE--------------------------"<<endl;
    table.selectAll();
    cout<<"\n---------------------------ALTER TABLE(ADD COLUMN)------------------------"<<endl;
    table.alterTable();
    cout<<"\n----------------------------SELECT DATA IN TABLE--------------------------"<<endl;
    table.showTable();
    cout<<"\n-------------------------------DROP COLUMN--------------------------------"<<endl;
    table.dropColumn();
    cout<<"\n----------------------------SELECT DATA IN TABLE--------------------------"<<endl;
    table.showTable();
    cout<<"\n---------------------------DELETE ALL DATA IN TABLE-----------------------"<<endl;
    table.deleteAllData();
    cout<<"\n----------------------------SELECT DATA IN TABLE--------------------------"<<endl;
    table.selectAll();
    return 0;
}

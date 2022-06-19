#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <vector>

using namespace std;

struct PersonsData {
    int id;
    string name, surname, email, phone, address;
};

void waitForKey() {
    char ch;
    cout << endl << "press any key to continue";
    ch = getch();
}

string readSubString(string row, int &startString){ // poprawic -> przekazanie struct
    string stringWithData="";
    int lengthString;

    int pos = startString;
    while (row[pos] != '|') pos++;
    lengthString = pos - startString;

    stringWithData = row.substr(startString, lengthString);
    startString = startString + lengthString + 1;

    return stringWithData;
}

vector<PersonsData> loadAddresseesFromFile() {
    fstream file;
    string row;

    PersonsData person;
    vector<PersonsData> addresees;

    file.open("adressBook.txt",ios::in | ios::out);

    if (file.good()) {

        while (!file.eof()) {

            getline(file,row);

            if (row == ""){
                return addresees;
            }

            int startString = 0;

            person.id      = atoi(readSubString(row, startString).c_str());
            person.name    = readSubString(row, startString);
            person.surname = readSubString(row, startString);
            person.phone   = readSubString(row, startString);
            person.email   = readSubString(row, startString);
            person.address = readSubString(row, startString);

            addresees.push_back(person);
        }

        file.close();
    } else {
        file.open("adressBook.txt",ios::out);
        file.close();
    }

    return addresees;
}

int readLastId(vector<PersonsData> addresees) {
    int vectorSize;
    vectorSize = addresees.size();
    return addresees[vectorSize-1].id;
}

void showMessageNoData() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
    cout << endl << "THERE IS NO SUCH DATA";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    Sleep(1000);
}

void writeColouredLine(string txt1, string txt2) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    cout << txt1;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout << txt2 << endl;
}

int mainMenu() {
    char mainMenuChoice;

    system("cls");
    writeColouredLine("1 ","Add addressee");
    writeColouredLine("2 ","Search by name");
    writeColouredLine("3 ","Search by surname");
    writeColouredLine("4 ","Show all addresees");
    writeColouredLine("5 ","Delete addressee");
    writeColouredLine("6 ","Edit addressee");
    writeColouredLine("9 ","Exit program");

    mainMenuChoice = getch();
    return mainMenuChoice - 48;
}

void showAddresees(vector<PersonsData> addresees, int idStart, int idEnd) {
    if (addresees.size() == 0) {
        showMessageNoData();
    } else {
        string row;
        for (int i = idStart; i <= idEnd; i++) {
            cout << endl;

            row = to_string(addresees[i].id);
            writeColouredLine("Id:      ",row);
            writeColouredLine("Name:    ",addresees[i].name);
            writeColouredLine("Surname: ",addresees[i].surname);
            writeColouredLine("Phone:   ",addresees[i].phone);
            writeColouredLine("Email:   ",addresees[i].email);
            writeColouredLine("Address: ",addresees[i].address);
        }
    }
}

string readLine(string data) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    cout << data;
    cin.sync();
    string line;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    getline(cin,line);
    return line;
}

vector<PersonsData> addAddressee(vector<PersonsData> addresees) {
    PersonsData person;
    fstream file;
    file.open("adressBook.txt",ios::app);

    system("cls");

    if (addresees.size()>0) {
        person.id = addresees[addresees.size()-1].id + 1;
    } else {
        person.id = 1;
    }

    if (person.id != 1) file << endl;

    person.name = readLine("write name:    ");
    person.surname = readLine("write surname: ");
    person.phone = readLine("write phone:   ");
    person.email = readLine("write email:   ");
    person.address = readLine("write address: ");

    file << person.id << '|';
    file << person.name << '|';
    file << person.surname << '|';
    file << person.phone << '|';
    file << person.email << '|';
    file << person.address << '|';

    addresees.push_back(person);
    file.close();

    return addresees;
}

void writePersonsData() {
    cout << endl;
    cout << "Name:     " << endl;
    cout << "Surname:  " << endl;
    cout << "Phone nr: " << endl;
    cout << "Email:    " << endl;
    cout << "Address:  " << endl;
    cout << endl;
}

void searchByName(vector<PersonsData> addresees) {
    if (addresees.size() == 0) {
        showMessageNoData();
    } else {
        string name;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
        cout << endl << "Name please: ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        cin >> name;
        bool thisNameAppears = false;

        for (int i=0; i<addresees.size(); i++) {

            if (addresees[i].name == name) {
                showAddresees(addresees,i,i);
                thisNameAppears = true;
            }
        }

        if (thisNameAppears == false) {
            showMessageNoData();
        }
    }
}

void searchBySurname(vector<PersonsData> addresees) {
    if (addresees.size() == 0) {
        showMessageNoData();
    } else {
        string surname;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
        cout << endl << "Surname please: ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        cin >> surname;
        bool thisSurnameAppears = false;

        for (int i=0; i<addresees.size(); i++) {
            if (addresees[i].surname == surname) {
                showAddresees(addresees,i,i);
                thisSurnameAppears = true;
            }
        }

        if (thisSurnameAppears == false) {
            showMessageNoData();
        }
    }
}

void writeAddreseesToFile(vector<PersonsData> addresees) {

    fstream file;
    file.open("adressBook.txt",ios::out);

    for(int i=0; i<addresees.size(); i++) {
        file << addresees[i].id << '|';
        file << addresees[i].name << '|';
        file << addresees[i].surname << '|';
        file << addresees[i].phone << '|';
        file << addresees[i].email << '|';
        file << addresees[i].address << '|';
        if ( i+1 < addresees.size() ) file << endl;
    }

    file.close();
}

vector<PersonsData> deleteAddresee(vector<PersonsData> addresees) {
    int id;
    system("cls");
    char choose_y_n;

    if (addresees.size() == 0) {
        showMessageNoData();
        return addresees;
    }

    id = atoi(readLine("write id of a person you want to delete: ").c_str());

    writeColouredLine("Do you really want to delete this person date? ","y/n");

    do {
        choose_y_n = getch();
    } while ( (choose_y_n != 'y') && (choose_y_n != 'n') );

    if (choose_y_n == 'y') {
        bool personDeleted = false;
        for (int i=0; i < addresees.size(); i++) {
            if (addresees[i].id == id) {

                auto it = addresees.begin() + i;
                addresees.erase(it);

                writeAddreseesToFile(addresees);
                cout << "Addresee deleted" << endl;
                personDeleted = true;
                break;
            }
        }

        if ( !personDeleted ) cout << "Id is not exist - addresee did't deleted" << endl;
    }
    return addresees;
}

vector<PersonsData> editAddresee(vector<PersonsData> addresees) {
    int id;
    char menuChoice;
    int pos = 0;
    string data;
    bool thisIdExist = false;

    system("cls");
    id = atoi(readLine("write id of a person you want to edit: ").c_str());

    for (int i=0; i<addresees.size(); i++){
        if (addresees[i].id == id) {
            thisIdExist = true;
            pos = i;
        }
    }

    if ( !thisIdExist ) {
        cout << "This id is not in base";
        waitForKey;
        return addresees;
    }

    showAddresees(addresees, pos, pos);

    cout << endl << "Choose which date you want to change:" << endl << endl;
    writeColouredLine("1 ","Name");
    writeColouredLine("2 ","Surname");
    writeColouredLine("3 ","Phone");
    writeColouredLine("4 ","Email");
    writeColouredLine("5 ","Address");
    writeColouredLine("6 ","Back to main menu");

    do {
        menuChoice = getch() - 48;
    } while( menuChoice<1 || menuChoice>6 );

    switch (menuChoice)
    {
        case 1:
            data = readLine("Name : ");
            addresees[pos].name = data;
        break;
        case 2:
            data = readLine("Surname : ");
            addresees[pos].surname = data;
        break;
        case 3:
            data = readLine("Phone : ");
            addresees[pos].phone = data;
        break;
        case 4:
            data = readLine("Email : ");
            addresees[pos].email = data;
        break;
        case 5:
            data = readLine("Address : ");
            addresees[pos].address = data;
        break;
    }

    if (menuChoice != 6) writeAddreseesToFile(addresees);
    return addresees;
}

//--------------------------------------------------------------
int main() {
    int mainMenuChoice;
    vector<PersonsData> addresees;

    addresees = loadAddresseesFromFile();

    do {
        mainMenuChoice = mainMenu();

        switch (mainMenuChoice) {
        case 1:
            addresees = addAddressee(addresees);
            break;

        case 2:
            searchByName(addresees);
            break;

        case 3:
            searchBySurname(addresees);
            break;

        case 4:
            showAddresees(addresees,0,addresees.size()-1);
            break;

        case 5:
            addresees = deleteAddresee(addresees);
            break;

        case 6:
            addresees = editAddresee(addresees);
            break;
        }

        if (mainMenuChoice == 9) {
            cout << endl;
            writeColouredLine("ARRIVEDERCI"," :)");
            break;
        }

        waitForKey();

    } while (mainMenuChoice != 9);

    return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <cstdlib>
#define CLEAR_COMMAND "cls"  // Windows clear screen command
#else
#include <unistd.h>
#define CLEAR_COMMAND "clear"  // Unix-based systems clear screen command
#endif

using namespace std;

// University class holds basic student data
class University {
private:
    string RollNo, Name, Subject, Address;

public:
    // Constructor
    University() : RollNo(""), Name(""), Subject(""), Address("") {}

    // Setter methods
    void setRollNo(string rollNo) { RollNo = rollNo; }
    void setName(string name) { Name = name; }
    void setSubject(string subject) { Subject = subject; }
    void setAddress(string address) { Address = address; }

    // Getter methods
    string getRollNo() { return RollNo; }
    string getName() { return Name; }
    string getSubject() { return Subject; }
    string getAddress() { return Address; }
};

// Function to add a new student and save data to file
void add(University& student) {
    string rollNo, name, subject, address;

    cout << "\tEnter RollNo Of Student: ";
    cin >> rollNo;
    student.setRollNo(rollNo);

    cout << "\tEnter Name Of Student: ";
    cin >> name;
    student.setName(name);

    cout << "\tEnter Subject Of Student: ";
    cin >> subject;
    student.setSubject(subject);

    cout << "\tEnter Address Of Student: ";
    cin >> address;
    student.setAddress(address);

    ofstream out("university.txt", ios::app);  // Append mode
    if (!out) {
        cout << "\tError: File Can't Open!" << endl;
        return;
    }

    // Writing student data to file
    out << "\t" << student.getRollNo() << " : " << student.getName() << " : " << student.getSubject()
        << " : " << student.getAddress() << endl << endl;

    out.close();
    cout << "\tStudent Added Successfully!" << endl;
}

// Function to search for a student by RollNo
void search() {
    string rollNo;
    cout << "\tEnter RollNo Of Student: ";
    cin >> rollNo;

    ifstream in("university.txt");
    if (!in) {
        cout << "\tError: File Can't Open!" << endl;
        return;
    }

    string line;
    bool found = false;
    // Read each line and search for roll number
    while (getline(in, line)) {
        if (line.find(rollNo) != string::npos) {
            cout << "\t" << line << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "\tStudent Not Found!" << endl;
    }

    in.close();
}

// Function to update a student's address based on RollNo
void update(University& student) {
    string rollNo;
    cout << "\tEnter RollNo Of Student: ";
    cin >> rollNo;

    ifstream infile("university.txt");
    ofstream outfile("university_temp.txt");

    if (!infile || !outfile) {
        cout << "\tError: File Can't Open!" << endl;
        return;
    }

    string line;
    bool found = false;
    // Check each line for the roll number and update address
    while (getline(infile, line)) {
        if (line.find(rollNo) != string::npos) {
            string address;
            cout << "\tEnter New Address: ";
            cin >> address;
            student.setAddress(address);

            int newPos = line.find_last_of(':');
            // Replace existing address with new address
            line.replace(newPos + 2, string::npos, student.getAddress());
            found = true;
        }
        outfile << line << endl;
    }

    infile.close();
    outfile.close();

    // Replace original file with updated file
    if (found) {
        remove("university.txt");
        rename("university_temp.txt", "university.txt");
        cout << "\tData Updated!" << endl;
    } else {
        cout << "\tStudent Not Found!" << endl;
        remove("university_temp.txt");
    }
}

// Cross-platform delay function
void wait(int milliseconds) {
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

// Cross-platform screen clear function
void clearScreen() {
    system(CLEAR_COMMAND);
}

// Main menu
int main() {
    University student;
    bool exitProgram = false;

    while (!exitProgram) {
        clearScreen();

        int choice;
        cout << "\tWelcome To University Management System" << endl;
        cout << "\t***************************************" << endl;
        cout << "\t1. Add Student." << endl;
        cout << "\t2. Search Student." << endl;
        cout << "\t3. Update Data Of Student." << endl;
        cout << "\t4. Exit." << endl;
        cout << "\tEnter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                clearScreen();
                add(student);
                wait(3000);
                break;
            case 2:
                clearScreen();
                search();
                wait(3000);
                break;
            case 3:
                clearScreen();
                update(student);
                wait(3000);
                break;
            case 4:
                exitProgram = true;
                clearScreen();
                cout << "\tGood Luck!" << endl;
                wait(2000);
                break;
            default:
                cout << "\tInvalid Choice!" << endl;
                wait(1500);
        }
    }

    return 0;
}

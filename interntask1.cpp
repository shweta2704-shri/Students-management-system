#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

struct Student {
    int rollNo;
    string name;
    float marks;
};

void addStudent() {
    Student s;
    ofstream file("students.txt", ios::app);
    
    cout << "Enter Roll Number: ";
    cin >> s.rollNo;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, s.name);
    cout << "Enter Marks: ";
    cin >> s.marks;
    
    file << s.rollNo << " " << s.name << " " << s.marks << endl;
    file.close();
    cout << "Student record added successfully!\n";
}

void displayStudents() {
    ifstream file("students.txt");
    Student s;
    
    cout << "\nStudent Records:\n";
    cout << left << setw(10) << "Roll No" << setw(20) << "Name" << "Marks" << endl;
    cout << "-------------------------------------------------\n";
    
    while (file >> s.rollNo >> ws && getline(file, s.name, ' ') && file >> s.marks) {
        cout << left << setw(10) << s.rollNo << setw(20) << s.name << s.marks << endl;
    }
    
    file.close();
}

void searchStudent(int rollNo) {
    ifstream file("students.txt");
    Student s;
    bool found = false;
    
    while (file >> s.rollNo >> ws && getline(file, s.name, ' ') && file >> s.marks) {
        if (s.rollNo == rollNo) {
            cout << "\nStudent Found:\n";
            cout << "Roll No: " << s.rollNo << "\nName: " << s.name << "\nMarks: " << s.marks << endl;
            found = true;
            break;
        }
    }
    
    file.close();
    if (!found) cout << "Student with Roll No " << rollNo << " not found!\n";
}

void deleteStudent(int rollNo) {
    ifstream file("students.txt");
    ofstream temp("temp.txt");
    Student s;
    bool deleted = false;
    
    while (file >> s.rollNo >> ws && getline(file, s.name, ' ') && file >> s.marks) {
        if (s.rollNo == rollNo) {
            deleted = true;
        } else {
            temp << s.rollNo << " " << s.name << " " << s.marks << endl;
        }
    }
    
    file.close();
    temp.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
    
    if (deleted) cout << "Student record deleted successfully!\n";
    else cout << "Student with Roll No " << rollNo << " not found!\n";
}

int main() {
    int choice, rollNo;
    
    do {
        cout << "\nStudent Management System\n";
        cout << "1. Add Student\n2. Display Students\n3. Search Student\n4. Delete Student\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                cout << "Enter Roll Number to search: ";
                cin >> rollNo;
                searchStudent(rollNo);
                break;
            case 4:
                cout << "Enter Roll Number to delete: ";
                cin >> rollNo;
                deleteStudent(rollNo);
                break;
            case 5:
                cout << "Exiting...";
                break;
            default:
                cout << "Invalid choice! Try again.";
        }
    } while (choice != 5);
    
    return 0;
}


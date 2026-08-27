#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Part 1: Scalar Data (Single Student, Multiple Subjects)
// Goal: Learn how to handle individual data points using basic variables.
// Write a C++ program that processes the marks of a single student for three subjects (Math, Science, and English) using scalar variables.
// ●	Requirements:
// ○	Prompt the user to enter the student's name.
// ○	Prompt the user to enter marks for the three individual subjects.
// ○	Calculate the Total Marks and the Average Mark.
// ○	Display the student's name, individual marks, total, and average.

int main() {
    string name;
    double math, science, english;
    double total, average;

    cout << "Enter student name: ";
    getline(cin, name);

    cout << "Enter Math mark: ";
    cin >> math;

    cout << "Enter Science mark: ";
    cin >> science;

    cout << "Enter English mark: ";
    cin >> english;

    total = math + science + english;
    average = total / 3;

    cout << "\n===== Student Report =====" << endl;
    cout << "Name     : " << name << endl;
    cout << "Math     : " << math << endl;
    cout << "Science  : " << science << endl;
    cout << "English  : " << english << endl;
    cout << "Total    : " << total << endl;
    cout << "Average  : " << fixed << setprecision(2) << average << endl;

    return 0;
}

// Part 2: Array Data (Multiple Students, Multiple Subjects)
// Goal: Scale the solution to handle multiple students using 1D and 2D arrays.
// Modify the program to handle three students, each taking three subjects. Use a 1D array for names and a 2D array for marks.
// ●	Requirements:
// ○	Use std::string names[3] to store names.
// ○	Use a 2D array double marks[3][3] where rows represent students and columns represent subjects.
// ○	Use nested loops to input data and to calculate/display the total and average for each student.

/*
int main() {
    const int STUDENTS = 3;
    const int SUBJECTS = 3;

    string names[STUDENTS];
    double marks[STUDENTS][SUBJECTS];
    string subjects[SUBJECTS] = {"Math", "Science", "English"};

    for (int i = 0; i < STUDENTS; i++) {
        cout << "\nEnter name of student " << i + 1 << ": ";
        cin >> names[i];

        for (int j = 0; j < SUBJECTS; j++) {
            cout << "Enter " << subjects[j] << " mark: ";
            cin >> marks[i][j];
        }
    }

    cout << "\n========== Student Reports ==========\n";

    for (int i = 0; i < STUDENTS; i++) {
        double total = 0;

        cout << "\nStudent: " << names[i] << endl;

        for (int j = 0; j < SUBJECTS; j++) {
            cout << subjects[j] << ": " << marks[i][j] << endl;
            total += marks[i][j];
        }

        double average = total / SUBJECTS;

        cout << "Total   : " << total << endl;
        cout << "Average : " << fixed << setprecision(2) << average << endl;
    }

    return 0;
}*/

// Part 3: Class with Array of Marks (Single Student, Multiple Subjects)
// Goal: Introduce encapsulation by binding a student's data and behavior together using a Class.
// Create a Student class that manages one student's details and an array of marks.
// ●	Requirements:
// ○	Attributes (Private): std::string name, double marks[3].
// ○	Methods (Public): * inputData() to read the name and 3 marks.
// ■	calculateTotal() and calculateAverage() to compute metrics.
// ■	displayReport() to print the final scorecard.

/*
class Student {
private:
    string name;
    double marks[3];

public:
    void inputData() {
        cout << "Enter student name: ";
        cin >> name;

        cout << "Enter Math mark: ";
        cin >> marks[0];

        cout << "Enter Science mark: ";
        cin >> marks[1];

        cout << "Enter English mark: ";
        cin >> marks[2];
    }

    double calculateTotal() {
        return marks[0] + marks[1] + marks[2];
    }

    double calculateAverage() {
        return calculateTotal() / 3;
    }

    void displayReport() {
        cout << "\n===== Student Report =====" << endl;
        cout << "Name     : " << name << endl;
        cout << "Math     : " << marks[0] << endl;
        cout << "Science  : " << marks[1] << endl;
        cout << "English  : " << marks[2] << endl;
        cout << "Total    : " << calculateTotal() << endl;
        cout << "Average  : " << fixed << setprecision(2)
             << calculateAverage() << endl;
    }
};

int main() {
    Student student;

    student.inputData();
    student.displayReport();

    return 0;
}*/

// Part 4: Class with Array of Objects (Multiple Students, Multiple Subjects)
// Goal: Combine OOP and arrays to build a complete, scalable database structure.
// Using the Student class defined in Part 3, write a program that creates an array of Student objects to manage a whole classroom.
// ●	Requirements:
// ○	Instantiate an array of Student objects (e.g., Student classroom[3]).
// ○	Loop through the array to call inputData() for each student.
// ○	Loop through the array to call displayReport() to print the final classroom roster.

/*
class Student {
private:
    string name;
    double marks[3];

public:
    void inputData() {
        cout << "\nEnter student name: ";
        cin >> name;

        cout << "Enter Math mark: ";
        cin >> marks[0];

        cout << "Enter Science mark: ";
        cin >> marks[1];

        cout << "Enter English mark: ";
        cin >> marks[2];
    }

    double calculateTotal() {
        return marks[0] + marks[1] + marks[2];
    }

    double calculateAverage() {
        return calculateTotal() / 3;
    }

    void displayReport() {
        cout << "\n===== Student Report =====" << endl;
        cout << "Name     : " << name << endl;
        cout << "Math     : " << marks[0] << endl;
        cout << "Science  : " << marks[1] << endl;
        cout << "English  : " << marks[2] << endl;
        cout << "Total    : " << calculateTotal() << endl;
        cout << "Average  : " << fixed << setprecision(2)
             << calculateAverage() << endl;
    }
};

int main() {
    const int SIZE = 3;

    Student classroom[SIZE];

    cout << "===== Enter Student Information =====\n";

    for (int i = 0; i < SIZE; i++) {
        cout << "\nStudent " << i + 1 << endl;
        classroom[i].inputData();
    }

    cout << "\n\n===== Classroom Report =====\n";

    for (int i = 0; i < SIZE; i++) {
        classroom[i].displayReport();
    }

    return 0;
}*/

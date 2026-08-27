#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

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
}
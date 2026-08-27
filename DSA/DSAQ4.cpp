#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    double marks[3];

    double calculateTotal() {
        return marks[0] + marks[1] + marks[2];
    }

    double calculateAverage() {
        return calculateTotal() / 3;
    }

    string buildReport() {
        ostringstream report;
        report << "\n===== Student Report =====\n";
        report << "Name     : " << name << "\n";
        report << "Math     : " << marks[0] << "\n";
        report << "Science  : " << marks[1] << "\n";
        report << "English  : " << marks[2] << "\n";
        report << "Total    : " << calculateTotal() << "\n";
        report << fixed << setprecision(2);
        report << "Average  : " << calculateAverage() << "\n";
        return report.str();
    }

public:
    bool inputData() {
        cout << "\nEnter student name: ";
        if (!(cin >> name)) {
            return false;
        }

        cout << "Enter Math mark: ";
        if (!(cin >> marks[0])) {
            return false;
        }

        cout << "Enter Science mark: ";
        if (!(cin >> marks[1])) {
            return false;
        }

        cout << "Enter English mark: ";
        if (!(cin >> marks[2])) {
            return false;
        }

        return true;
    }

    string displayReport() {
        return buildReport();
    }
};

int main() {
    const int SIZE = 3;

    Student classroom[SIZE];

    cout << "===== Enter Student Information =====\n";

    for (int i = 0; i < SIZE; i++) {
        cout << "\nStudent " << i + 1 << endl;
        if (!classroom[i].inputData()) {
            cout << "Invalid input. Please enter valid marks." << endl;
            return 1;
        }
    }

    cout << "\n\n===== Classroom Report =====\n";

    for (int i = 0; i < SIZE; i++) {
        cout << classroom[i].displayReport();
    }

    return 0;
}

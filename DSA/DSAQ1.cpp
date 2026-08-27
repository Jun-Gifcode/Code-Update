#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

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
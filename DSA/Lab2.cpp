#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int scores[5];
    int *ptr = scores;

    cout << "Enter scores for 5 students:\n";
    for (int i = 0; i < 5; i++) {
        cout << "Enter score for Student" << i + 1 << ": ";
        cin >> *(ptr + i);
    }

    cout << "\nStudent scores:\n";
    for (int i = 0; i < 5; i++) {
        cout << "Student" << i + 1 << ": " << *(ptr + i) << endl;
    }

    int total = 0;
    int highest = *(ptr + 0);
    int lowest = *(ptr + 0);

    for (int i = 0; i < 5; i++) {

        total += *(ptr + i);
        
        if (*(ptr + i) > highest) {
            highest = *(ptr + i);
        }
        
        if (*(ptr + i) < lowest) {
            lowest = *(ptr + i);
        }
    }

    double average = static_cast<double>(total) / 5;

    cout << fixed << setprecision(2);
    cout << "\nTotal score: " << total << endl;
    cout << "Average score: " << average << endl;
    cout << "Highest score: " << highest << endl;
    cout << "Lowest score: " << lowest << endl;

    return 0;
}

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Function to convert mark to grade and point value
char markToGrade(int mark) {
    if (mark >= 95) return 'A+';
    else if (mark >= 90) return 'A';
    else if (mark >= 85) return 'A-';
    else if (mark >= 80) return 'B+';
    else if (mark >= 75) return 'B';
    else if (mark >= 70) return 'C+';
    else if (mark >= 65) return 'C';
    else if (mark >= 60) return 'D';
    else return 'F';
}

// Function to convert mark to grade point (4.0 scale)
double markToGradePoint(int mark) {
    if (mark >= 95) return 4.0;      // A+
    else if (mark >= 90) return 4.0; // A
    else if (mark >= 85) return 3.9; // A-
    else if (mark >= 80) return 3.5; // B+
    else if (mark >= 75) return 3.0; // B
    else if (mark >= 70) return 2.5; // C+
    else if (mark >= 65) return 2.0; // C
    else if (mark >= 60) return 1.0; // D
    else return 0.0;                 // F
}

struct Subject {
    string name;
    int mark;
    int creditHour;
    char grade;
    double gradePoint;
};

int main(){
    string studentName, programme;
    int age, numSubjects;
    
    // Input student information
    cout << "\n========== STUDENT GPA CALCULATOR ==========" << endl;
    cout << "\nEnter your name: ";
    getline(cin, studentName);
    cout << "Name recorded: " << studentName << endl;
    
    cout << "\nEnter your age: ";
    cin >> age;
    cout << "Age recorded: " << age << endl;
    
    cout << "\nEnter your programme: ";
    cin.ignore(); // Clear the newline from previous cin
    getline(cin, programme);
    cout << " Programme recorded: " << programme << endl;
    
    cout << "\nEnter number of subjects for last semester: ";
    cin >> numSubjects;
    cout << " Number of subjects: " << numSubjects << endl;
    
    // Create array to store subject information
    Subject subjects[numSubjects];
    
    double totalWeightedPoints = 0.0;
    int totalCreditHours = 0;
    
    // Input subject information
    cout << "\n========== ENTER SUBJECT DETAILS ==========" << endl;
    
    for (int i = 0; i < numSubjects; i++) {
        cout << "\n--- Subject " << (i + 1) << " ---" << endl;
        
        // Input subject name
        cout << "Enter subject name: ";
        cin.ignore();
        getline(cin, subjects[i].name);
        cout << " Subject: " << subjects[i].name << endl;
        
        // Input mark
        cout << "Enter mark for " << subjects[i].name << " (0-100): ";
        cin >> subjects[i].mark;
        subjects[i].grade = markToGrade(subjects[i].mark);
        subjects[i].gradePoint = markToGradePoint(subjects[i].mark);
        cout << " Mark: " << subjects[i].mark << " | Grade: " << subjects[i].grade 
             << " | Grade Point: " << fixed << setprecision(2) << subjects[i].gradePoint << endl;
        
        // Input credit hour
        cout << "Enter credit hour for " << subjects[i].name << ": ";
        cin >> subjects[i].creditHour;
        cout << " Credit Hour: " << subjects[i].creditHour << endl;
        
        // Calculate weighted points
        double weightedPoints = subjects[i].gradePoint * subjects[i].creditHour;
        totalWeightedPoints += weightedPoints;
        totalCreditHours += subjects[i].creditHour;
        
        cout << " Weighted Points: " << subjects[i].gradePoint << " × " 
             << subjects[i].creditHour << " = " << fixed << setprecision(2) 
             << weightedPoints << endl;
    }
    
    // Calculate final GPA
    double finalGPA = totalWeightedPoints / totalCreditHours;
    
    // Display final summary
    cout << "\n========== SEMESTER GPA SUMMARY ==========" << endl;
    cout << "\nStudent Information:" << endl;
    cout << "  Name: " << studentName << endl;
    cout << "  Age: " << age << endl;
    cout << "  Programme: " << programme << endl;
    
    cout << "\nSubject Breakdown:" << endl;
    cout << setw(20) << "Subject" << setw(10) << "Mark" << setw(8) << "Grade" 
         << setw(12) << "Grade Pt" << setw(12) << "Credit Hr" << setw(15) << "Weighted Pt" << endl;
    cout << "--------------------------------------------------------------------------------------------" << endl;
    
    for (int i = 0; i < numSubjects; i++) {
        double weightedPoints = subjects[i].gradePoint * subjects[i].creditHour;
        cout << setw(20) << subjects[i].name 
             << setw(10) << subjects[i].mark 
             << setw(8) << subjects[i].grade 
             << setw(12) << fixed << setprecision(2) << subjects[i].gradePoint 
             << setw(12) << subjects[i].creditHour 
             << setw(15) << weightedPoints << endl;
    }
    
    cout << "--------------------------------------------------------------------------------------------" << endl;
    cout << "\nCalculation:" << endl;
    cout << "Total Weighted Points = ";
    for (int i = 0; i < numSubjects; i++) {
        double weightedPoints = subjects[i].gradePoint * subjects[i].creditHour;
        cout << subjects[i].gradePoint << "x" << subjects[i].creditHour;
        if (i < numSubjects - 1) cout << " + ";
    }
    cout << " = " << fixed << setprecision(2) << totalWeightedPoints << endl;
    
    cout << "Total Credit Hours = " << totalCreditHours << endl;
    cout << "\nFinal GPA = Total Weighted Points ÷ Total Credit Hours" << endl;
    cout << "Final GPA = " << totalWeightedPoints << " ÷ " << totalCreditHours 
         << " = " << fixed << setprecision(2) << finalGPA << endl;
    
    cout << "\n========== FINAL RESULT ==========" << endl;
    cout << "Your Semester GPA: " << fixed << setprecision(2) << finalGPA << endl;
    cout << "===================================" << endl;
    
    return 0;
}

#include <string>//Include necessary libraries
#include <limits>//For input validation
#include <iostream>//For input/output
#include <array>//For fixed-size array
#include <vector>//For dynamic array (if needed)
#include <fstream>//For file handling
#include <sstream>//For string stream operations
#include <ctime>//For date and time
#include <iomanip>//For formatting output
#include <cstdlib>//For system commands

const int MAX_EMPLOYEES{200};//Maximum Employees 200

using namespace std;

class Employee {//Employee Class
private:
    string employeeID;
    string employeeName;
    int employeeAge;
    string Department;
    string Position;
    double employeeSalary;
    string employeeEmail;
    string employeePhone;
    bool employeeStatus; //Active or Inactive

    public:
    Employee() {//Default Constructor
        employeeID = "-";
        employeeName = "-";
        employeeAge = 0;
        Department = "-";
        Position = "-";
        employeeSalary = 0.0;
        employeeEmail = "-";
        employeePhone = "-";
        employeeStatus = false;//Inactive by default
    }

    //Update Employee Information [setters]
    void updateEmployeeID(string id) { employeeID = id; }
    void updateEmployeeName(string name) { employeeName = name; }
    void updateEmployeeAge(int age) { employeeAge = age; }
    void updateDepartment(string department) { Department = department; }
    void updatePosition(string position) { Position = position; }
    void updateEmployeeSalary(double salary) { employeeSalary = salary; }
    void updateEmployeeEmail(string email) { employeeEmail = email; }
    void updateEmployeePhone(string phone) { employeePhone = phone; }
    void updateEmployeeStatus(bool status) { employeeStatus = status; }

    //get Employee Information [getters]
    string getEmployeeID() { return employeeID; }
    string getEmployeeName() { return employeeName; }
    int getEmployeeAge() { return employeeAge; }
    string getDepartment() { return Department; }
    string getPosition() { return Position; }
    double getEmployeeSalary() { return employeeSalary; }
    string getEmployeeEmail() { return employeeEmail; }
    string getEmployeePhone() { return employeePhone; }
    bool getEmployeeStatus() { return employeeStatus; }
};

class EMS {//Employee Management System
private:
    array<Employee, MAX_EMPLOYEES> employees;//Array to store employees
    int employeeCount{0};

    public:
    array<Employee, MAX_EMPLOYEES> &getEmployees() { return employees; }//Getter for employees array

    string getYearMonth() {//Generate Year and Month for Employee ID
    time_t t = time(nullptr);
    tm* now = localtime(&t);

    int year = now->tm_year + 1900;
    int month = now->tm_mon + 1;

    stringstream ss;
    ss << year << std::setw(2) << std::setfill('0') << month;

    return ss.str();
    }

    string generateID(int choice, int employeeCount) {//Generate Employee ID
    stringstream id;

    id << "EMP-"
       << getYearMonth()
       << "-"
       << std::setw(2) << setfill('0') << choice
       << std::setw(4) << setfill('0') << employeeCount;

    return id.str();//Example: EMP-202409-010001 (Department 1, Employee 1)
    }

    string departmentName(int choice){//Get Department Name based on user choice
        switch (choice) {
            case 1: return "Management";
            case 2: return "Administration";
            case 3: return "Finance";
            case 4: return "Technical";
            case 5: return "Marketing";
            case 6: return "Operations";
            case 7: return "Support";
            default: return "Unknown";
        }
    }
    
    void mainmenu() {
        int choice;
        do {
            cout << "\nEmployee Management System" << endl;
            cout << "1. Add Employee" << endl;
            cout << "2. View Employees" << endl;
            cout << "3. Update Employee" << endl;
            cout << "4. Delete Employee" << endl;
            cout << "5. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    addEmployee();
                    break;
                case 2:
                    viewEmployees();
                    break;
                case 3:
                    updateEmployee();
                    break;
                case 4:
                    deleteEmployee();
                    break;
                case 5:
                    cout << "Exiting..." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 5);
    }

    void loadEmployee() {//Load specific employee details from file
    ifstream inFile("employees.txt");
        if (!inFile) {
            cout << "No saved file found. Starting fresh." << endl;
            return;
        }

        string searchKEY;
        cout << "\nEnter Employee ID or Name to search: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, searchKEY);

        bool found = false;
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string id, name, ageStr, dept, pos, salaryStr, email, phone, statusStr;

            getline(ss, id, '|');
            getline(ss, name, '|');
            getline(ss, ageStr, '|');
            getline(ss, dept, '|');
            getline(ss, pos, '|');
            getline(ss, salaryStr, '|');
            getline(ss, email, '|');
            getline(ss, phone, '|');
            getline(ss, statusStr);

            if (id == searchKEY || name == searchKEY) {
                found = true;
                cout << "\nEmployee found:" << endl;
                cout << "ID: " << id << endl;
                cout << "Name: " << name << endl;
                cout << "Age: " << ageStr << endl;
                cout << "Department: " << dept << endl;
                cout << "Position: " << pos << endl;
                cout << "Salary: $" << salaryStr << endl;
                cout << "Email: " << email << endl;
                cout << "Phone: " << phone << endl;
                cout << "Status: " << (statusStr == "1" ? "Active" : "Inactive") << endl;
                break;
            }
        }

        if (!found) {
            cout << "\nEmployee not found." << endl;
        }
    }

    void saveFile() {//Save employees to file
        ofstream outFile("employees.txt", ios::trunc);
        if (!outFile) {
            cout << "\nError opening file for writing." << endl;
            return;
        }

        for (int i = 0; i < employeeCount; i++) {
            Employee e = employees[i];
            outFile << e.getEmployeeID() << "|"
                    << e.getEmployeeName() << "|"
                    << e.getEmployeeAge() << "|"
                    << e.getDepartment() << "|"
                    << e.getPosition() << "|"
                    << e.getEmployeeSalary() << "|"
                    << e.getEmployeeEmail() << "|"
                    << e.getEmployeePhone() << "|"
                    << e.getEmployeeStatus() << endl;
        }
        outFile.close();
        cout << "\nEmployees saved to file successfully." << endl;
    }

    void loadFile() {//Load employees from file
        ifstream inFile("employees.txt");
        if (!inFile) {
            cout << "No saved file found. Starting fresh." << endl;
            return;
        }

        employeeCount = 0;
        string line;

        while (getline(inFile, line) && employeeCount < MAX_EMPLOYEES) {
            stringstream ss(line);
            string id, name, dept, pos, email, phone;
            int age;
            double salary;
            bool status;

            getline(ss, id, '|');
            getline(ss, name, '|');
            ss >> age; ss.ignore();
            getline(ss, dept, '|');
            getline(ss, pos, '|');
            ss >> salary; ss.ignore();
            getline(ss, email, '|');
            getline(ss, phone, '|');
            ss >> status;

            Employee e;
            e.updateEmployeeID(id);
            e.updateEmployeeName(name);
            e.updateEmployeeAge(age);
            e.updateDepartment(dept);
            e.updatePosition(pos);
            e.updateEmployeeSalary(salary);
            e.updateEmployeeEmail(email);
            e.updateEmployeePhone(phone);
            e.updateEmployeeStatus(status);

            employees[employeeCount++] = e;//Add employee to array and increment count
        }
        inFile.close();
        cout << "\nEmployees loaded from file successfully." << endl;
    }

    void addEmployee() {
        if (employeeCount >= MAX_EMPLOYEES) {
            cout << "\nEmployee limit reached. Cannot add more employees." << endl;
            return;
        }

        Employee newEmployee;
        string id, name, department, position, email, phone;
        int age;
        double salary;
        bool status;

        cout << "\nEnter Employee Name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);
        while (name.empty()) {
            cout << "\nName cannot be empty. Enter again: ";
            getline(cin, name);
        }
        newEmployee.updateEmployeeName(name);

        cout << "\nEnter Employee Age: ";
        cin >> age;
        while (age <= 17 || age >= 65) {
            cout << "\nAge must be between 18 and 64. Enter again: ";
            cin >> age;
        }
        newEmployee.updateEmployeeAge(age);

        int choice;
        cout << "\nSelect Department:\n";
        cout << "1.Management\n2.Administration\n3.Finance\n4.Technical\n5.Marketing\n6.Operations\n7.Support\n";
        cout << "Enter employee department: ";
        cin >> choice;
        while (choice < 1 || choice > 7) {//Basic department validation
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid choice. Please select a valid department: ";
            cin >> choice;
        }
        department = departmentName(choice);
        newEmployee.updateDepartment(department);

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nEnter Position: ";
        getline(cin, position);
        newEmployee.updatePosition(position);
        while (position.empty()) {
            cout << "\nPosition cannot be empty. Enter again: ";
            getline(cin, position);
        }

        cout << "\nEnter Salary $ (minimum $1700): ";
        cin >> salary;
        newEmployee.updateEmployeeSalary(salary);
        while (cin.fail() || salary <= 1699) {//Basic salary validation
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid salary. Enter again: ";
            cin >> salary;
        }
        newEmployee.updateEmployeeSalary(salary);
        

        cout << "\nEnter Email: ";
        cin.ignore();
        getline(cin, email);
        while (email.find('@') == string::npos) {//Basic email validation
            cout << "\nInvalid email. Enter again: ";
            cin >> email;
        }
        newEmployee.updateEmployeeEmail(email);

        cout << "\nEnter Phone: ";
        cin.ignore();
        getline(cin, phone);
        while (phone.length() < 8 || phone.length() > 12) {//Basic phone validation
            cout << "\nInvalid phone number length. Enter again: ";
            cin >> phone;
        }
        newEmployee.updateEmployeePhone(phone);

        newEmployee.updateEmployeeID(generateID(choice, employeeCount + 1));

        status = true; //Active by default
        newEmployee.updateEmployeeStatus(status);

        cout << "\nEmployee added successfully! Employee ID: " << newEmployee.getEmployeeID() << endl;
        employees[employeeCount++] = newEmployee;
        saveFile();
    }
    
    void viewEmployees() {
        if (employeeCount == 0) {
            cout << "\nNo employees to display." << endl;
            return;
        }

        cout << "\nSelect view option:\n1.All Employees\n2.Specific Employee\n3.Exit\n";
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\n-------------Employee List-------------" << endl;
                for (int i = 0; i < employeeCount; i++) {
                    Employee e = employees[i];
                    cout << i + 1 << ". ";
                    cout << "ID: " << e.getEmployeeID() << ", Name: " << e.getEmployeeName() 
                         << ", Department: " << e.getDepartment() << ", Position: " << e.getPosition() 
                         << ", Email: " << e.getEmployeeEmail() << ", Status: " << (e.getEmployeeStatus() ? "Active" : "Inactive") << endl;
                }
                cout << "\nTotal Employees: " << employeeCount << endl;
                break;
            case 2:
                loadEmployee();
                break;
            case 3:
                cout << "\nReturning to main menu..." << endl;
                return;
            default:
                cout << "\nInvalid choice. Please try again." << endl;
        }
    }

    void updateEmployee() {
        string name,dept, pos, email, phone,newID;
        int age, ageInput, salaryInput;
        double salary;
        char statusChoice;

        if (employeeCount == 0) {
            cout << "\nNo employees to update." << endl;
            return;
        }

        string searchID;
        cout << "\nEnter Employee ID or Name to update, [Quit to cancel]: ";
        cin >> searchID;

        if (searchID == "Quit" || searchID == "quit") {
            cout << "\nUpdate cancelled." << endl;
            return;
        }

        bool found = false;
        for (int i = 0; i < employeeCount; i++) {
            if (employees[i].getEmployeeID() == searchID || employees[i].getEmployeeName() == searchID) {
                found = true;
                Employee &e = employees[i];

                cout << "\nEmployee found: " << e.getEmployeeName() << endl;
                cout <<"1.Update Information"<<endl;
                cout <<"2.Set Employee Status"<<endl;
                cout <<"3.Exit"<<endl;
                int choice;
                cout << "\nEnter your choice: ";
                cin >> choice;

                switch (choice) {
                    case 1:
                        cout << "-------------Current details-------------" << endl;
                        cout << "Name: " << e.getEmployeeName() << endl;
                        cout << "Age: " << e.getEmployeeAge() << endl;
                        cout << "Department: " << e.getDepartment() << endl;
                        cout << "Position: " << e.getPosition() << endl;
                        cout << "Salary: " << e.getEmployeeSalary() << endl;
                        cout << "Email: " << e.getEmployeeEmail() << endl;
                        cout << "Phone: " << e.getEmployeePhone() << endl;
                        cout << "Status: " << (e.getEmployeeStatus() ? "Active" : "Inactive") << endl;
                        cout << "\nEnter new details (leave blank to keep current value):" << endl;

                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\nNew Name: ";
                        getline(cin, name);
                        if (!name.empty()) e.updateEmployeeName(name);
                        
                        cout << "\nNew Age: ";
                        if (cin.peek() != '\n') {
                            cin >> age;
                            if (age >= 18 && age <= 64) e.updateEmployeeAge(age);
                        }
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "\nNew Department:\n";
                        cout << "1.Management\n2.Administration\n3.Finance\n4.Technical\n5.Marketing\n6.Operations\n7.Support\n";
                        cout << "\nNew Department: ";
                        getline(cin, dept);
                        if (!dept.empty()) {
                            int deptChoice = stoi(dept);
                            if (deptChoice >= 1 && deptChoice <= 7) {
                                e.updateDepartment(departmentName(deptChoice));

                                newID = generateID(deptChoice, i + 1);
                                e.updateEmployeeID(newID);
                                cout << "Employee ID updated to: " << newID << endl;
                            }
                        }

                        cout << "\nNew Position: ";
                        getline(cin, pos);
                        if (!pos.empty()) e.updatePosition(pos);

                        cout << "\nNew Salary: ";
                        if (cin.peek() != '\n') {
                            cin >> salary;
                            if (salary > 1699) e.updateEmployeeSalary(salary);
                        }
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "\nNew Email: ";
                        getline(cin, email);
                        if (!email.empty() && email.find('@') != string::npos) e.updateEmployeeEmail(email);

                        cout << "\nNew Phone: ";
                        getline(cin, phone);
                        if (!phone.empty() && phone.length() >= 8 && phone.length() <= 12) e.updateEmployeePhone(phone);

                        cout << "Change Status (Active, Inactive, Enter [No changes]): ";
                        cin.get(statusChoice);
                        if (statusChoice == 'A' || statusChoice == 'a') e.updateEmployeeStatus(true);
                        else if (statusChoice == 'I' || statusChoice == 'i') e.updateEmployeeStatus(false);
                        
                        cout << "\nEmployee information updated successfully." << endl;
                        saveFile();
                        break;
                    case 2:
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Change Status (A-Active, I-Inactive, [Enter to no changes]): ";
                        cin.get(statusChoice);
                        if (statusChoice == 'A' || statusChoice == 'a') e.updateEmployeeStatus(true);
                        else if (statusChoice == 'I' || statusChoice == 'i') e.updateEmployeeStatus(false);
                        cout << "\nEmployee status updated successfully." << endl;
                        saveFile();
                        break;
                    case 3:
                        cout << "\nExiting update menu." << endl;
                        break;
                    default:
                        cout << "\nInvalid choice. Returning to main menu." << endl;
                }
            }
        }
        if (!found) {
            cout << "\nEmployee with ID " << searchID << " not found." << endl;
        }
    }

    void deleteEmployee() {
        if (employeeCount == 0) {
            cout << "\nNo employees to delete." << endl;
            return;
        }

        string searchID;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nEnter Employee ID or Name to delete [Quit to cancel]: ";
        getline(cin, searchID);
        if (searchID == "Quit" || searchID == "quit") {
            cout << "\nDelete cancelled." << endl;
            return;
        }
        
        bool found = false;
        for (int i = 0; i < employeeCount; i++) {
            if (employees[i].getEmployeeID() == searchID || employees[i].getEmployeeName() == searchID) {
                found = true;
                for (int j = i; j < employeeCount - 1; j++) {
                    employees[j] = employees[j + 1];
                }
                employeeCount--;
                cout << "\nEmployee with ID " << searchID << " deleted successfully." << endl;
                saveFile();
                break;
            }
        }
        if (!found) {
            cout << "\nEmployee with ID " << searchID << " not found." << endl;
        }
    }
};
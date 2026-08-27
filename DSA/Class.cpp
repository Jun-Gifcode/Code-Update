#include <iostream>

using namespace std;

class Employee {
private:
    string name;
    string company;
    int age;

public:
    Employee(string name, string company, int age) {
        this->name = name;
        this->company = company;
        this->age = age;
    }

    void intro_yourself() {
        cout << "Name: " << name << endl;
        cout << "Company: " << company << endl;
        cout << "Age: " << age << endl;
    }
};

int main() {
    Employee employee1("Jun", "QIU", 20);
    Employee employee2("V-Max", "QIU", 19);
    Employee employee3("Peter", "QIU", 18);

    Employee* employees[] = { &employee1, &employee2, &employee3 };

    for (int i = 0; i < 2; i++) {
        cout << "Employee " << i + 1 << ":" << endl;
        employees[i]->intro_yourself();
        cout << endl;
    }

    return 0;
}
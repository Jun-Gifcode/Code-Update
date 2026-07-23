#include <iostream>
#include <string>

using namespace std;

class Person{
private:
    string personName;
    int personAge;

public:
    Person(): personName("User"), personAge(0) {};
    
    void setName(string name){
        personName = name;
    }
    void setAge(int age){
        personAge = age;
    }
    string getName() const {
        return personName;
    }
    int getAge() const {
        return personAge;
    }
};

int main(){

    Person info;

    cout << "Name: " << info.getName() << endl;
    cout << "Age: " << info.getAge() << endl;
}
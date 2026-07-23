#include <iostream>
#include <cmath> //math function
#include <ctime> //time function

using std::cout;
using std::cin;
using string = std::string;

string concatStrings(string str1, string str2){
    return str1 + " " + str2;
}

int main(){
    
    /*
    string name;

    cout << "Whats your name:";
    std::getline(cin >>std::ws, name); //std::ws eat /n

    //name.length(); //length of string
    //name.empty(); //check string is empty or not
    //name.clear(); //clear string
    //name.append("suffix"); //add suffix to string
    //name.at(0); //access character at index 0
    //name.insert(0,"prefix"); //add prefix to string
    //name.erase(0,3); //erase 3 character from index 0
    //name.find("substring"); //find substring in string

    std::cout << "Your name "<< name;
    */

    //double x = 3, y = 4, z;

    //z = std::max(x,y);
    //z = std::min(x,y);
    //z = pow(2,3);
    //z = sqrt(9);
    //z = abs(-3); //absolute fubction (3)
    //z = round(3.14); //z = floor(3.14); // 3.14 = 3
    //z = ceil(3.14); // 3.14 = 4

    //cout << z;

    /*
    double a,b,c;

    cout << "Enter side A : ";
    cin >> a;

    cout << "Enter side B : ";
    cin >> b;

    c = sqrt(pow(a,2) + pow(b,2));

    cout <<"Side C: "<< c << std::endl;
    */

    /*
    int age;

    cout << "Enter Your age: ";
    cin >> age;

    if (age >= 18)
    {
        cout << "You are "<< age <<" ,You are adult.";
    }
    else 
    {
        cout << "You are "<< age <<" ,You aren't adult.";
    }
    */
    
    //age >=18 ? cout << "You are adult." : cout << "You aren't adult.";
    //cout << (age >=18 ? "You are adult." : "You aren't adult.");
    // if else condition in one line

    //continue;// skip current iteration of loop
    //break; //exit loop

    srand(time(NULL)); //seed random number generator
    int num = rand() % 6 + 1; //random number between 1 and 6
    //cout << num;
    
    string str1, str2;
    str1 = "Hello";
    str2 = "Jun";
    cout << concatStrings(str1, str2);

    return 0;
}
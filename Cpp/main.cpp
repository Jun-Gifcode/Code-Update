#include <iostream>
#include <string>
#include "account.h"

using namespace std;
    
int main(){
    string accountname;
    Account myaccount{"User"};

    cout << "Defaullt name: "<< myaccount.getName() << endl;
    cout << "Enter account name: ";
    getline(cin, accountname);

    myaccount.setName(accountname);

    cout << "Account Name: " << myaccount.getName() << endl;
    
}
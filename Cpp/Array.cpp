#include <iostream>
#include <iomanip>
#include <array>

using namespace std;

int main (){
    const size_t arraySize {5};
    array <int,arraySize> a{10,20,30,40,50};
    int total{0};

    for (size_t i{0}; i < a.size(); ++i){
        total += a[i];

        if (i == a.size() - 1)
            cout << a[i] << " ";
        else
        cout << a[i] << " + ";
    }

    cout << "= " << total << endl;
    return 0;
}
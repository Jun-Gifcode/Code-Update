#include <iostream>
#include <iomanip>
#include <array>
using namespace std;

/*
int main() {
array<int, 5> n; // n is an array of 5 int values

// initialize elements of array n to 0
for (size_t i{0}; i < n.size(); ++i) {
n[i] = 0; // set element at location i to O
}

cout << "Element" <<setw(10) << "Value" << endl;

// output each array element's value
for (size_t j{0}; j < n.size(); ++j) {
cout << setw(7) << j << setw(10) << n[j] << endl;
}
}*/

/*
int main() {

const size_t arraySize{11};
array<unsigned int, arraySize> n{0, 0, 0, 0, 0, 0, 1, 2, 4, 2, 1};

cout << "Grade distribution:" << endl;

// for each element of array n, output a bar of the chart
for (size_t i{0}; i < n.size(); ++i) {
// output bar labels ("0-9:", ..., "90-99:", "100:")
if (0 == i) {
cout << " 0-9: ";
}
else if (10 == i) {
cout << " 100: ";
}
else {
cout << i * 10 << "-" << (i * 10) + 9 << ":";
}

for (unsigned int stars{0}; stars < n[i]; ++stars) {
cout << '*';
}

cout << endl; // start a new line of output
}
}*/

/*
int main() {
// define array sizes
const size_t responseSize{20}; // size of array responses
const size_t frequencySize{6}; // size of array frequency

// place survey responses in array responses

const array<unsigned int, responseSize> responses{
1, 2, 5, 4, 3, 5, 2, 1, 3, 1, 4, 3, 3, 3, 2, 3, 3, 2, 2, 5};

// initialize frequency counters to 0
array<unsigned int, frequencySize> frequency{};

// for each answer, select responses element and use that value
// as frequency subscript to determine element to increment
for (size_t answer{0}; answer < responses.size(); ++answer) {
++frequency[responses[answer]];
}

cout << "Rating" << setw(12) << "Frequency" << endl;

// output each array element's value

for (size_t rating{1}; rating < frequency.size(); ++rating) {
cout << setw(6) << rating << setw(12) << frequency [rating] << endl;
}
}*/

void staticArrayInit(); // function prototype
void automaticArrayInit();// function prototуре
const size_t arraySize{3};

int main() {

cout << "First call to each function:\n";
staticArrayInit();
automaticArrayInit();

cout << "\n\nSecond call to each function:\n";
staticArrayInit();
automaticArrayInit();
cout << endl;
}

// function to demonstrate a static local array
void staticArrayInit(void) {
// initializes elements to 0 first time function is called
static array<int, arraySize> array1; // static local array
cout << "\nValues on entering staticArrayInit:\n";
// output contents of array1

for (size_t i{0}; i < array1.size(); ++i) {
cout << "array1[" << i << "] = " << array1[i] << " ";
}
cout << "\nValues on exiting staticArrayInit:\n";
// modify and output contents of array1
for (size_t j{0}; j < array1.size(); ++j) {
cout << "array1[" << j << "] = " << (array1[j] += 5) <<" ";
}
}
// function to demonstrate an automatic local array
void automaticArrayInit(void) {

// initializes elements each time function is called
array<int, arraySize> array2{1, 2, 3}; // automatic local array

cout << "\n\nValues on entering automaticArrayInit:\n";
// output contents of array2
for (size_t i{0}; i < array2.size(); ++i) {
cout << "array2 [" << i << "] = " << array2 [i] <<" ";
}
cout << "\nValues on exiting automaticArrayInit:\n";
// modify and output contents of array2
for (size_t j{0}; j < array2.size(); ++j) {
cout << "array2[" << j << "] = " << (array2[j] += 5) << " ";
}
}
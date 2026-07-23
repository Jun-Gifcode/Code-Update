//
// Created by User on 11/25/2025.
//
#include <iostream>//contain the basic function of input/output
#include <vector>

namespace first
{
    int x = 1;
}

//typedef std::vector<std::pair<std::string, int>> pairlist_t;// covert data or function into shorter term "pairlist_t"
//typedef std::string string;// simplified
using string = std::string;//work better


int main(){
    //std::cout(standard character output) << (output(Left shift output))"content";
    //<< next
    //std::endl represent of end of the line

    /* // print function
    std::cout<<"Hello World!"<<std::endl;//eat buffer
    std::cout<<"I like pizza!"<<'\n';//better performance
    */

    /* // string and arrangement output
    std::string name = "Jun";
    std::cout << name << std::endl;
    std::cout << "Hello " << name << std::endl;
    */

    const double PI = 3.141592653589793;//fix variable declaration
    // int x = 0;
    // std::cout << first::x << std::endl;
    //using namespace first;
    //std::cout << x << std::endl;

    //pairlist_t pairs; // callout data



    return 0;
}
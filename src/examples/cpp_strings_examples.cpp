// SSUDS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string.h>
#include <string> //new for c++
#include <person.h>

using namespace std;

int main()
{
    int x;
    std::string cpp_name = "Bob Jones"; //internally, the # of chars is still important, but we dont have to allocate it
    cpp_name = "Robert Jones";
    //std::cout << cpp_name << "\n";
    x = cpp_name.length();
    //std::cout << x << "\n";
    //if (cpp_name < "mmmm")
        //std::cout << "cpp_name is alphabetically less\n";

    Person p;
    Person q;

   // p.id = 42;
   //p.first_name = "Bob";

   // std::cout << p.id << " " << p.firstname;
}

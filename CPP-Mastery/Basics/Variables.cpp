/*
----------------------------------------
Topic : Variables & Data Types
Difficulty : Easy
Time Complexity : O(1)
Space Complexity : O(1)
Author : Prakhar Ojha
----------------------------------------
Concept:
A variable is a named piece of memory with a type that determines
what kind of data it can hold and how much space it occupies.
C++ is statically typed: the type is fixed at compile time.

Example:
Input : declare int, float, double, char, bool
Output : prints each value and its size in bytes
----------------------------------------
*/

#include <iostream>
using namespace std;

int main() {
    int age = 21;
    float height = 5.9f;
    double pi = 3.14159265358979;
    char grade = 'A';
    bool isStudent = true;

    cout << "int age = " << age << " (size: " << sizeof(age) << " bytes)" << endl;
    cout << "float height = " << height << " (size: " << sizeof(height) << " bytes)" << endl;
    cout << "double pi = " << pi << " (size: " << sizeof(pi) << " bytes)" << endl;
    cout << "char grade = " << grade << " (size: " << sizeof(grade) << " bytes)" << endl;
    cout << "bool isStudent = " << isStudent << " (size: " << sizeof(isStudent) << " bytes)" << endl;

    return 0;
}

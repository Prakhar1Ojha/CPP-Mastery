/*
----------------------------------------
Topic : Operators
Difficulty : Easy
Time Complexity : O(1)
Space Complexity : O(1)
Author : Prakhar Ojha
----------------------------------------
Concept:
C++ operators fall into categories: arithmetic (+ - * / %),
relational (== != < > <= >=), logical (&& || !), bitwise
(& | ^ ~ << >>), and assignment (= += -= etc).
The modulo operator % only works on integers, not floats.

Example:
Input : a = 10, b = 3
Output : a+b=13, a-b=7, a*b=30, a/b=3, a%b=1
----------------------------------------
*/

#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 3;

    cout << "a + b = " << (a + b) << endl;
    cout << "a - b = " << (a - b) << endl;
    cout << "a * b = " << (a * b) << endl;
    cout << "a / b = " << (a / b) << " (integer division)" << endl;
    cout << "a % b = " << (a % b) << endl;

    cout << "a == b: " << (a == b) << endl;
    cout << "a > b: " << (a > b) << endl;

    cout << "a << 1 = " << (a << 1) << " (left shift = multiply by 2)" << endl;
    cout << "a >> 1 = " << (a >> 1) << " (right shift = divide by 2)" << endl;

    return 0;
}

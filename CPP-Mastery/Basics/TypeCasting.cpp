/*
----------------------------------------
Topic : Type Casting
Difficulty : Easy
Time Complexity : O(1)
Space Complexity : O(1)
Author : Prakhar Ojha
----------------------------------------
Concept:
static_cast<T>(value) is the preferred way to convert between
related types (int<->double, base<->derived pointers with care).
It's checked at compile time, unlike a C-style cast (T)value
which silently allows unsafe conversions.

Example:
Input : double d = 9.7
Output : static_cast<int>(d) = 9 (truncates, does not round)
----------------------------------------
*/

#include <iostream>
using namespace std;

int main() {
    double d = 9.7;
    int truncated = static_cast<int>(d);
    cout << "double " << d << " -> int " << truncated << " (truncated, not rounded)" << endl;

    char c = 'A';
    int asciiValue = static_cast<int>(c);
    cout << "char '" << c << "' -> int " << asciiValue << " (ASCII value)" << endl;

    int i = 65;
    char backToChar = static_cast<char>(i);
    cout << "int " << i << " -> char '" << backToChar << "'" << endl;

    return 0;
}

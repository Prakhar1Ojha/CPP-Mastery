/*
----------------------------------------
Topic : Input / Output
Difficulty : Easy
Time Complexity : O(n) for reading n items
Space Complexity : O(1)
Author : Prakhar Ojha
----------------------------------------
Concept:
cin >> skips whitespace and reads token by token, which breaks
on strings with spaces. getline(cin, str) reads a full line
including spaces. Mixing cin >> and getline() is a classic bug:
after cin >> n, a leftover newline sits in the buffer, so the
next getline() reads an empty string unless you cin.ignore() first.

Example:
Input : 5 (then a full name line "Prakhar Ojha")
Output : n=5, name="Prakhar Ojha"
----------------------------------------
*/

#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;

    cin.ignore(); // clear leftover newline before getline

    string name;
    cout << "Enter your full name: ";
    getline(cin, name);

    cout << "n = " << n << ", name = \"" << name << "\"" << endl;

    return 0;
}

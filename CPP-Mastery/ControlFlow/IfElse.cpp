/*
----------------------------------------
Topic : If-Else Conditionals
Difficulty : Easy
Time Complexity : O(1)
Space Complexity : O(1)
Author : Prakhar Ojha
----------------------------------------
Concept:
if/else if/else evaluates conditions top-down and executes the
first branch that's true. Only one branch ever runs. Ternary
operator (cond ? a : b) is a compact alternative for simple
two-way branches.

Example:
Input : marks = 78
Output : Grade: B
----------------------------------------
*/

#include <iostream>
using namespace std;

char getGrade(int marks) {
    if (marks >= 90) return 'A';
    else if (marks >= 75) return 'B';
    else if (marks >= 60) return 'C';
    else if (marks >= 40) return 'D';
    else return 'F';
}

int main() {
    int marks = 78;
    cout << "Grade: " << getGrade(marks) << endl;

    // Ternary equivalent for a simpler two-way check
    int n = 7;
    string parity = (n % 2 == 0) ? "even" : "odd";
    cout << n << " is " << parity << endl;

    return 0;
}

/*
----------------------------------------
Topic : Pattern Printing
Difficulty : Easy
Time Complexity : O(n^2)
Space Complexity : O(1)
Author : Prakhar Ojha
----------------------------------------
Concept:
Pattern printing is nested-loop practice: the outer loop controls
rows, the inner loop(s) control what's printed per row. Good
warm-up for thinking in terms of row/column relationships before
moving to 2D array and matrix problems.

Example:
Input : n = 4
Output : right triangle of stars, 4 rows
----------------------------------------
*/

#include <iostream>
using namespace std;

int main() {
    int n = 4;

    // Right triangle
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            cout << "* ";
        }
        cout << endl;
    }
    cout << endl;

    // Inverted right triangle
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            cout << "* ";
        }
        cout << endl;
    }
    cout << endl;

    // Pyramid (centered)
    for (int i = 1; i <= n; i++) {
        for (int s = 1; s <= n - i; s++) cout << "  ";
        for (int j = 1; j <= (2 * i - 1); j++) cout << "* ";
        cout << endl;
    }

    return 0;
}

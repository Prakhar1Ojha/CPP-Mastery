/*
----------------------------------------
Topic : Data Type Ranges & Limits
Difficulty : Easy
Time Complexity : O(1)
Space Complexity : O(1)
Author : Prakhar Ojha
----------------------------------------
Concept:
Every fixed-width type has a min/max range defined by <climits>
and <cfloat>. Knowing these ranges matters for avoiding overflow
bugs, especially in competitive programming (e.g. int overflow
around 2^31).

Example:
Output : prints INT_MIN, INT_MAX, LONG_MAX, etc.
----------------------------------------
*/

#include <iostream>
#include <climits>
using namespace std;

int main() {
    cout << "int range: " << INT_MIN << " to " << INT_MAX << endl;
    cout << "long long range: " << LLONG_MIN << " to " << LLONG_MAX << endl;
    cout << "char range: " << (int)CHAR_MIN << " to " << (int)CHAR_MAX << endl;
    cout << "unsigned int max: " << UINT_MAX << endl;

    // Overflow demonstration
    int overflowDemo = INT_MAX;
    overflowDemo += 1;
    cout << "INT_MAX + 1 overflows to: " << overflowDemo << endl;

    return 0;
}

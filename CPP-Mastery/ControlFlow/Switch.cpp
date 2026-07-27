/*
----------------------------------------
Topic : Switch Statement
Difficulty : Easy
Time Complexity : O(1)
Space Complexity : O(1)
Author : Prakhar Ojha
----------------------------------------
Concept:
switch is best when comparing one variable against several
discrete constant values (int, char, enum) — it reads cleaner
than a long if-else chain. Forgetting break causes fall-through
to the next case, which is a common source of bugs (sometimes
used intentionally to group cases together).

Example:
Input : day = 3
Output : Wednesday
----------------------------------------
*/

#include <iostream>
using namespace std;

int main() {
    int day = 3;

    switch (day) {
        case 1:
            cout << "Monday" << endl;
            break;
        case 2:
            cout << "Tuesday" << endl;
            break;
        case 3:
            cout << "Wednesday" << endl;
            break;
        case 6:
        case 7:
            // intentional fall-through: both map to "Weekend"
            cout << "Weekend" << endl;
            break;
        default:
            cout << "Invalid day" << endl;
    }

    return 0;
}

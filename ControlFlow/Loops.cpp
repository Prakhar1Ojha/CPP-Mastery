/*
----------------------------------------
Topic : Loops (for, while, do-while)
Difficulty : Easy
Time Complexity : O(n)
Space Complexity : O(1)
Author : Prakhar Ojha
----------------------------------------
Concept:
- for: best when the iteration count is known upfront.
- while: best when the condition is checked before each
  iteration and the count isn't known ahead of time.
- do-while: guarantees at least one execution since the
  condition is checked after the body runs.

Example:
Input : n = 5
Output : sum of 1..5 = 15 (computed 3 ways)
----------------------------------------
*/

#include <iostream>
using namespace std;

int main() {
    int n = 5;

    // for loop
    int sumFor = 0;
    for (int i = 1; i <= n; i++) sumFor += i;
    cout << "for loop sum: " << sumFor << endl;

    // while loop
    int sumWhile = 0, i = 1;
    while (i <= n) {
        sumWhile += i;
        i++;
    }
    cout << "while loop sum: " << sumWhile << endl;

    // do-while loop
    int sumDoWhile = 0, j = 1;
    do {
        sumDoWhile += j;
        j++;
    } while (j <= n);
    cout << "do-while loop sum: " << sumDoWhile << endl;

    return 0;
}

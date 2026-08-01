/*
 * LeetCode 7. Reverse Integer
 *
 * Reverse digits of a 32-bit signed integer.
 * Return 0 if the reversed value overflows.
 *
 * Time:  O(log |x|)
 * Space: O(1)
 */

#include <iostream>
#include <climits>
using namespace std;

class Solution {
public:
    int reverse(int x) {
        int rev = 0;

        while (x != 0) {
            int digit = x % 10;
            x /= 10;

            // Check overflow BEFORE multiplying
            if (rev > INT_MAX / 10 || (rev == INT_MAX / 10 && digit > 7))
                return 0;
            if (rev < INT_MIN / 10 || (rev == INT_MIN / 10 && digit < -8))
                return 0;

            rev = rev * 10 + digit;
        }

        return rev;
    }
};

int main() {
    Solution sol;

    cout << sol.reverse(123) << endl;          // 321
    cout << sol.reverse(-123) << endl;         // -321
    cout << sol.reverse(120) << endl;          // 21
    cout << sol.reverse(0) << endl;            // 0
    cout << sol.reverse(1534236469) << endl;   // 0 (overflow)
    cout << sol.reverse(-2147483648) << endl;  // 0 (overflow)

    return 0;
}

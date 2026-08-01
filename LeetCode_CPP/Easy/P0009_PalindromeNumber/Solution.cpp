/*
 * LeetCode 9. Palindrome Number
 *
 * Determine whether an integer is a palindrome without converting to string.
 *
 * Time:  O(log x)
 * Space: O(1)
 */

#include <iostream>
using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        // Negatives and numbers ending with 0 (except 0) are not palindromes
        if (x < 0 || (x % 10 == 0 && x != 0))
            return false;

        int reversedHalf = 0;

        // Reverse only the second half
        while (x > reversedHalf) {
            reversedHalf = reversedHalf * 10 + x % 10;
            x /= 10;
        }

        // Even digits: x == reversedHalf
        // Odd digits:  x == reversedHalf / 10 (ignore middle digit)
        return x == reversedHalf || x == reversedHalf / 10;
    }
};

int main() {
    Solution sol;

    cout << boolalpha;
    cout << sol.isPalindrome(121) << endl;    // true
    cout << sol.isPalindrome(-121) << endl;   // false
    cout << sol.isPalindrome(10) << endl;     // false
    cout << sol.isPalindrome(0) << endl;      // true
    cout << sol.isPalindrome(12321) << endl;  // true
    cout << sol.isPalindrome(123321) << endl; // true

    return 0;
}

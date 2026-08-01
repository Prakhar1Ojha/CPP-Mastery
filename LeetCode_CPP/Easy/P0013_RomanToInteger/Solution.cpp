/*
 * LeetCode 13. Roman to Integer
 *
 * Convert a Roman numeral string to an integer.
 *
 * Time:  O(n)
 * Space: O(1)
 */

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> map = {
            {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
            {'C', 100}, {'D', 500}, {'M', 1000}
        };

        int total = 0;
        int n = s.size();

        for (int i = 0; i < n; i++) {
            int value = map[s[i]];

            // Lookahead: current < next → subtractive case
            if (i + 1 < n && value < map[s[i + 1]]) {
                total -= value;
            } else {
                total += value;
            }
        }

        return total;
    }

    // Alternative: right-to-left
    int romanToIntRTL(string s) {
        unordered_map<char, int> map = {
            {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
            {'C', 100}, {'D', 500}, {'M', 1000}
        };

        int total = 0, prev = 0;
        for (int i = s.size() - 1; i >= 0; i--) {
            int curr = map[s[i]];
            total += (curr >= prev) ? curr : -curr;
            prev = curr;
        }
        return total;
    }
};

int main() {
    Solution sol;

    cout << sol.romanToInt("III") << endl;      // 3
    cout << sol.romanToInt("LVIII") << endl;    // 58
    cout << sol.romanToInt("MCMXCIV") << endl;  // 1994
    cout << sol.romanToInt("IX") << endl;       // 9
    cout << sol.romanToInt("XL") << endl;       // 40
    cout << sol.romanToInt("CDXLIV") << endl;   // 444

    return 0;
}

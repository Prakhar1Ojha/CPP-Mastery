/*
 * LeetCode 1. Two Sum
 *
 * Given an array of integers nums and an integer target,
 * return indices of the two numbers such that they add up to target.
 *
 * Approaches:
 * 1. Brute Force       - O(n^2) time, O(1) space
 * 2. Hash Map One-Pass - O(n) time, O(n) space  (Optimal)
 */

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    // -----------------------------------------------------------------
    // Approach 1: Brute Force
    // -----------------------------------------------------------------
    vector<int> twoSumBruteForce(vector<int>& nums, int target) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
        return {-1, -1};
    }

    // -----------------------------------------------------------------
    // Approach 2: Hash Map One-Pass (Recommended)
    // -----------------------------------------------------------------
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> map; // value -> index

        for (int i = 0; i < (int)nums.size(); i++) {
            int complement = target - nums[i];

            if (map.count(complement)) {
                return {map[complement], i};
            }

            map[nums[i]] = i;
        }

        return {-1, -1};
    }
};

// ---------------------------------------------------------------------
// Test Driver
// ---------------------------------------------------------------------
int main() {
    Solution sol;

    vector<int> nums1 = {2, 7, 11, 15};
    auto r1 = sol.twoSum(nums1, 9);
    cout << "Example 1: [" << r1[0] << ", " << r1[1] << "]" << endl; // [0, 1]

    vector<int> nums2 = {3, 2, 4};
    auto r2 = sol.twoSum(nums2, 6);
    cout << "Example 2: [" << r2[0] << ", " << r2[1] << "]" << endl; // [1, 2]

    vector<int> nums3 = {3, 3};
    auto r3 = sol.twoSum(nums3, 6);
    cout << "Example 3: [" << r3[0] << ", " << r3[1] << "]" << endl; // [0, 1]

    vector<int> nums4 = {-1, -2, -3, -4, -5};
    auto r4 = sol.twoSum(nums4, -8);
    cout << "Negatives: [" << r4[0] << ", " << r4[1] << "]" << endl; // [2, 4]

    return 0;
}


# 1. Two Sum

**Difficulty:** Easy  
**Topics:** Array, Hash Table  
**LeetCode:** [Two Sum](https://leetcode.com/problems/two-sum/)

---

## Problem Statement

Given an array of integers `nums` and an integer `target`, return **indices** of the two numbers such that they add up to `target`.

You may assume that each input would have **exactly one solution**, and you may not use the same element twice.

You can return the answer in any order.

### Examples

**Example 1:**
```
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
```

**Example 2:**
```
Input: nums = [3,2,4], target = 6
Output: [1,2]
```

**Example 3:**
```
Input: nums = [3,3], target = 6
Output: [0,1]
```

### Constraints
- `2 <= nums.length <= 10^4`
- `-10^9 <= nums[i] <= 10^9`
- `-10^9 <= target <= 10^9`
- Only one valid answer exists.

---

## Approach 1: Brute Force (Beginner)

### Idea
Check every pair of numbers. For each index `i`, loop through all indices `j > i` and check if `nums[i] + nums[j] == target`.

### Complexity
- **Time:** O(n²) — nested loops
- **Space:** O(1)

### When to use
Good for understanding the problem. Too slow for large inputs (n = 10⁴ → ~10⁸ operations).

---

## Approach 2: Hash Map – One Pass (Optimal)

### Idea
While iterating, store each number and its index in a HashMap.  
For the current number `x`, check if `target - x` already exists in the map.  
If yes → we found the pair.

### Why it works
- We only need one pass because when we see the second number of the pair, the first one is already stored.
- HashMap gives O(1) average lookup.

### Complexity
- **Time:** O(n)
- **Space:** O(n)

### Step-by-step
1. Create an empty `HashMap<Integer, Integer>` (value → index).
2. For each index `i`:
   - Compute `complement = target - nums[i]`.
   - If `complement` exists in map → return `[map.get(complement), i]`.
   - Otherwise put `nums[i] → i` into the map.

---

## Edge Cases to Consider
| Case | Example | Notes |
|------|---------|-------|
| Two same numbers | `[3,3], target=6` | Works — different indices |
| Negative numbers | `[-1,-2,-3,-4], target=-6` | HashMap handles negatives fine |
| Minimum size | `[1,2], target=3` | Only one pair |
| Large values | near ±10⁹ | Use `int` carefully (no overflow in sum check needed here) |

---

## Key Takeaways
- **Brute force** teaches nested loops and pair checking.
- **HashMap** is the classic optimization: trade space for time.
- Pattern: “Looking for a complement” → think HashMap.
- This is one of the most frequently asked interview questions.

---

## Follow-up Questions (Advanced)
1. What if the array is sorted? (Two pointers → O(n) time, O(1) space)
2. What if there are multiple valid pairs? Return all of them.
3. What if we need the numbers themselves instead of indices?
4. Three Sum / Four Sum generalizations.


# 7. Reverse Integer

**Difficulty:** Easy  
**Topics:** Math  
**LeetCode:** [Reverse Integer](https://leetcode.com/problems/reverse-integer/)

---

## Problem Statement

Given a signed 32-bit integer `x`, return `x` with its digits reversed.  
If reversing `x` causes the value to go outside the signed 32-bit integer range `[-2³¹, 2³¹ - 1]`, then return `0`.

Assume the environment does **not** allow you to store 64-bit integers (i.e., you must handle overflow carefully).

### Examples

**Example 1:**
```
Input: x = 123
Output: 321
```

**Example 2:**
```
Input: x = -123
Output: -321
```

**Example 3:**
```
Input: x = 120
Output: 21
```

### Constraints
- `-2³¹ <= x <= 2³¹ - 1`

---

## Approach: Digit Extraction + Overflow Check

### Idea
1. Repeatedly take the last digit (`x % 10`) and append it to the result.
2. Remove the last digit from `x` (`x / 10`).
3. Before multiplying the current result by 10, check whether the next operation would overflow.

### Overflow Detection (Important)
Before doing `rev = rev * 10 + digit`:
- If `rev > Integer.MAX_VALUE / 10` → overflow
- If `rev == Integer.MAX_VALUE / 10` and `digit > 7` → overflow (MAX = 2147483647)
- Same logic for `Integer.MIN_VALUE` (digit < -8)

### Complexity
- **Time:** O(log₁₀|x|) — number of digits
- **Space:** O(1)

---

## Edge Cases
| Case | Example | Result |
|------|---------|--------|
| Trailing zeros | 120 | 21 |
| Negative | -123 | -321 |
| Overflow | 1534236469 | 0 |
| Single digit | 5 | 5 |
| MIN_VALUE | -2147483648 | 0 (cannot reverse safely) |

---

## Key Takeaways
- Always think about integer overflow when reversing or multiplying.
- `%` and `/` work correctly with negative numbers in Java (towards zero).
- This problem trains careful boundary checking.

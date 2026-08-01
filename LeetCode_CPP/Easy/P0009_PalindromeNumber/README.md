# 9. Palindrome Number

**Difficulty:** Easy  
**Topics:** Math  
**LeetCode:** [Palindrome Number](https://leetcode.com/problems/palindrome-number/)

---

## Problem Statement

Given an integer `x`, return `true` if `x` is a **palindrome**, and `false` otherwise.

An integer is a palindrome when it reads the same forward and backward.

### Examples

```
Input: x = 121
Output: true

Input: x = -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-.

Input: x = 10
Output: false
Explanation: Reads 01 from right to left.
```

### Constraints
- `-2³¹ <= x <= 2³¹ - 1`

**Follow-up:** Could you solve it without converting the integer to a string?

---

## Approach 1: Convert to String (Beginner)

Convert the number to a string and check if it equals its reverse.  
Simple but uses extra space and may not be allowed in interviews.

- Time: O(n) where n = number of digits
- Space: O(n)

---

## Approach 2: Reverse Half of the Number (Optimal)

### Idea
- Negative numbers are never palindromes.
- Numbers ending with 0 (except 0 itself) are never palindromes.
- Reverse only the **second half** of the digits and compare with the first half.
- This avoids overflow issues that full reversal might cause.

### Steps
1. If `x < 0` or (`x % 10 == 0` && `x != 0`) → return false.
2. Reverse digits until the reversed part becomes ≥ the remaining part.
3. Compare: either equal (even digits) or `x == rev / 10` (odd digits, middle digit ignored).

### Complexity
- **Time:** O(log₁₀ x)
- **Space:** O(1)

---

## Edge Cases
| Case | Result | Reason |
|------|--------|--------|
| Negative | false | Sign makes it non-palindrome |
| Ends with 0 (not 0) | false | Leading zero after reverse |
| Single digit | true | Always palindrome |
| 0 | true | |

---

## Key Takeaways
- Avoid string conversion when possible (follow-up requirement).
- Reversing only half the digits is elegant and prevents overflow.
- Early rejection of negatives and trailing zeros saves work.

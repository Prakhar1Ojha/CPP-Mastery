# 13. Roman to Integer

**Difficulty:** Easy  
**Topics:** Hash Table, Math, String  
**LeetCode:** [Roman to Integer](https://leetcode.com/problems/roman-to-integer/)

---

## Problem Statement

Roman numerals are represented by seven symbols:

| Symbol | Value |
|--------|-------|
| I      | 1     |
| V      | 5     |
| X      | 10    |
| L      | 50    |
| C      | 100   |
| D      | 500   |
| M      | 1000  |

Roman numerals are usually written largest to smallest from left to right.  
However, there are six instances where subtraction is used:
- I before V or X → 4, 9
- X before L or C → 40, 90
- C before D or M → 400, 900

Given a roman numeral, convert it to an integer.

### Examples
```
Input: s = "III"
Output: 3

Input: s = "LVIII"
Output: 58
Explanation: L = 50, V = 5, III = 3

Input: s = "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90, IV = 4
```

### Constraints
- `1 <= s.length <= 15`
- `s` contains only characters `('I', 'V', 'X', 'L', 'C', 'D', 'M')`
- It is **guaranteed** that `s` is a valid roman numeral in the range `[1, 3999]`

---

## Approach: Single Pass with Lookahead

### Idea
Iterate from left to right.  
If the current symbol’s value is **less than** the next symbol’s value, it is a subtractive case → subtract current.  
Otherwise add current.

### Complexity
- **Time:** O(n)
- **Space:** O(1) (fixed map of 7 symbols)

---

## Alternative: Right-to-Left
Start from the end. Keep a `prev` value.  
If current ≥ prev → add, else subtract.  
Also very clean.

---

## Key Takeaways
- The subtractive cases are the only “special” rule.
- A simple map + one pass is enough.
- Because input is guaranteed valid, no error handling is needed.

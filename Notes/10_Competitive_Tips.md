# Competitive Programming Tips

Practical, hard-won conventions for CP and timed coding interviews — less "concept," more "how to not lose time to silly mistakes."

---

## 1. Fast I/O (Beginner — do this every time)

```cpp
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // ... rest of program
}
```
Without this, `cin`/`cout` sync with C's `stdio` on every call — on inputs with 10^5+ lines, this alone can be the difference between AC (accepted) and TLE (time limit exceeded). Never mix `cin`/`cout` with `scanf`/`printf` in the same program after disabling sync.

---

## 2. Know Your Complexity Budget (Beginner–Intermediate)

Competitive judges typically allow ~10^8 simple operations per second. Use the constraint (`n ≤ ...`) to reverse-engineer the required complexity *before* writing code:

| n ≤ | Required complexity |
|---|---|
| 10 | O(n!) or O(2^n · n) — brute force/backtracking fine |
| 20 | O(2^n) — bitmask DP |
| 500 | O(n^3) |
| 5,000 | O(n^2 log n) |
| 10^5 | O(n log n) |
| 10^6 – 10^7 | O(n) or O(n log n) with small constant |
| 10^9+ | O(log n) or O(1) — usually math/binary search |

If your first idea's complexity doesn't fit the constraint, that's the signal to rethink the approach *before* coding — not after a TLE.

---

## 3. Integer Overflow (Beginner — the #1 silent bug)

`int` in C++ is typically 32-bit, capping around 2.1 × 10^9. Multiplying two numbers near 10^5 already overflows (`10^5 * 10^5 = 10^10`).

```cpp
int a = 100000, b = 100000;
int overflow = a * b;        // WRONG — overflows int
long long safe = (long long)a * b; // cast BEFORE multiplying, not after
```
Rule of thumb: if a problem's constraints suggest the answer could exceed ~2×10^9, use `long long` (or `unsigned long long` if negatives are impossible) for every intermediate calculation, not just the final answer.

---

## 4. Common STL Shortcuts for Speed (Intermediate)

```cpp
// Read entire line fast:
string s; getline(cin, s);

// Sort with custom comparator:
sort(v.begin(), v.end(), [](int a, int b) { return a > b; });

// Remove duplicates from a sorted vector:
v.erase(unique(v.begin(), v.end()), v.end());

// Fast prefix sums for range-sum queries:
vector<long long> prefix(n + 1, 0);
for (int i = 0; i < n; i++) prefix[i+1] = prefix[i] + arr[i];
// sum(l, r) = prefix[r+1] - prefix[l]
```

---

## 5. Debugging Under Time Pressure (Intermediate)

- Print variable state with clear labels (`cerr << "x=" << x << " y=" << y << endl;`) — using `cerr` keeps debug output separate from the actual program output being judged.
- Check off-by-one errors first: `<` vs `<=`, `n` vs `n-1` are the most common single-character bugs in CP.
- Re-read constraints for edge cases: `n = 0`, `n = 1`, all-same elements, negative numbers, empty input.

---

## 6. Template Boilerplate (Intermediate)

A reusable starting template saves setup time across problems:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vi vector<int>
#define pb push_back

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        // solve one test case
    }
    return 0;
}
```
Note: `#include <bits/stdc++.h>` (pulls in the whole standard library) is fine for CP speed, but avoid it in production/interview code — it's non-standard (GCC-specific) and considered poor practice outside of contests, where compile-time and portability matter.

---

## 7. Binary Search on the Answer (Advanced pattern)

When a problem asks for the "minimum X such that condition holds" (or maximum), and the condition is monotonic (once true, stays true as X increases), binary search the answer space itself instead of the array:

```cpp
int lo = 0, hi = maxPossible;
while (lo < hi) {
    int mid = lo + (hi - lo) / 2;   // avoids overflow vs (lo+hi)/2
    if (feasible(mid)) hi = mid;     // condition holds — try smaller
    else lo = mid + 1;
}
// lo is now the minimum feasible answer
```
This pattern shows up constantly once you learn to recognize it — "minimize the maximum," "maximize the minimum," capacity/speed problems, etc.

---

## 8. Practice Strategy (General)

- Don't just solve problems — after solving (or after 30-45 min stuck), read the editorial and note the *pattern*, not just the specific solution. Patterns transfer; specific solutions don't.
- Track weak topics explicitly (a simple spreadsheet: topic, problems solved, problems stuck on) rather than solving randomly — targeted practice on weak areas beats volume on strong ones.
- For interviews specifically: practice explaining your approach *out loud* before coding, and state time/space complexity unprompted at the end — both are usually part of the evaluation, not just "does it pass."

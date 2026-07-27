# STL (Standard Template Library)

The STL is four things working together: **Containers** (store data), **Iterators** (traverse containers uniformly), **Algorithms** (operate on ranges via iterators), and **Function objects/lambdas** (customize algorithm behavior). Knowing it cold is non-negotiable for competitive programming and MAANG interviews — reimplementing what STL already gives you for free wastes interview time.

---

## 1. Sequence Containers (Beginner)

### `vector` — dynamic array
```cpp
vector<int> v = {1, 2, 3};
v.push_back(4);      // O(1) amortized
v.pop_back();         // O(1)
v[0];                 // O(1) random access
v.insert(v.begin()+1, 10); // O(n) — shifts elements
v.erase(v.begin());        // O(n)
```
Contiguous memory → cache-friendly → almost always the default choice over `list`.

### `deque` — double-ended queue
Like `vector` but supports O(1) push/pop at **both** ends (`push_front`, `push_back`). Not contiguous, slightly more overhead per access than `vector`.

### `list` — doubly linked list
O(1) insert/erase *anywhere* if you already have an iterator to that position, but O(n) to get there (no random access, no `[]`). Rarely the right choice unless you're doing lots of mid-list insertions with iterators already in hand.

### `array` — fixed-size, stack-allocated
`array<int, 5> a;` — like a raw array but with STL container interface (`.size()`, iterators, bounds-checked `.at()`). Size is fixed at compile time.

---

## 2. Associative Containers (Beginner–Intermediate)

### `map` / `set` — ordered, tree-based
```cpp
map<string, int> m;
m["apple"] = 5;           // O(log n)
m.find("apple");           // O(log n)
for (auto& [key, val] : m) // iterates in SORTED key order
    cout << key << " " << val << "\n";
```
Implemented as a **Red-Black Tree** (self-balancing BST) — this is why iteration is sorted and every operation is O(log n).

`set<int> s;` — same idea, just keys, no values. Useful for maintaining a sorted unique collection.

`multimap`/`multiset` — same but allow duplicate keys.

### `unordered_map` / `unordered_set` — hash-table based
```cpp
unordered_map<string, int> um;
um["apple"] = 5; // O(1) average, O(n) worst case
```
Average O(1) operations (vs `map`'s O(log n)) because it's a hash table, not a tree — but no ordering guarantee, and worst-case O(n) if there are many hash collisions. **Default to `unordered_map` for speed unless you need sorted keys or the ordering matters.**

| | map | unordered_map |
|---|---|---|
| Backing structure | Red-Black Tree | Hash Table |
| Order | Sorted by key | No guaranteed order |
| Access | O(log n) | O(1) average, O(n) worst |
| Use when | Need sorted iteration, range queries | Need raw speed, no ordering needed |

---

## 3. Container Adapters (Beginner)

These wrap another container to restrict the interface:

```cpp
stack<int> st;      // LIFO — push, pop, top — default backing: deque
st.push(1); st.push(2);
st.top();  // 2
st.pop();

queue<int> q;        // FIFO — push, pop, front, back
q.push(1); q.push(2);
q.front(); // 1

priority_queue<int> pq;  // max-heap by default
pq.push(5); pq.push(1); pq.push(10);
pq.top();  // 10

// Min-heap:
priority_queue<int, vector<int>, greater<int>> minHeap;
```
`priority_queue` is the STL's binary heap — `push`/`pop` are O(log n), `top` is O(1). This is what you reach for instead of hand-rolling a heap in Dijkstra's algorithm or "top K elements" problems.

---

## 4. Iterators (Intermediate)

An iterator is a generalized pointer that lets algorithms work uniformly across different container types.

```cpp
vector<int> v = {1,2,3};
for (auto it = v.begin(); it != v.end(); ++it) cout << *it;
// range-based for loop is sugar over the same thing:
for (int x : v) cout << x;
```
Iterator categories (increasing power): Input → Output → Forward → Bidirectional → Random Access. `vector`/`array` give random access iterators (`it + 5` works); `list`/`map` give bidirectional only (`it + 5` doesn't compile — must `advance(it, 5)`).

---

## 5. Algorithms (`<algorithm>`) (Intermediate)

```cpp
sort(v.begin(), v.end());                         // O(n log n)
sort(v.begin(), v.end(), greater<int>());          // descending
reverse(v.begin(), v.end());                       // O(n)
auto it = find(v.begin(), v.end(), 5);              // O(n), linear
bool found = binary_search(v.begin(), v.end(), 5);  // O(log n), needs sorted input
int cnt = count(v.begin(), v.end(), 5);             // O(n)
auto mx = max_element(v.begin(), v.end());          // O(n)
int s = accumulate(v.begin(), v.end(), 0);           // O(n), needs <numeric>
```
The advantage over hand-writing loops: these are tested, optimized, and instantly communicate intent to anyone reading the code — including an interviewer.

### `lower_bound` / `upper_bound` (frequently tested)
On a sorted range: `lower_bound(v.begin(), v.end(), x)` returns iterator to first element `>= x`. `upper_bound` returns first element `> x`. Both O(log n). This is how you binary-search for insertion points or count occurrences of a value: `upper_bound - lower_bound`.

---

## 6. Pairs, Tuples & Structured Bindings (Intermediate)

```cpp
pair<int, string> p = {1, "one"};
p.first; p.second;

tuple<int, string, double> t = {1, "one", 1.0};
get<0>(t);

auto [num, word, val] = t; // structured bindings (C++17) — much cleaner
```

---

## 7. Advanced: Complexity Cheat Sheet

| Container | Access | Search | Insert | Delete |
|---|---|---|---|---|
| vector | O(1) | O(n) | O(n) (O(1) at end) | O(n) (O(1) at end) |
| deque | O(1) | O(n) | O(1) at ends | O(1) at ends |
| list | O(n) | O(n) | O(1) with iterator | O(1) with iterator |
| map/set | O(log n) | O(log n) | O(log n) | O(log n) |
| unordered_map/set | O(1) avg | O(1) avg | O(1) avg | O(1) avg |
| priority_queue | O(1) top | — | O(log n) | O(log n) |

**Interview tip**: when asked to justify a container choice, always state the operation you're optimizing for and cite this table — that's what signals real understanding versus memorized syntax.

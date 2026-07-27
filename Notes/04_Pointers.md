# Pointers

Pointers are C++'s most interview-tested topic because they're where "I know the syntax" and "I understand memory" diverge. A pointer is a variable that stores a memory address.

---

## 1. Basics (Beginner)

```cpp
int x = 10;
int* p = &x;   // p holds the address of x
cout << p;      // prints the address itself
cout << *p;      // dereference — prints 10, the value AT that address
*p = 20;          // modifies x through the pointer — x is now 20
```

- `&` (address-of) gets a variable's address.
- `*` (dereference) gets the value stored at an address.
- `*` also *declares* a pointer type (`int* p`) — same symbol, different context, which trips up beginners.

### Null pointers
```cpp
int* p = nullptr;   // C++11, preferred over NULL or 0
if (p == nullptr) cout << "points to nothing";
*p; // undefined behavior — dereferencing a null pointer crashes (segfault)
```
Always check for `nullptr` before dereferencing a pointer that might not point anywhere valid.

---

## 2. Pointers & Arrays (Beginner–Intermediate)

An array name decays into a pointer to its first element in most expressions.

```cpp
int arr[3] = {10, 20, 30};
int* p = arr;        // same as &arr[0]
cout << *(p + 1);     // 20 — pointer arithmetic: p+1 moves by sizeof(int) bytes
cout << p[1];          // 20 — arr[i] is literally syntactic sugar for *(arr + i)
```
This is why array indexing and pointer arithmetic are interchangeable in C++ — internalizing this equivalence is what "understanding pointers" usually means in interviews.

---

## 3. Pointers to Pointers (Intermediate)

```cpp
int x = 5;
int* p = &x;
int** pp = &p;    // pointer to a pointer
cout << **pp;      // 5 — double dereference
```
Common real use: modifying a pointer itself inside a function (e.g. a function that reassigns a `head` pointer for a linked list needs `Node**` or a reference to the pointer).

---

## 4. Pointers vs References (frequently asked)

| | Pointer | Reference |
|---|---|---|
| Can be null | Yes | No — must bind to a real object |
| Can be reassigned | Yes | No — bound once, forever |
| Needs dereference | Yes (`*p`) | No — acts like the original variable |
| Nullable / optional param | Good fit | Bad fit |
| Function param (no reassignment needed) | Works, but verbose | Cleaner: `void f(int& x)` |

Use references when a value must exist and won't be reseated; use pointers when "no value" (`nullptr`) or reassignment is a valid state.

---

## 5. `const` and Pointers (Intermediate)

```cpp
const int* p1;        // pointer to const int — *p1 = 5 is ERROR, p1 = &y is OK
int* const p2 = &x;    // const pointer to int — *p2 = 5 is OK, p2 = &y is ERROR
const int* const p3 = &x; // both locked
```
Read right-to-left from the variable name: `p1` is "a pointer to a const int"; `p2` is "a const pointer to an int."

---

## 6. Dynamic Memory Allocation (Intermediate)

```cpp
int* p = new int(5);      // allocate a single int on the heap
delete p;                  // must free manually — no garbage collector in C++
p = nullptr;                // good practice: avoid a dangling pointer after delete

int* arr = new int[10];     // allocate an array
delete[] arr;                 // MUST use delete[] for arrays, not delete
```
**Common bugs:**
- **Memory leak**: forgetting `delete` — the memory is never returned to the OS until the process exits.
- **Dangling pointer**: using a pointer after its memory has been `delete`d.
- **Double free**: calling `delete` twice on the same pointer — undefined behavior, often a crash.
- **Mismatched new/delete**: using `delete` on memory from `new[]` (or vice versa) — undefined behavior.

This is exactly why modern C++ pushes toward **smart pointers** (see Memory Management notes) instead of raw `new`/`delete`.

---

## 7. Function Pointers (Advanced)

```cpp
int add(int a, int b) { return a + b; }
int (*funcPtr)(int, int) = add;
cout << funcPtr(2, 3); // 5
```
Useful for callback-style APIs (e.g. passing a comparator to `qsort`). In modern C++, `std::function` and lambdas usually replace raw function pointers because they can also capture state.

---

## 8. `void*` and Type Erasure (Advanced)

```cpp
void* generic = &x;             // can point to anything, but can't be dereferenced directly
int* back = static_cast<int*>(generic); // must cast back to a concrete type first
```
Rarely used directly in modern C++ (templates/generics are the type-safe alternative), but shows up in low-level C-interop code and is a classic "explain what this does" interview question.

---

## 9. Common Interview Traps

- **Dangling pointer from returning address of a local variable**:
  ```cpp
  int* bad() {
      int local = 5;
      return &local; // BUG — local is destroyed when the function returns
  }
  ```
- **`sizeof` on a pointer vs an array**: `sizeof(arr)` inside the same scope as the array gives the full array size; `sizeof(ptr)` where `ptr` is `int*` always gives the pointer's size (8 bytes on 64-bit systems), *not* what it points to — a classic gotcha when arrays decay to pointers across a function boundary.

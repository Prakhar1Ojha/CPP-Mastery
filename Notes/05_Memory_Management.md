# Memory Management

C++ gives you manual control over memory — power, but also the most common source of bugs and interview questions. Understanding *where* memory lives and *who's responsible* for freeing it is the core skill here.

---

## 1. Stack vs Heap (Beginner)

| | Stack | Heap |
|---|---|---|
| Allocation | Automatic (`int x;`) | Manual (`new`) |
| Deallocation | Automatic (scope ends) | Manual (`delete`) — or via smart pointers |
| Speed | Very fast (just moves a pointer) | Slower (allocator has to find free space) |
| Size | Limited (~1-8MB typically, causes stack overflow if exceeded) | Large (limited by system RAM) |
| Lifetime | Tied to scope | Until explicitly freed |

```cpp
void f() {
    int a = 5;          // stack — destroyed automatically when f() returns
    int* p = new int(5); // heap — survives after f() returns UNLESS you delete it
} // 'a' is gone here; the heap int is leaked unless deleted before this point
```

Recursion that goes too deep causes a **stack overflow** because every call frame (local variables, return address) is pushed onto the stack, which has a fixed size.

---

## 2. `new`/`delete` (Beginner–Intermediate)

```cpp
int* p = new int(10);
delete p;

int* arr = new int[5];
delete[] arr;   // array form — required, or undefined behavior
```

`new` calls the constructor (for objects) after allocating memory; `delete` calls the destructor before freeing memory. This is the key difference from C's `malloc`/`free`, which just move raw bytes with no constructor/destructor awareness — mixing `malloc` with C++ objects breaks construction/destruction semantics.

---

## 3. Memory Leaks (Intermediate)

A leak happens when heap memory becomes unreachable (no pointer refers to it anymore) *without* being freed first.

```cpp
void leak() {
    int* p = new int(5);
    p = new int(10); // BUG: the first int(5) is now unreachable — leaked forever
    delete p;          // only frees the second allocation
}
```
Leaks don't crash immediately — they accumulate and eventually exhaust memory, which is why they're insidious in long-running programs (servers, games) and why tools like Valgrind exist to catch them.

---

## 4. RAII — Resource Acquisition Is Initialization (Intermediate–Advanced)

The core C++ idiom for automatic resource management: tie a resource's lifetime to an object's lifetime. Acquire the resource in the constructor, release it in the destructor — then the compiler-guaranteed destructor call (when the object goes out of scope) handles cleanup automatically, even if an exception is thrown.

```cpp
class FileHandle {
    FILE* f;
public:
    FileHandle(const char* name) { f = fopen(name, "r"); }
    ~FileHandle() { if (f) fclose(f); } // always runs, even on exception
};
```
Smart pointers (next section) and STL containers are all built on RAII — that's *why* a `vector` frees its internal array automatically when it goes out of scope.

---

## 5. Smart Pointers (Advanced — modern C++ default)

Since C++11, prefer smart pointers over raw `new`/`delete` almost everywhere. They wrap a raw pointer in RAII so you can't forget to free it.

### `unique_ptr` — sole ownership
```cpp
unique_ptr<int> p1 = make_unique<int>(5); // C++14+
// unique_ptr<int> p2 = p1; // ERROR — can't copy
unique_ptr<int> p2 = move(p1);              // OK — ownership transferred, p1 is now null
```
Zero overhead compared to a raw pointer — it's the default choice when only one owner should ever exist.

### `shared_ptr` — shared ownership, reference counted
```cpp
shared_ptr<int> a = make_shared<int>(5);
shared_ptr<int> b = a;    // both now own it, refcount = 2
cout << a.use_count();     // 2
// memory freed automatically when the LAST shared_ptr owning it is destroyed
```
Has overhead (atomic refcount increments/decrements) — use only when multiple owners genuinely need to share the object's lifetime.

### `weak_ptr` — non-owning observer
```cpp
shared_ptr<int> sp = make_shared<int>(5);
weak_ptr<int> wp = sp;  // doesn't increase refcount
if (auto locked = wp.lock()) cout << *locked; // must "lock" to safely access
```
Exists specifically to break **reference cycles**: if object A holds a `shared_ptr` to B and B holds a `shared_ptr` back to A, neither's refcount ever reaches 0 — a leak. Replacing one side with `weak_ptr` breaks the cycle.

| | unique_ptr | shared_ptr | weak_ptr |
|---|---|---|---|
| Ownership | Single | Shared (refcounted) | None |
| Overhead | None | Atomic refcount | Minimal |
| Use when | Default choice | Multiple owners genuinely needed | Breaking cycles, caching |

---

## 6. Rule of Three / Five / Zero (Advanced)

If a class manually manages a resource (raw pointer, file handle), and you define **any** of these, you almost always need to define **all** of them (Rule of Three):
1. Destructor
2. Copy constructor
3. Copy assignment operator

C++11 extends this to Rule of Five, adding move constructor and move assignment operator (for efficient "steal the resource" transfers instead of deep copies).

**Rule of Zero** (the modern preferred approach): don't manage raw resources directly at all — compose your class out of `unique_ptr`/`vector`/other RAII types, and let the compiler-generated special member functions just work, because each member already knows how to clean up after itself.

---

## 7. Common Interview Questions

- What's a memory leak, and how would you detect one? (Valgrind, AddressSanitizer, or just tracking allocation/deallocation pairs)
- `unique_ptr` vs `shared_ptr` vs raw pointer — when would you use each?
- What's a dangling pointer, and how is it different from a memory leak? (Leak = memory never freed; dangling = pointer still points to memory that *has* been freed)
- Explain RAII in your own words with an example outside of smart pointers (e.g. a mutex lock guard).

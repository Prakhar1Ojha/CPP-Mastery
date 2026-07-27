# Templates

Templates are how C++ achieves generic programming: writing code once that works across multiple types, with zero runtime overhead (the compiler generates a separate concrete version for each type actually used — this is called **instantiation**).

---

## 1. Function Templates (Beginner)

```cpp
template <typename T>
T maxVal(T a, T b) {
    return (a > b) ? a : b;
}

maxVal(3, 7);        // T deduced as int
maxVal(3.5, 2.1);     // T deduced as double
maxVal<double>(3, 7.5); // explicit — forces T = double
```
Without templates you'd need a separate `maxInt`, `maxDouble`, `maxString`... Templates let the compiler generate exactly the versions you actually call, at compile time, with no runtime type-checking cost (unlike, say, Java generics with type erasure — C++ templates are fully "real" per instantiation).

---

## 2. Class Templates (Beginner–Intermediate)

```cpp
template <typename T>
class Box {
private:
    T value;
public:
    Box(T v) : value(v) {}
    T get() { return value; }
};

Box<int> b1(5);
Box<string> b2("hello");
```
This is exactly how `vector<T>`, `map<K,V>`, etc. are implemented internally — the STL is built entirely on templates.

### Multiple type parameters
```cpp
template <typename K, typename V>
class Pair {
    K key; V value;
public:
    Pair(K k, V v) : key(k), value(v) {}
};
Pair<string, int> p("age", 21);
```

---

## 3. Non-Type Template Parameters (Intermediate)

Templates can also take *values*, not just types — this is how `array<int, 5>` gets a compile-time-fixed size.

```cpp
template <typename T, int Size>
class FixedArray {
    T data[Size];
public:
    int length() { return Size; }
};
FixedArray<int, 10> fa; // Size = 10, baked in at compile time
```

---

## 4. Template Specialization (Intermediate–Advanced)

Sometimes the generic implementation isn't right for a specific type — you can override it.

```cpp
template <typename T>
class Printer {
public:
    void print(T val) { cout << val << "\n"; }
};

// Full specialization for bool — print "true"/"false" instead of 1/0
template <>
class Printer<bool> {
public:
    void print(bool val) { cout << (val ? "true" : "false") << "\n"; }
};
```

**Partial specialization** (for class templates only, not function templates) specializes for a *category* of types, e.g. all pointer types:
```cpp
template <typename T>
class Printer<T*> {
public:
    void print(T* val) { cout << "pointer to: " << *val << "\n"; }
};
```

---

## 5. Variadic Templates (Advanced)

Templates that accept an arbitrary number of arguments — the mechanism behind `make_unique`, `emplace_back`, `std::tuple`, etc.

```cpp
template <typename T>
void print(T val) { cout << val << " "; }

template <typename T, typename... Args>
void print(T first, Args... rest) {
    cout << first << " ";
    print(rest...); // recursively unpacks the parameter pack
}

print(1, 2.5, "three", 'x'); // works for any number/mix of types
```
`Args...` is a **parameter pack**. Understanding this is the foundation for reading STL/library source code and is a strong-signal advanced-interview topic.

---

## 6. Templates + STL (Advanced)

Every STL container and algorithm is a template. Writing your own generic `Stack<T>` before you've internalized how `vector<T>`/`stack<T>` work is a common (and useful) exercise — it demystifies "how does the STL even work" for good.

```cpp
template <typename T>
class Stack {
    vector<T> data;
public:
    void push(T val) { data.push_back(val); }
    void pop() { data.pop_back(); }
    T top() { return data.back(); }
    bool empty() { return data.empty(); }
};
```

---

## 7. Common Pitfalls & Interview Notes

- **Templates are compiled per translation unit**: this is why template definitions almost always live in header files (`.h`), not `.cpp` files — the compiler needs to see the full definition everywhere the template is instantiated.
- **Compile errors in templates are notoriously verbose** — a single misuse can produce pages of error output because the error surfaces at instantiation, not definition.
- Templates give **zero-cost abstraction**: unlike runtime polymorphism (virtual functions), there's no vtable lookup — the "generic-ness" disappears entirely after compilation. This is a key distinction to articulate in interviews: templates are compile-time polymorphism, virtual functions are runtime polymorphism.

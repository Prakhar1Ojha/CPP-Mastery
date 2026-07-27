# Exception Handling

Exceptions let you separate "how to detect an error" from "how to handle it" — the code that hits a problem doesn't need to know what the right response is; it just signals upward until something that *does* know catches it.

---

## 1. Basics: try / catch / throw (Beginner)

```cpp
try {
    int a = 10, b = 0;
    if (b == 0) throw runtime_error("Division by zero");
    cout << a / b;
} catch (const runtime_error& e) {
    cout << "Caught: " << e.what() << "\n";
}
```
- `throw` raises an exception — control immediately leaves the current function (unwinding the stack) looking for a matching `catch`.
- `catch (const T& e)` catches exceptions of type `T` (or anything derived from `T`) — always catch by `const reference` to avoid slicing and unnecessary copies.

---

## 2. Standard Exception Hierarchy (Beginner–Intermediate)

`<stdexcept>` provides a hierarchy rooted at `std::exception`:

```
exception
├── logic_error
│   ├── invalid_argument
│   ├── out_of_range
│   └── length_error
└── runtime_error
    ├── overflow_error
    ├── underflow_error
    └── range_error
```

```cpp
vector<int> v = {1, 2, 3};
try {
    v.at(10); // .at() throws out_of_range; v[10] would be undefined behavior instead
} catch (const out_of_range& e) {
    cout << e.what() << "\n";
}
```
Key distinction worth knowing cold: `logic_error` types represent bugs that should've been prevented by the caller (bad arguments); `runtime_error` types represent conditions only detectable while the program runs.

---

## 3. Catching Multiple Types (Intermediate)

```cpp
try {
    // ...
} catch (const invalid_argument& e) {
    cout << "Invalid argument: " << e.what() << "\n";
} catch (const out_of_range& e) {
    cout << "Out of range: " << e.what() << "\n";
} catch (const exception& e) {
    cout << "Some other standard exception: " << e.what() << "\n"; // catch-all base class
} catch (...) {
    cout << "Unknown exception\n"; // truly catches anything, even non-std types
}
```
Order matters — catch blocks are checked top to bottom, so more specific types must come before more general ones (a `catch (const exception&)` before `catch (const out_of_range&)` would swallow it first and the specific handler would be unreachable).

---

## 4. Custom Exceptions (Intermediate)

```cpp
class InsufficientFundsException : public runtime_error {
public:
    InsufficientFundsException(double shortfall)
        : runtime_error("Insufficient funds, short by " + to_string(shortfall)) {}
};

void withdraw(double balance, double amount) {
    if (amount > balance) throw InsufficientFundsException(amount - balance);
}
```
Deriving from `std::exception` (or a subclass like `runtime_error`) means callers who don't know about your specific type can still catch it generically via `catch (const exception& e)` and call `.what()`.

---

## 5. Stack Unwinding & RAII (Intermediate–Advanced)

When an exception is thrown, the stack **unwinds**: every local object between the throw site and the matching catch has its destructor called, in reverse order of construction. This is *why* RAII matters so much in C++ — a `unique_ptr` or a `lock_guard` on the stack will still clean up correctly even if an exception blows past it, because its destructor runs during unwinding regardless.

```cpp
void risky() {
    unique_ptr<int> p = make_unique<int>(5);
    throw runtime_error("oops");
    // p's destructor STILL runs during unwinding — no leak
}
```
Without RAII (raw `new`/`delete`), an exception between `new` and `delete` would leak — this is the single biggest practical reason modern C++ avoids manual memory management.

---

## 6. `noexcept` (Advanced)

```cpp
void f() noexcept { /* promises not to throw */ }
```
Marking a function `noexcept` lets the compiler skip generating stack-unwinding code for it (a performance win) and communicates intent. **If a `noexcept` function throws anyway, `std::terminate()` is called immediately** — no unwinding, no catching, the program just aborts. Move constructors are commonly marked `noexcept` because STL containers (like `vector`) check this: they'll only use the (fast) move constructor during a reallocation if it's guaranteed not to throw halfway through, otherwise they fall back to the (slower but safe) copy constructor.

---

## 7. Exception Safety Guarantees (Advanced — strong interview signal)

| Guarantee | Meaning |
|---|---|
| No-throw | Operation is guaranteed to never throw |
| Strong | If it throws, program state is unchanged (rolled back, as if never called) |
| Basic | If it throws, no resources leak, but state may have partially changed |
| No guarantee | Anything could happen — avoid this |

Aiming for the **strong guarantee** where possible (e.g. via copy-and-swap idiom) is considered good C++ practice — being able to name and explain these levels is a solid interview differentiator beyond just "know try/catch."

---

## 8. Costs & When Not to Use Exceptions (Advanced)

Exceptions have runtime cost *only when thrown* (the happy path is essentially free in modern implementations — "zero-cost exceptions"), but throwing itself is relatively expensive (stack unwinding, RTTI lookups) — which is why exceptions are for **exceptional, rare** conditions, not routine control flow. In hot loops or performance-critical/embedded code, error codes or `std::optional`/`std::expected` (C++23) are often preferred over exceptions for expected-to-fail operations.

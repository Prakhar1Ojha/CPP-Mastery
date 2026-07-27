# Object-Oriented Programming (OOP) in C++

## Why OOP?

Procedural code (just functions + global data) gets unmanageable past a certain size — data and the logic that touches it live far apart, and anything can mutate anything. OOP bundles data with the functions that operate on it, and controls who's allowed to touch what. The four pillars: **Encapsulation, Abstraction, Inheritance, Polymorphism.**

---

## 1. Classes & Objects (Beginner)

A **class** is a blueprint. An **object** is an instance built from that blueprint — its own copy of the member variables, sharing the class's methods.

```cpp
class Car {
private:
    string model;
    int speed;
public:
    Car(string m, int s) : model(m), speed(s) {} // constructor
    void accelerate(int by) { speed += by; }
    void display() { cout << model << " at " << speed << " km/h\n"; }
};
```

`Car c1("Civic", 0);` — `c1` is an object; `Car` is the class.

### Constructors & Destructors
- **Default constructor**: no args, compiler auto-generates one if you define none.
- **Parameterized constructor**: takes args to initialize members (as above).
- **Copy constructor**: `Car(const Car& other)` — called when an object is copied. If you don't write one, the compiler generates a shallow copy — dangerous if the class owns a raw pointer (two objects would point to the same memory, causing a double-free on destruction).
- **Destructor**: `~Car()` — runs automatically when an object goes out of scope. Critical for releasing manually-allocated memory (`delete`), closing files, etc.

**Initializer list** (`: model(m), speed(s)`) is preferred over assigning inside the constructor body — it initializes members directly instead of default-constructing then reassigning, and it's *required* for `const` members and reference members.

---

## 2. Encapsulation (Beginner)

Keeping data `private` and exposing controlled access via `public` getters/setters. Prevents external code from putting an object into an invalid state.

```cpp
class BankAccount {
private:
    double balance;
public:
    void deposit(double amt) {
        if (amt > 0) balance += amt; // validation lives with the data
    }
    double getBalance() const { return balance; }
};
```

Without encapsulation, anyone could do `account.balance = -9999;` directly. `const` on `getBalance()` means the method promises not to modify the object — lets you call it on `const` references too.

---

## 3. Abstraction (Beginner–Intermediate)

Exposing *what* an object does, hiding *how*. A `Stack` class exposes `push()`/`pop()`; the caller doesn't need to know whether it's backed by an array or a linked list internally. Abstract classes (below) are the formal mechanism for this in C++.

---

## 4. Inheritance (Intermediate)

A derived class reuses and extends a base class.

```cpp
class Animal {
public:
    void eat() { cout << "eating\n"; }
};

class Dog : public Animal {
public:
    void bark() { cout << "woof\n"; }
};
// Dog d; d.eat(); d.bark(); — Dog gets eat() for free
```

### Access specifiers with inheritance
| Base member | `public` inheritance | `protected` inheritance | `private` inheritance |
|---|---|---|---|
| `public`    | public in derived    | protected in derived    | private in derived |
| `protected` | protected            | protected                | private |
| `private`   | not accessible in derived | not accessible      | not accessible |

`public` inheritance ("is-a" relationship) is what you use ~95% of the time.

### The Diamond Problem
If `B` and `C` both inherit from `A`, and `D` inherits from both `B` and `C`, `D` ends up with two copies of `A`'s members — ambiguous. Fixed with **virtual inheritance**: `class B : virtual public A`. Rare in practice but a common interview question.

---

## 5. Polymorphism (Intermediate–Advanced)

**Compile-time (static) polymorphism**: function overloading, operator overloading — resolved at compile time based on argument types.

```cpp
int add(int a, int b) { return a + b; }
double add(double a, double b) { return a + b; } // overload
```

**Run-time (dynamic) polymorphism**: `virtual` functions — resolved at runtime based on the actual object type, not the pointer/reference type.

```cpp
class Shape {
public:
    virtual double area() { return 0; }       // virtual — enables override
    virtual ~Shape() {}                        // virtual destructor — important!
};
class Circle : public Shape {
    double r;
public:
    Circle(double r) : r(r) {}
    double area() override { return 3.14159 * r * r; }
};

Shape* s = new Circle(5);
cout << s->area(); // calls Circle::area() even though s is a Shape*
delete s;           // virtual destructor ensures Circle's destructor runs too
```

**Why the virtual destructor matters**: without it, `delete s` (a `Shape*` pointing to a `Circle`) only calls `~Shape()`, leaking any resources `Circle` allocated. Rule of thumb: if a class has *any* virtual function, give it a virtual destructor.

### How it works internally (vtable)
Each class with virtual functions gets a **vtable** (virtual function table) — an array of function pointers. Each object of that class carries a hidden **vptr** pointing to its class's vtable. A virtual call is resolved by looking up the vptr at runtime instead of binding the call at compile time. This indirection is why virtual calls are marginally slower than non-virtual ones (and why virtual functions can't be inlined).

### Pure virtual functions & abstract classes
```cpp
class Shape {
public:
    virtual double area() = 0; // pure virtual — no implementation
};
// Shape s; // ERROR — can't instantiate an abstract class
```
Any class with at least one pure virtual function is abstract — it exists only to be inherited from, forcing derived classes to implement `area()`.

---

## 6. Friend Functions (Intermediate)

A `friend` function/class can access another class's `private`/`protected` members, even though it isn't a member itself. Used sparingly — mainly for operator overloading (e.g. `operator<<` for printing) where the left operand isn't the class itself.

```cpp
class Point {
    int x, y;
    friend ostream& operator<<(ostream& os, const Point& p);
};
ostream& operator<<(ostream& os, const Point& p) {
    return os << "(" << p.x << ", " << p.y << ")"; // accesses private x, y
}
```

---

## 7. Advanced: Overloading vs Overriding (common interview trip-up)

| | Overloading | Overriding |
|---|---|---|
| Same class or derived? | Same class | Base + derived |
| Signature | Must differ (params) | Must match exactly |
| Resolved | Compile time | Runtime (needs `virtual`) |
| Purpose | Multiple behaviors, same name | Redefine base behavior |

---

## 8. Composition vs Inheritance

"Has-a" (composition) is often preferable to "is-a" (inheritance) — a `Car` *has an* `Engine`, it isn't *a kind of* `Engine`. Composition is more flexible (can swap engines) and avoids deep, fragile inheritance hierarchies. Modern C++ guidance: "prefer composition over inheritance" unless there's a genuine is-a relationship with shared polymorphic behavior.

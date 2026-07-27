/*
================================================================================
                    POLYMORPHISM IN C++ - COMPLETE GUIDE
              From Beginner to Advanced Level
================================================================================

Polymorphism means "many forms". It allows objects of different types to be
treated through a common interface, and the correct method is called based
on the actual object type at runtime (or compile time).

Two main types in C++:

1. Compile-time Polymorphism (Static / Early Binding)
   - Function Overloading
   - Operator Overloading
   - Templates

2. Runtime Polymorphism (Dynamic / Late Binding)
   - Virtual Functions
   - Pure Virtual Functions / Abstract Classes
   - Function Overriding

================================================================================
1. BEGINNER LEVEL - Function Overloading & Basic Operator Overloading
================================================================================
*/

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// -----------------------------------------------------------------------------
// Example 1: Function Overloading (Compile-time Polymorphism)
// -----------------------------------------------------------------------------
class Calculator {
public:
    // Same function name, different parameters
    int add(int a, int b) {
        cout << "Adding two integers: ";
        return a + b;
    }

    double add(double a, double b) {
        cout << "Adding two doubles: ";
        return a + b;
    }

    int add(int a, int b, int c) {
        cout << "Adding three integers: ";
        return a + b + c;
    }

    string add(string a, string b) {
        cout << "Concatenating strings: ";
        return a + b;
    }
};

// -----------------------------------------------------------------------------
// Example 2: Basic Operator Overloading
// -----------------------------------------------------------------------------
class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // Overload + operator
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    // Overload - operator
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    // Overload << for easy printing (friend function)
    friend ostream& operator<<(ostream& os, const Complex& c) {
        os << c.real;
        if (c.imag >= 0) os << " + " << c.imag << "i";
        else os << " - " << -c.imag << "i";
        return os;
    }

    // Overload == operator
    bool operator==(const Complex& other) const {
        return (real == other.real) && (imag == other.imag);
    }
};

/*
================================================================================
2. INTERMEDIATE LEVEL - Runtime Polymorphism with Virtual Functions
================================================================================
*/

// -----------------------------------------------------------------------------
// Example 3: Virtual Functions - The Heart of Runtime Polymorphism
// -----------------------------------------------------------------------------
class Animal {
public:
    // Virtual function - enables dynamic binding
    virtual void makeSound() {
        cout << "Some generic animal sound" << endl;
    }

    virtual void move() {
        cout << "Animal moves" << endl;
    }

    // Virtual destructor is CRITICAL for proper cleanup
    virtual ~Animal() {
        cout << "[Animal] Destructor" << endl;
    }
};

class Dog : public Animal {
public:
    void makeSound() override {
        cout << "Woof! Woof!" << endl;
    }

    void move() override {
        cout << "Dog runs on four legs" << endl;
    }

    ~Dog() {
        cout << "[Dog] Destructor" << endl;
    }
};

class Cat : public Animal {
public:
    void makeSound() override {
        cout << "Meow!" << endl;
    }

    void move() override {
        cout << "Cat walks gracefully" << endl;
    }

    ~Cat() {
        cout << "[Cat] Destructor" << endl;
    }
};

class Bird : public Animal {
public:
    void makeSound() override {
        cout << "Chirp! Chirp!" << endl;
    }

    void move() override {
        cout << "Bird flies in the sky" << endl;
    }

    ~Bird() {
        cout << "[Bird] Destructor" << endl;
    }
};

// -----------------------------------------------------------------------------
// Example 4: Without virtual vs With virtual (important demonstration)
// -----------------------------------------------------------------------------
class BaseNoVirtual {
public:
    void show() {
        cout << "BaseNoVirtual::show()" << endl;
    }
};

class DerivedNoVirtual : public BaseNoVirtual {
public:
    void show() {
        cout << "DerivedNoVirtual::show()" << endl;
    }
};

class BaseWithVirtual {
public:
    virtual void show() {
        cout << "BaseWithVirtual::show()" << endl;
    }
    virtual ~BaseWithVirtual() {}
};

class DerivedWithVirtual : public BaseWithVirtual {
public:
    void show() override {
        cout << "DerivedWithVirtual::show()" << endl;
    }
};

/*
================================================================================
3. ADVANCED LEVEL - Pure Virtual Functions, Abstract Classes,
                    Virtual Function Table (vtable), final, covariant returns
================================================================================
*/

// -----------------------------------------------------------------------------
// Example 5: Abstract Class & Pure Virtual Functions
// -----------------------------------------------------------------------------
/*
A class is abstract if it has at least one pure virtual function.
You cannot create objects of an abstract class.
It serves as an interface / contract for derived classes.
*/

class Shape {                       // Abstract base class
public:
    // Pure virtual functions - must be overridden
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void draw() const = 0;

    // Non-pure virtual function (optional to override)
    virtual void info() const {
        cout << "This is a shape." << endl;
    }

    virtual ~Shape() {}
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    double area() const override {
        return 3.1415926535 * radius * radius;
    }

    double perimeter() const override {
        return 2 * 3.1415926535 * radius;
    }

    void draw() const override {
        cout << "Drawing a Circle with radius " << radius << endl;
    }

    void info() const override {
        cout << "Circle - Radius: " << radius << endl;
    }
};

class Rectangle : public Shape {
private:
    double length, width;

public:
    Rectangle(double l, double w) : length(l), width(w) {}

    double area() const override {
        return length * width;
    }

    double perimeter() const override {
        return 2 * (length + width);
    }

    void draw() const override {
        cout << "Drawing a Rectangle " << length << " x " << width << endl;
    }
};

class Triangle : public Shape {
private:
    double a, b, c;   // three sides

public:
    Triangle(double x, double y, double z) : a(x), b(y), c(z) {}

    double area() const override {
        // Heron's formula
        double s = (a + b + c) / 2.0;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }

    double perimeter() const override {
        return a + b + c;
    }

    void draw() const override {
        cout << "Drawing a Triangle with sides " 
             << a << ", " << b << ", " << c << endl;
    }
};

// -----------------------------------------------------------------------------
// Example 6: More Operator Overloading (Advanced)
// -----------------------------------------------------------------------------
class Vector2D {
private:
    double x, y;

public:
    Vector2D(double x = 0, double y = 0) : x(x), y(y) {}

    // Arithmetic operators
    Vector2D operator+(const Vector2D& v) const {
        return Vector2D(x + v.x, y + v.y);
    }

    Vector2D operator-(const Vector2D& v) const {
        return Vector2D(x - v.x, y - v.y);
    }

    Vector2D operator*(double scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }

    // Unary operators
    Vector2D operator-() const {
        return Vector2D(-x, -y);
    }

    // Compound assignment
    Vector2D& operator+=(const Vector2D& v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    // Comparison
    bool operator==(const Vector2D& v) const {
        return (x == v.x) && (y == v.y);
    }

    bool operator!=(const Vector2D& v) const {
        return !(*this == v);
    }

    // Subscript operator
    double& operator[](int index) {
        if (index == 0) return x;
        return y;
    }

    const double& operator[](int index) const {
        if (index == 0) return x;
        return y;
    }

    // Function call operator (makes object callable)
    double operator()() const {
        return sqrt(x * x + y * y);   // magnitude
    }

    friend ostream& operator<<(ostream& os, const Vector2D& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }

    // Prefix ++
    Vector2D& operator++() {
        ++x; ++y;
        return *this;
    }

    // Postfix ++
    Vector2D operator++(int) {
        Vector2D temp = *this;
        ++x; ++y;
        return temp;
    }
};

// -----------------------------------------------------------------------------
// Example 7: Understanding vtable (conceptual)
// -----------------------------------------------------------------------------
/*
When a class has virtual functions, the compiler creates a Virtual Table (vtable).

Each object of such a class contains a hidden pointer (vptr) that points to
the vtable of its class.

At runtime, the call is resolved through:
    object → vptr → vtable → correct function address

This is why virtual functions have a small runtime overhead.

You can check with:
    sizeof(ClassWithVirtual) > sizeof(ClassWithoutVirtual)
*/

/*
================================================================================
4. DEMONSTRATION
================================================================================
*/

void demonstratePolymorphism(Animal* animal) {
    // Runtime decision: which makeSound() to call?
    animal->makeSound();
    animal->move();
}

int main() {
    cout << "========== 1. FUNCTION OVERLOADING ==========\n";
    Calculator calc;
    cout << calc.add(5, 3) << endl;
    cout << calc.add(2.5, 3.7) << endl;
    cout << calc.add(1, 2, 3) << endl;
    cout << calc.add("Hello, ", "World!") << endl;

    cout << "\n========== 2. OPERATOR OVERLOADING (Complex) ==========\n";
    Complex c1(3, 4);
    Complex c2(1, -2);
    Complex c3 = c1 + c2;
    Complex c4 = c1 - c2;

    cout << "c1 = " << c1 << endl;
    cout << "c2 = " << c2 << endl;
    cout << "c1 + c2 = " << c3 << endl;
    cout << "c1 - c2 = " << c4 << endl;
    cout << "c1 == c2? " << (c1 == c2 ? "Yes" : "No") << endl;

    cout << "\n========== 3. RUNTIME POLYMORPHISM (Virtual) ==========\n";
    {
        Animal* animals[3];
        animals[0] = new Dog();
        animals[1] = new Cat();
        animals[2] = new Bird();

        for (int i = 0; i < 3; i++) {
            cout << "Animal " << i + 1 << ": ";
            demonstratePolymorphism(animals[i]);
        }

        // Proper cleanup thanks to virtual destructor
        for (int i = 0; i < 3; i++) {
            delete animals[i];
        }
    }

    cout << "\n========== 4. WITHOUT vs WITH VIRTUAL ==========\n";
    DerivedNoVirtual dnv;
    BaseNoVirtual* ptr1 = &dnv;
    ptr1->show();   // Calls Base version (static binding)

    DerivedWithVirtual dwv;
    BaseWithVirtual* ptr2 = &dwv;
    ptr2->show();   // Calls Derived version (dynamic binding)

    cout << "\n========== 5. ABSTRACT CLASS / PURE VIRTUAL ==========\n";
    // Shape s;  // ERROR: cannot instantiate abstract class

    Shape* shapes[3];
    shapes[0] = new Circle(5.0);
    shapes[1] = new Rectangle(4.0, 6.0);
    shapes[2] = new Triangle(3.0, 4.0, 5.0);

    for (int i = 0; i < 3; i++) {
        shapes[i]->draw();
        shapes[i]->info();
        cout << "  Area: " << shapes[i]->area() 
             << ", Perimeter: " << shapes[i]->perimeter() << "\n\n";
    }

    for (int i = 0; i < 3; i++) {
        delete shapes[i];
    }

    cout << "========== 6. ADVANCED OPERATOR OVERLOADING ==========\n";
    Vector2D v1(3, 4);
    Vector2D v2(1, 2);

    cout << "v1 = " << v1 << endl;
    cout << "v2 = " << v2 << endl;
    cout << "v1 + v2 = " << (v1 + v2) << endl;
    cout << "v1 * 2 = " << (v1 * 2) << endl;
    cout << "Magnitude of v1: " << v1() << endl;   // function call operator

    Vector2D v3 = v1;
    cout << "Before ++: " << v3 << endl;
    cout << "Prefix ++: " << ++v3 << endl;
    cout << "Postfix ++: " << v3++ << endl;
    cout << "After postfix: " << v3 << endl;

    cout << "v1[0] = " << v1[0] << ", v1[1] = " << v1[1] << endl;

    cout << "\n========== PROGRAM END ==========\n";
    return 0;
}

/*
================================================================================
SUMMARY - KEY TAKEAWAYS
================================================================================

Compile-time Polymorphism:
✓ Function Overloading
✓ Operator Overloading
✓ Templates
→ Resolved at compile time → Faster, no runtime overhead

Runtime Polymorphism:
✓ Virtual Functions
✓ Pure Virtual Functions (Abstract Classes)
→ Resolved at runtime via vtable → Slightly slower, very flexible

Critical Rules:
1. Always make destructor virtual in base classes intended for inheritance
2. Use 'override' keyword (C++11) for safety
3. Use 'final' to prevent further overriding
4. Prefer pure virtual functions for interfaces
5. Never call virtual functions in constructors/destructors (object not fully formed)

When to use what:
- Overloading → Same operation, different types/number of arguments
- Virtual functions → Same interface, different behavior based on object type
- Abstract class → Force derived classes to implement certain methods

================================================================================
*/
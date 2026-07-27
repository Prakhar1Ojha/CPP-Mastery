/*
================================================================================
                    INHERITANCE IN C++ - COMPLETE GUIDE
              From Beginner to Advanced Level
================================================================================

Inheritance is one of the four pillars of Object-Oriented Programming.
It allows a class (derived/child) to acquire properties and behaviors
of another class (base/parent).

Benefits:
- Code Reusability
- Hierarchical classification
- Extensibility
- Polymorphism support

Terminology:
- Base Class / Parent Class / Super Class
- Derived Class / Child Class / Sub Class

Access Specifiers in Inheritance:
┌─────────────────┬───────────┬─────────────┬──────────┐
│ Access in Base  │  public   │  protected  │ private  │
├─────────────────┼───────────┼─────────────┼──────────┤
│ public inherit  │  public   │  protected  │  hidden  │
│ protected inherit│ protected│  protected  │  hidden  │
│ private inherit │  private  │  private    │  hidden  │
└─────────────────┴───────────┴─────────────┴──────────┘

================================================================================
1. BEGINNER LEVEL - Single Inheritance & Access Specifiers
================================================================================
*/

#include <iostream>
#include <string>
using namespace std;

// -----------------------------------------------------------------------------
// Example 1: Basic Single Inheritance (public)
// -----------------------------------------------------------------------------
class Animal {
protected:                  // accessible in derived classes
    string name;
    int age;

public:
    Animal(string n = "Unknown", int a = 0) : name(n), age(a) {
        cout << "[Animal] Constructor called for " << name << endl;
    }

    void eat() {
        cout << name << " is eating." << endl;
    }

    void sleep() {
        cout << name << " is sleeping." << endl;
    }

    void displayInfo() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }

    ~Animal() {
        cout << "[Animal] Destructor called for " << name << endl;
    }
};

// Derived class
class Dog : public Animal {     // public inheritance
private:
    string breed;

public:
    Dog(string n, int a, string b) : Animal(n, a), breed(b) {
        cout << "[Dog] Constructor called. Breed: " << breed << endl;
    }

    void bark() {
        cout << name << " says: Woof! Woof!" << endl;
    }

    void displayDog() {
        displayInfo();          // inherited method
        cout << "Breed: " << breed << endl;
    }

    ~Dog() {
        cout << "[Dog] Destructor called." << endl;
    }
};

/*
================================================================================
2. INTERMEDIATE LEVEL - Types of Inheritance, Constructor/Destructor Order,
                        Method Overriding, Protected Members
================================================================================
*/

// -----------------------------------------------------------------------------
// Example 2: Multilevel Inheritance
// -----------------------------------------------------------------------------
class Vehicle {
protected:
    string brand;
    int year;

public:
    Vehicle(string b, int y) : brand(b), year(y) {
        cout << "[Vehicle] Created: " << brand << " (" << year << ")" << endl;
    }

    void start() {
        cout << brand << " engine started." << endl;
    }

    ~Vehicle() {
        cout << "[Vehicle] Destroyed." << endl;
    }
};

class Car : public Vehicle {
protected:
    int numDoors;

public:
    Car(string b, int y, int doors) : Vehicle(b, y), numDoors(doors) {
        cout << "[Car] Created with " << numDoors << " doors." << endl;
    }

    void openTrunk() {
        cout << "Trunk of " << brand << " opened." << endl;
    }

    ~Car() {
        cout << "[Car] Destroyed." << endl;
    }
};

class ElectricCar : public Car {
private:
    int batteryCapacity;    // in kWh

public:
    ElectricCar(string b, int y, int doors, int battery)
        : Car(b, y, doors), batteryCapacity(battery) {
        cout << "[ElectricCar] Battery: " << batteryCapacity << " kWh" << endl;
    }

    void charge() {
        cout << brand << " is charging..." << endl;
    }

    void display() {
        cout << "\n--- Electric Car Info ---\n";
        cout << "Brand: " << brand << "\nYear: " << year
             << "\nDoors: " << numDoors
             << "\nBattery: " << batteryCapacity << " kWh\n";
    }

    ~ElectricCar() {
        cout << "[ElectricCar] Destroyed." << endl;
    }
};

// -----------------------------------------------------------------------------
// Example 3: Hierarchical Inheritance
// -----------------------------------------------------------------------------
class Shape {
protected:
    string color;

public:
    Shape(string c = "Black") : color(c) {}

    virtual double area() { return 0; }   // will be overridden
    virtual void draw() {
        cout << "Drawing a shape of color " << color << endl;
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r, string c = "Red") : Shape(c), radius(r) {}

    double area() override {
        return 3.14159 * radius * radius;
    }

    void draw() override {
        cout << "Drawing Circle (r=" << radius << ") in " << color << endl;
    }
};

class Rectangle : public Shape {
private:
    double length, width;

public:
    Rectangle(double l, double w, string c = "Blue") 
        : Shape(c), length(l), width(w) {}

    double area() override {
        return length * width;
    }

    void draw() override {
        cout << "Drawing Rectangle (" << length << "x" << width 
             << ") in " << color << endl;
    }
};

// -----------------------------------------------------------------------------
// Example 4: Multiple Inheritance
// -----------------------------------------------------------------------------
class Flyer {
public:
    void fly() {
        cout << "Flying high in the sky!" << endl;
    }
};

class Swimmer {
public:
    void swim() {
        cout << "Swimming in the water!" << endl;
    }
};

// Multiple inheritance
class Duck : public Flyer, public Swimmer {
private:
    string name;

public:
    Duck(string n) : name(n) {}

    void quack() {
        cout << name << " says: Quack! Quack!" << endl;
    }

    void showAbilities() {
        cout << name << " can: ";
        fly();
        swim();
        quack();
    }
};

/*
================================================================================
3. ADVANCED LEVEL - Diamond Problem, Virtual Inheritance,
                    Function Overriding vs Hiding, final, override
================================================================================
*/

// -----------------------------------------------------------------------------
// Example 5: Diamond Problem & Virtual Inheritance
// -----------------------------------------------------------------------------
/*
        Person
       /      \
   Student    Employee
       \      /
        Manager     <--- Diamond Problem (two copies of Person)

Solution: Virtual Inheritance
*/

class Person {
protected:
    string name;
    int age;

public:
    Person(string n = "Unknown", int a = 0) : name(n), age(a) {
        cout << "[Person] Constructor: " << name << endl;
    }

    void introduce() {
        cout << "I am " << name << ", " << age << " years old." << endl;
    }

    virtual ~Person() {
        cout << "[Person] Destructor: " << name << endl;
    }
};

// Virtual inheritance
class Student : virtual public Person {
protected:
    string university;
    float gpa;

public:
    Student(string n, int a, string uni, float g)
        : Person(n, a), university(uni), gpa(g) {
        cout << "[Student] Constructor" << endl;
    }

    void study() {
        cout << name << " is studying at " << university << endl;
    }
};

class Employee : virtual public Person {
protected:
    string company;
    double salary;

public:
    Employee(string n, int a, string comp, double sal)
        : Person(n, a), company(comp), salary(sal) {
        cout << "[Employee] Constructor" << endl;
    }

    void work() {
        cout << name << " works at " << company 
             << " earning $" << salary << endl;
    }
};

// Manager inherits from both - only ONE Person subobject due to virtual
class Manager : public Student, public Employee {
private:
    string department;

public:
    Manager(string n, int a, string uni, float g, 
            string comp, double sal, string dept)
        : Person(n, a),                    // must initialize virtual base
          Student(n, a, uni, g),
          Employee(n, a, comp, sal),
          department(dept) {
        cout << "[Manager] Constructor - Department: " << department << endl;
    }

    void manage() {
        cout << "\n--- Manager Profile ---\n";
        introduce();        // unambiguous because of virtual inheritance
        study();
        work();
        cout << "Manages department: " << department << endl;
    }

    ~Manager() {
        cout << "[Manager] Destructor" << endl;
    }
};

// -----------------------------------------------------------------------------
// Example 6: Method Hiding vs Overriding + final
// -----------------------------------------------------------------------------
class Base {
public:
    virtual void show() {
        cout << "Base::show()" << endl;
    }

    void display() {        // non-virtual
        cout << "Base::display()" << endl;
    }

    // final method - cannot be overridden further
    virtual void critical() final {
        cout << "Base::critical() - cannot be overridden" << endl;
    }
};

class Derived : public Base {
public:
    // Proper overriding (virtual + override keyword recommended)
    void show() override {
        cout << "Derived::show()" << endl;
    }

    // This HIDES Base::display() (because Base::display is not virtual)
    void display() {
        cout << "Derived::display() - this hides Base version" << endl;
    }

    // void critical() override { }  // ERROR: cannot override final method
};

// A class marked final cannot be inherited from
class FinalClass final {
public:
    void hello() {
        cout << "I am a final class." << endl;
    }
};

// class CannotInherit : public FinalClass { };  // ERROR

/*
================================================================================
4. IMPORTANT CONCEPTS SUMMARY
================================================================================

Constructor Calling Order:
Base → Intermediate → Derived

Destructor Calling Order (reverse):
Derived → Intermediate → Base

When to use which inheritance:
- public    : "is-a" relationship (most common)
- protected : rare, for further derivation control
- private   : "implemented-in-terms-of" (composition alternative)

Virtual Inheritance:
- Use when diamond problem occurs
- Virtual base class is initialized by the most derived class

Best Practices:
1. Prefer composition over inheritance when possible
2. Use virtual destructors in base classes that will be inherited
3. Use 'override' keyword for clarity and safety
4. Use 'final' to prevent further overriding/inheritance when needed
5. Keep inheritance hierarchies shallow
6. Avoid multiple inheritance unless necessary (prefer interfaces via pure virtual)

================================================================================
5. DEMONSTRATION
================================================================================
*/

int main() {
    cout << "========== 1. SINGLE INHERITANCE ==========\n";
    {
        Dog d("Buddy", 3, "Golden Retriever");
        d.eat();
        d.bark();
        d.displayDog();
    } // destructors called in reverse order

    cout << "\n========== 2. MULTILEVEL INHERITANCE ==========\n";
    {
        ElectricCar tesla("Tesla", 2024, 4, 100);
        tesla.start();
        tesla.openTrunk();
        tesla.charge();
        tesla.display();
    }

    cout << "\n========== 3. HIERARCHICAL INHERITANCE ==========\n";
    Circle c(5.0, "Green");
    Rectangle r(4.0, 6.0, "Yellow");
    c.draw();
    cout << "Circle area: " << c.area() << endl;
    r.draw();
    cout << "Rectangle area: " << r.area() << endl;

    cout << "\n========== 4. MULTIPLE INHERITANCE ==========\n";
    Duck donald("Donald");
    donald.showAbilities();

    cout << "\n========== 5. DIAMOND PROBLEM + VIRTUAL INHERITANCE ==========\n";
    {
        Manager m("Alice", 35, "MIT", 3.9, "Google", 150000, "AI Research");
        m.manage();
    }

    cout << "\n========== 6. OVERRIDING vs HIDING ==========\n";
    Derived der;
    Base* basePtr = &der;

    basePtr->show();      // calls Derived::show() (virtual)
    basePtr->display();   // calls Base::display() (non-virtual - hiding)

    der.show();
    der.display();

    cout << "\n========== PROGRAM END ==========\n";
    return 0;
}

/*
================================================================================
QUICK REFERENCE - TYPES OF INHERITANCE
================================================================================

1. Single Inheritance
   A → B

2. Multilevel Inheritance
   A → B → C

3. Hierarchical Inheritance
      A
     / \
    B   C

4. Multiple Inheritance
   A   B
    \ /
     C

5. Hybrid Inheritance (combination of above)
   Often involves diamond → use virtual inheritance

================================================================================
*/
/*
================================================================================
                    CONSTRUCTORS IN C++ - COMPLETE GUIDE
              From Beginner to Advanced Level
================================================================================

A Constructor is a special member function of a class that is automatically
called when an object of that class is created. Its primary purpose is to
initialize the object's data members.

Key Characteristics:
- Same name as the class
- No return type (not even void)
- Automatically invoked when object is created
- Can be overloaded
- Can have default arguments
- Cannot be inherited or virtual (but can call base class constructors)

================================================================================
1. BEGINNER LEVEL - Basic Constructors
================================================================================
*/

#include <iostream>
#include <string>
using namespace std;

// -----------------------------------------------------------------------------
// Example 1: Default Constructor
// -----------------------------------------------------------------------------
class Student {
private:
    string name;
    int age;
    int rollNo;

public:
    // Default Constructor - no parameters
    // Called when: Student s1;
    Student() {
        name = "Unknown";
        age = 0;
        rollNo = 0;
        cout << "[Default Constructor] Object created with default values." << endl;
    }

    void display() {
        cout << "Name: " << name << ", Age: " << age 
             << ", Roll No: " << rollNo << endl;
    }
};

// -----------------------------------------------------------------------------
// Example 2: Parameterized Constructor
// -----------------------------------------------------------------------------
class Book {
private:
    string title;
    string author;
    double price;

public:
    // Parameterized Constructor
    Book(string t, string a, double p) {
        title = t;
        author = a;
        price = p;
        cout << "[Parameterized Constructor] Book object created." << endl;
    }

    void display() {
        cout << "Title: " << title << ", Author: " << author 
             << ", Price: $" << price << endl;
    }
};

/*
================================================================================
2. INTERMEDIATE LEVEL - Constructor Overloading, Default Arguments,
                        Copy Constructor, Initializer Lists
================================================================================
*/

// -----------------------------------------------------------------------------
// Example 3: Constructor Overloading
// -----------------------------------------------------------------------------
class Rectangle {
private:
    double length;
    double width;

public:
    // 1. Default constructor
    Rectangle() {
        length = 0;
        width = 0;
        cout << "Default Rectangle created." << endl;
    }

    // 2. Single parameter (square)
    Rectangle(double side) {
        length = side;
        width = side;
        cout << "Square created with side " << side << endl;
    }

    // 3. Two parameters
    Rectangle(double l, double w) {
        length = l;
        width = w;
        cout << "Rectangle created: " << l << " x " << w << endl;
    }

    double area() {
        return length * width;
    }
};

// -----------------------------------------------------------------------------
// Example 4: Constructor with Default Arguments
// -----------------------------------------------------------------------------
class Circle {
private:
    double radius;
    string color;

public:
    // Default arguments allow flexible object creation
    Circle(double r = 1.0, string c = "Red") {
        radius = r;
        color = c;
        cout << "Circle created: radius=" << radius 
             << ", color=" << color << endl;
    }

    double area() {
        return 3.14159 * radius * radius;
    }
};

// -----------------------------------------------------------------------------
// Example 5: Copy Constructor
// -----------------------------------------------------------------------------
/*
Copy Constructor is a special constructor used to create a new object as a
copy of an existing object.

Syntax: ClassName(const ClassName &obj)

When is it called?
1. When an object is initialized from another object of the same type
2. When an object is passed by value to a function
3. When an object is returned by value from a function
4. When the compiler generates a temporary object

If you don't define one, compiler provides a shallow copy constructor.
*/

class DeepCopyDemo {
private:
    int *data;   // pointer to dynamic memory
    int size;

public:
    // Parameterized constructor
    DeepCopyDemo(int s) {
        size = s;
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = i + 1;
        }
        cout << "Parameterized constructor called." << endl;
    }

    // Deep Copy Constructor (IMPORTANT for classes with dynamic memory)
    DeepCopyDemo(const DeepCopyDemo &other) {
        size = other.size;
        data = new int[size];          // allocate NEW memory
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];   // copy values
        }
        cout << "Deep Copy Constructor called." << endl;
    }

    // Destructor (required when using dynamic memory)
    ~DeepCopyDemo() {
        delete[] data;
        cout << "Destructor called. Memory freed." << endl;
    }

    void display() {
        cout << "Data: ";
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    void modify(int index, int value) {
        if (index >= 0 && index < size)
            data[index] = value;
    }
};

// -----------------------------------------------------------------------------
// Example 6: Member Initializer List (Preferred way)
// -----------------------------------------------------------------------------
/*
Member Initializer List is more efficient because:
1. It initializes members directly instead of first default-constructing
   then assigning.
2. Required for const members and reference members.
3. Required when calling base class constructors in inheritance.
*/

class Point {
private:
    const int x;      // const member - MUST use initializer list
    const int y;
    int &ref;         // reference member - MUST use initializer list

public:
    // Using Member Initializer List
    Point(int a, int b, int &r) : x(a), y(b), ref(r) {
        cout << "Point created using initializer list: (" 
             << x << ", " << y << ")" << endl;
    }

    void display() {
        cout << "x = " << x << ", y = " << y 
             << ", ref = " << ref << endl;
    }
};

/*
================================================================================
3. ADVANCED LEVEL - Explicit Constructors, Delegating Constructors,
                    Move Constructors (C++11), Constructor Rules
================================================================================
*/

// -----------------------------------------------------------------------------
// Example 7: Explicit Constructor (prevents implicit conversion)
// -----------------------------------------------------------------------------
class Distance {
private:
    int meters;

public:
    // Without 'explicit', Distance d = 10; would work (implicit conversion)
    explicit Distance(int m) {
        meters = m;
        cout << "Distance object created with " << meters << " meters." << endl;
    }

    void display() {
        cout << "Distance: " << meters << " m" << endl;
    }
};

// -----------------------------------------------------------------------------
// Example 8: Delegating Constructors (C++11)
// -----------------------------------------------------------------------------
/*
A constructor can call another constructor of the same class.
This reduces code duplication.
*/

class Employee {
private:
    string name;
    int id;
    double salary;
    string department;

public:
    // Main constructor
    Employee(string n, int i, double s, string d) 
        : name(n), id(i), salary(s), department(d) {
        cout << "Full constructor called for " << name << endl;
    }

    // Delegating constructors
    Employee(string n, int i) 
        : Employee(n, i, 0.0, "Unassigned") {   // delegates to main constructor
        cout << "Delegating constructor (name, id) called." << endl;
    }

    Employee() 
        : Employee("Unknown", 0) {              // delegates further
        cout << "Default delegating constructor called." << endl;
    }

    void display() {
        cout << "Name: " << name << ", ID: " << id 
             << ", Salary: " << salary 
             << ", Dept: " << department << endl;
    }
};

// -----------------------------------------------------------------------------
// Example 9: Move Constructor (C++11) - for efficient resource transfer
// -----------------------------------------------------------------------------
/*
Move Constructor transfers ownership of resources from a temporary (rvalue)
object to a new object, avoiding expensive deep copies.

Syntax: ClassName(ClassName &&other) noexcept
*/

class MoveDemo {
private:
    int *data;
    size_t size;

public:
    // Constructor
    MoveDemo(size_t s) : size(s) {
        data = new int[size];
        for (size_t i = 0; i < size; i++) data[i] = static_cast<int>(i);
        cout << "Constructor: allocated " << size << " integers." << endl;
    }

    // Copy Constructor (expensive)
    MoveDemo(const MoveDemo &other) : size(other.size) {
        data = new int[size];
        for (size_t i = 0; i < size; i++) data[i] = other.data[i];
        cout << "Copy Constructor: deep copied " << size << " integers." << endl;
    }

    // Move Constructor (cheap - steals resources)
    MoveDemo(MoveDemo &&other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;   // leave source in valid but empty state
        other.size = 0;
        cout << "Move Constructor: stole resources!" << endl;
    }

    // Destructor
    ~MoveDemo() {
        delete[] data;
        cout << "Destructor called." << endl;
    }

    void display() const {
        if (data == nullptr) {
            cout << "Empty object (moved from)." << endl;
            return;
        }
        cout << "Size: " << size << ", First element: " << data[0] << endl;
    }
};

// Helper function that returns a temporary object (rvalue)
MoveDemo createTemp(size_t s) {
    return MoveDemo(s);
}

/*
================================================================================
4. IMPORTANT RULES & BEST PRACTICES
================================================================================

1. Rule of Three (C++98/03):
   If you need to define any of: Destructor, Copy Constructor, Copy Assignment
   → You probably need to define all three.

2. Rule of Five (C++11):
   Add Move Constructor and Move Assignment Operator.

3. Rule of Zero:
   Prefer designs where you don't need to write any of the special members
   (use smart pointers, containers, etc.).

4. Always initialize members in the order they are declared in the class
   (initializer list order should match declaration order).

5. Prefer initializer lists over assignment in constructor body.

6. Mark single-argument constructors as 'explicit' unless conversion is desired.

7. Use '= default' and '= delete' (C++11) to control special members.

================================================================================
5. DEMONSTRATION - main() function
================================================================================
*/

int main() {
    cout << "========== 1. DEFAULT CONSTRUCTOR ==========\n";
    Student s1;
    s1.display();

    cout << "\n========== 2. PARAMETERIZED CONSTRUCTOR ==========\n";
    Book b1("The C++ Programming Language", "Bjarne Stroustrup", 69.99);
    b1.display();

    cout << "\n========== 3. CONSTRUCTOR OVERLOADING ==========\n";
    Rectangle r1;           // default
    Rectangle r2(5.0);      // square
    Rectangle r3(4.0, 6.0); // rectangle
    cout << "Areas: " << r1.area() << ", " << r2.area() 
         << ", " << r3.area() << endl;

    cout << "\n========== 4. DEFAULT ARGUMENTS ==========\n";
    Circle c1;                  // both defaults
    Circle c2(5.0);             // default color
    Circle c3(3.0, "Blue");     // both provided

    cout << "\n========== 5. COPY CONSTRUCTOR (Deep Copy) ==========\n";
    {
        DeepCopyDemo d1(5);
        d1.display();

        DeepCopyDemo d2 = d1;   // copy constructor
        d2.modify(0, 100);      // modify copy

        cout << "After modifying copy:\n";
        cout << "Original: ";
        d1.display();
        cout << "Copy:     ";
        d2.display();
    } // destructors called here

    cout << "\n========== 6. INITIALIZER LIST ==========\n";
    int value = 42;
    Point p(10, 20, value);
    p.display();

    cout << "\n========== 7. EXPLICIT CONSTRUCTOR ==========\n";
    Distance dist(100);
    // Distance dist2 = 200;  // ERROR if explicit is used
    dist.display();

    cout << "\n========== 8. DELEGATING CONSTRUCTORS ==========\n";
    Employee e1;
    e1.display();
    Employee e2("Alice", 101);
    e2.display();
    Employee e3("Bob", 102, 75000, "Engineering");
    e3.display();

    cout << "\n========== 9. MOVE CONSTRUCTOR ==========\n";
    MoveDemo m1 = createTemp(1000);  // move constructor used
    m1.display();

    MoveDemo m2(std::move(m1));      // explicit move
    m2.display();
    m1.display();                    // m1 is now empty

    cout << "\n========== PROGRAM END ==========\n";
    return 0;
}

/*
================================================================================
SUMMARY - KEY TAKEAWAYS
================================================================================

| Constructor Type       | When Used                              | Key Point                      |
|------------------------|----------------------------------------|--------------------------------|
| Default                | Object created without arguments       | Compiler provides if none      |
| Parameterized          | Object created with arguments          | Most common                    |
| Copy                   | Object initialized from another object | Deep vs Shallow copy           |
| Move (C++11)           | Transfer resources from rvalue         | Efficient for large objects    |
| Delegating (C++11)     | One ctor calls another                 | Reduces duplication            |
| Explicit               | Prevent implicit conversions           | Good practice for 1-arg ctors  |

Always prefer:
- Initializer lists
- Rule of Zero / Rule of Five awareness
- explicit for single-argument constructors
- Deep copy when managing resources

================================================================================
*/
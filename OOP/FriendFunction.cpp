/*
================================================================================
                    FRIEND FUNCTION & FRIEND CLASS IN C++ 
                         COMPLETE GUIDE
              From Beginner to Advanced Level
================================================================================

A Friend Function is a function that is not a member of a class but has
access to the private and protected members of the class.

It is declared inside the class with the 'friend' keyword.

Key Points:
- Friend functions are not member functions
- They can be global functions or member functions of another class
- Friendship is not mutual (if A is friend of B, B is not automatically friend of A)
- Friendship is not inherited
- Friendship is not transitive
- Use sparingly — it breaks encapsulation

When to use Friend Functions:
1. Operator overloading (especially << and >>)
2. When a function needs access to private data of two or more different classes
3. Performance-critical code where getters would be too slow (rare)
4. Factory functions / helper functions that need deep access

================================================================================
1. BEGINNER LEVEL - Basic Friend Function
================================================================================
*/

#include <iostream>
#include <string>
using namespace std;

// -----------------------------------------------------------------------------
// Example 1: Simple Friend Function
// -----------------------------------------------------------------------------
class Box {
private:
    double length;
    double width;
    double height;

public:
    Box(double l = 0, double w = 0, double h = 0) 
        : length(l), width(w), height(h) {}

    // Declare friend function
    friend void printDimensions(const Box& b);

    // Friend function that calculates volume
    friend double calculateVolume(const Box& b);

    void setDimensions(double l, double w, double h) {
        length = l;
        width = w;
        height = h;
    }
};

// Friend function definition (not a member of Box)
void printDimensions(const Box& b) {
    // Can access private members directly
    cout << "Length: " << b.length 
         << ", Width: " << b.width 
         << ", Height: " << b.height << endl;
}

double calculateVolume(const Box& b) {
    return b.length * b.width * b.height;
}

// -----------------------------------------------------------------------------
// Example 2: Friend Function for Operator Overloading
// -----------------------------------------------------------------------------
class ComplexNumber {
private:
    double real;
    double imag;

public:
    ComplexNumber(double r = 0, double i = 0) : real(r), imag(i) {}

    // Friend operator overloads
    friend ComplexNumber operator+(const ComplexNumber& a, const ComplexNumber& b);
    friend ComplexNumber operator*(const ComplexNumber& a, const ComplexNumber& b);
    friend ostream& operator<<(ostream& os, const ComplexNumber& c);
    friend istream& operator>>(istream& is, ComplexNumber& c);

    // Member function for comparison
    bool operator==(const ComplexNumber& other) const {
        return real == other.real && imag == other.imag;
    }
};

ComplexNumber operator+(const ComplexNumber& a, const ComplexNumber& b) {
    return ComplexNumber(a.real + b.real, a.imag + b.imag);
}

ComplexNumber operator*(const ComplexNumber& a, const ComplexNumber& b) {
    // (a+bi)(c+di) = (ac-bd) + (ad+bc)i
    return ComplexNumber(
        a.real * b.real - a.imag * b.imag,
        a.real * b.imag + a.imag * b.real
    );
}

ostream& operator<<(ostream& os, const ComplexNumber& c) {
    os << c.real;
    if (c.imag >= 0) os << " + " << c.imag << "i";
    else os << " - " << -c.imag << "i";
    return os;
}

istream& operator>>(istream& is, ComplexNumber& c) {
    cout << "Enter real part: ";
    is >> c.real;
    cout << "Enter imaginary part: ";
    is >> c.imag;
    return is;
}

/*
================================================================================
2. INTERMEDIATE LEVEL - Friend Class, Member Friend Functions,
                        Friend with Multiple Classes
================================================================================
*/

// -----------------------------------------------------------------------------
// Example 3: Friend Class
// -----------------------------------------------------------------------------
/*
When a class is declared as a friend of another class, all member functions
of the friend class can access the private/protected members of the other class.
*/

class Engine;       // Forward declaration

class Car {
private:
    string model;
    int year;
    Engine* engine;     // Car has an Engine

public:
    Car(string m, int y);
    ~Car();

    void display() const;
    void startCar();

    // Declare Engine as friend so it can access Car's private members if needed
    // (In this design we mostly go the other way)
};

class Engine {
private:
    int horsepower;
    double capacity;    // in liters
    bool isRunning;

public:
    Engine(int hp, double cap) : horsepower(hp), capacity(cap), isRunning(false) {}

    void start() {
        isRunning = true;
        cout << "Engine started (" << horsepower << " HP, " 
             << capacity << "L)" << endl;
    }

    void stop() {
        isRunning = false;
        cout << "Engine stopped." << endl;
    }

    // Friend declaration: Car can access Engine's private members
    friend class Car;
};

// Car implementation
Car::Car(string m, int y) : model(m), year(y) {
    engine = new Engine(300, 3.0);   // create engine
}

Car::~Car() {
    delete engine;
}

void Car::display() const {
    cout << "Car: " << model << " (" << year << ")" << endl;
    // Accessing private members of Engine because Car is a friend
    cout << "  Engine: " << engine->horsepower << " HP, "
         << engine->capacity << "L, Status: "
         << (engine->isRunning ? "Running" : "Off") << endl;
}

void Car::startCar() {
    cout << "Starting " << model << "..." << endl;
    engine->start();
}

// -----------------------------------------------------------------------------
// Example 4: Function that is Friend of Multiple Classes
// -----------------------------------------------------------------------------
class Student;
class Teacher;

class Student {
private:
    string name;
    int marks;

public:
    Student(string n, int m) : name(n), marks(m) {}

    friend void compareMarks(const Student& s, const Teacher& t);
};

class Teacher {
private:
    string name;
    int experience;     // years
    int standardMarks;  // expected marks

public:
    Teacher(string n, int exp, int std) 
        : name(n), experience(exp), standardMarks(std) {}

    friend void compareMarks(const Student& s, const Teacher& t);
};

// This function is friend of both classes
void compareMarks(const Student& s, const Teacher& t) {
    cout << "Student: " << s.name << " scored " << s.marks << endl;
    cout << "Teacher: " << t.name << " expects " << t.standardMarks << endl;

    if (s.marks >= t.standardMarks) {
        cout << "Result: Student meets the standard!" << endl;
    } else {
        cout << "Result: Student needs improvement." << endl;
    }
}

// -----------------------------------------------------------------------------
// Example 5: Member Function of One Class as Friend of Another
// -----------------------------------------------------------------------------
class ClassB;   // Forward declaration

class ClassA {
private:
    int secretA;

public:
    ClassA(int val) : secretA(val) {}

    // Member function that will be friend of ClassB
    void showB(const ClassB& b);
};

class ClassB {
private:
    int secretB;

public:
    ClassB(int val) : secretB(val) {}

    // Declare ClassA's member function as friend
    friend void ClassA::showB(const ClassB& b);
};

void ClassA::showB(const ClassB& b) {
    cout << "ClassA's secret: " << secretA << endl;
    cout << "ClassB's secret (accessed via friendship): " << b.secretB << endl;
}

/*
================================================================================
3. ADVANCED LEVEL - Friend and Templates, Best Practices,
                    Alternatives to Friendship
================================================================================
*/

// -----------------------------------------------------------------------------
// Example 6: Friend Function with Templates
// -----------------------------------------------------------------------------
template <typename T>
class Container {
private:
    T data;
    int id;

public:
    Container(T d, int i) : data(d), id(i) {}

    // Friend function template
    template <typename U>
    friend void printContainer(const Container<U>& c);

    // Friend non-template function
    friend void resetId(Container<T>& c) {
        c.id = 0;
        cout << "ID reset to 0" << endl;
    }
};

template <typename U>
void printContainer(const Container<U>& c) {
    cout << "Container ID: " << c.id << ", Data: " << c.data << endl;
}

// -----------------------------------------------------------------------------
// Example 7: When Friendship is Useful - Matrix Multiplication Helper
// -----------------------------------------------------------------------------
class Matrix {
private:
    int rows, cols;
    int** data;

public:
    Matrix(int r, int c) : rows(r), cols(c) {
        data = new int*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new int[cols]();
        }
    }

    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
    }

    // Disable copy for simplicity in this example
    Matrix(const Matrix&) = delete;
    Matrix& operator=(const Matrix&) = delete;

    void set(int i, int j, int value) {
        if (i >= 0 && i < rows && j >= 0 && j < cols)
            data[i][j] = value;
    }

    void display() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << data[i][j] << "\t";
            }
            cout << endl;
        }
    }

    // Friend function for matrix multiplication
    friend Matrix* multiply(const Matrix& a, const Matrix& b);
};

Matrix* multiply(const Matrix& a, const Matrix& b) {
    if (a.cols != b.rows) {
        cout << "Cannot multiply: incompatible dimensions." << endl;
        return nullptr;
    }

    Matrix* result = new Matrix(a.rows, b.cols);

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < b.cols; j++) {
            int sum = 0;
            for (int k = 0; k < a.cols; k++) {
                sum += a.data[i][k] * b.data[k][j];
            }
            result->data[i][j] = sum;
        }
    }
    return result;
}

/*
================================================================================
4. BEST PRACTICES & ALTERNATIVES
================================================================================

When to use friend:
✓ Operator overloading (<<, >>, +, -, etc.) where left operand is not the class
✓ Functions that need intimate knowledge of two or more classes
✓ Performance-critical code (very rare justification)

When NOT to use friend:
✗ As a shortcut to avoid writing proper getters
✗ Just because you want easy access
✗ In most application-level code

Alternatives to Friendship:
1. Public getters / setters (preferred for most cases)
2. Nested classes
3. Make the function a member function
4. Use public interfaces and pass necessary data
5. Refactor design so that one class owns the data

Remember:
Friendship grants access but does not grant inheritance or membership.
A friend function is called like a normal function, not with the object.dot syntax.

================================================================================
5. DEMONSTRATION
================================================================================
*/

int main() {
    cout << "========== 1. BASIC FRIEND FUNCTION ==========\n";
    Box box(3.5, 2.0, 1.5);
    printDimensions(box);
    cout << "Volume: " << calculateVolume(box) << endl;

    cout << "\n========== 2. FRIEND OPERATORS ==========\n";
    ComplexNumber c1(3, 4);
    ComplexNumber c2(1, 2);

    cout << "c1 = " << c1 << endl;
    cout << "c2 = " << c2 << endl;
    cout << "c1 + c2 = " << (c1 + c2) << endl;
    cout << "c1 * c2 = " << (c1 * c2) << endl;

    cout << "\n========== 3. FRIEND CLASS ==========\n";
    Car myCar("Tesla Model S", 2024);
    myCar.display();
    myCar.startCar();
    myCar.display();

    cout << "\n========== 4. FRIEND OF MULTIPLE CLASSES ==========\n";
    Student stud("Alice", 85);
    Teacher teach("Dr. Smith", 15, 70);
    compareMarks(stud, teach);

    cout << "\n========== 5. MEMBER FUNCTION AS FRIEND ==========\n";
    ClassA a(100);
    ClassB b(200);
    a.showB(b);

    cout << "\n========== 6. FRIEND WITH TEMPLATES ==========\n";
    Container<string> c("Hello Friends", 1);
    printContainer(c);
    resetId(c);
    printContainer(c);

    Container<int> cInt(42, 2);
    printContainer(cInt);

    cout << "\n========== 7. MATRIX MULTIPLICATION (FRIEND) ==========\n";
    Matrix m1(2, 3);
    m1.set(0, 0, 1); m1.set(0, 1, 2); m1.set(0, 2, 3);
    m1.set(1, 0, 4); m1.set(1, 1, 5); m1.set(1, 2, 6);

    Matrix m2(3, 2);
    m2.set(0, 0, 7); m2.set(0, 1, 8);
    m2.set(1, 0, 9); m2.set(1, 1, 10);
    m2.set(2, 0, 11); m2.set(2, 1, 12);

    cout << "Matrix A:\n";
    m1.display();
    cout << "\nMatrix B:\n";
    m2.display();

    Matrix* result = multiply(m1, m2);
    if (result) {
        cout << "\nA x B:\n";
        result->display();
        delete result;
    }

    cout << "\n========== PROGRAM END ==========\n";
    return 0;
}

/*
================================================================================
SUMMARY - KEY TAKEAWAYS
================================================================================

Friend Function:
- Non-member function with access to private/protected members
- Declared with 'friend' keyword inside the class
- Defined outside the class like a normal function

Friend Class:
- All members of the friend class get access
- Declared as: friend class ClassName;

Important Properties:
┌────────────────────────┬─────────────┐
│ Property               │ Status      │
├────────────────────────┼─────────────┤
│ Mutual                 │ No          │
│ Inherited              │ No          │
│ Transitive             │ No          │
│ Affects Encapsulation  │ Yes (breaks)│
└────────────────────────┴─────────────┘

Use friend primarily for:
1. Symmetric operator overloading
2. Tightly coupled classes that need mutual private access
3. Certain design patterns (e.g., Iterator sometimes)

Otherwise → Prefer proper encapsulation with public interfaces.

================================================================================
*/
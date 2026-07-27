/*
================================================================================
                    ABSTRACTION IN C++ - COMPLETE GUIDE
              From Beginner to Advanced Level
================================================================================

Abstraction means showing only essential features and hiding unnecessary
implementation details from the user.

It focuses on "what" an object does rather than "how" it does it.

Abstraction vs Encapsulation:
- Encapsulation → Hiding the data (implementation details of data)
- Abstraction   → Hiding the complexity (implementation details of behavior)
                  and showing only the relevant interface

In C++, Abstraction is achieved primarily through:
1. Abstract Classes (classes with pure virtual functions)
2. Interfaces (pure abstract classes)
3. Header files + separate implementation
4. Access specifiers (supporting role)

================================================================================
1. BEGINNER LEVEL - Understanding Abstraction Concept
================================================================================
*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// -----------------------------------------------------------------------------
// Example 1: Real-world Analogy - Car
// -----------------------------------------------------------------------------
/*
When you drive a car, you use:
- Steering wheel
- Accelerator
- Brake
- Gear

You don't need to know:
- How the engine injects fuel
- How the transmission works internally
- How ABS calculates braking force

This is Abstraction: You interact with a simple interface.
*/

class Car {
private:
    // Complex internal details (hidden)
    double fuelLevel;
    double engineTemperature;
    bool engineOn;
    int currentGear;

    // Private complex methods
    void injectFuel() {
        if (fuelLevel > 0) {
            fuelLevel -= 0.1;
            engineTemperature += 0.5;
        }
    }

    void coolEngine() {
        if (engineTemperature > 90) {
            engineTemperature -= 2.0;
        }
    }

    void checkSystems() {
        if (fuelLevel < 5) {
            cout << "[System] Low fuel warning!" << endl;
        }
        if (engineTemperature > 110) {
            cout << "[System] Engine overheating!" << endl;
        }
    }

public:
    Car() : fuelLevel(50.0), engineTemperature(25.0), 
            engineOn(false), currentGear(0) {}

    // Simple public interface (what the user needs)
    void start() {
        if (!engineOn) {
            engineOn = true;
            cout << "Car started." << endl;
        }
    }

    void stop() {
        engineOn = false;
        currentGear = 0;
        cout << "Car stopped." << endl;
    }

    void accelerate() {
        if (!engineOn) {
            cout << "Start the car first!" << endl;
            return;
        }
        injectFuel();
        coolEngine();
        checkSystems();
        cout << "Accelerating... Speed increasing." << endl;
    }

    void brake() {
        cout << "Braking... Speed decreasing." << endl;
    }

    void displayDashboard() const {
        cout << "\n--- Dashboard ---\n"
             << "Fuel: " << fuelLevel << "%\n"
             << "Engine Temp: " << engineTemperature << " C\n"
             << "Engine: " << (engineOn ? "ON" : "OFF") << "\n";
    }
};

/*
================================================================================
2. INTERMEDIATE LEVEL - Abstract Classes & Interfaces
================================================================================
*/

// -----------------------------------------------------------------------------
// Example 2: Abstract Class (Partial Abstraction)
// -----------------------------------------------------------------------------
/*
An abstract class can have:
- Pure virtual functions (must be overridden)
- Regular virtual functions (can be overridden)
- Concrete (non-virtual) functions
- Data members

You cannot create objects of an abstract class.
*/

class PaymentMethod {                   // Abstract class
protected:
    string accountHolder;

public:
    PaymentMethod(string name) : accountHolder(name) {}

    // Pure virtual - forces derived classes to implement
    virtual bool processPayment(double amount) = 0;
    virtual string getType() const = 0;

    // Concrete method - shared behavior
    void showHolder() const {
        cout << "Account Holder: " << accountHolder << endl;
    }

    virtual ~PaymentMethod() {}
};

class CreditCard : public PaymentMethod {
private:
    string cardNumber;
    double creditLimit;
    double currentBalance;

public:
    CreditCard(string name, string number, double limit)
        : PaymentMethod(name), cardNumber(number), 
          creditLimit(limit), currentBalance(0) {}

    bool processPayment(double amount) override {
        if (currentBalance + amount > creditLimit) {
            cout << "Credit limit exceeded!" << endl;
            return false;
        }
        currentBalance += amount;
        cout << "Credit Card payment of $" << amount << " successful." << endl;
        return true;
    }

    string getType() const override {
        return "Credit Card";
    }

    void showDetails() const {
        showHolder();
        cout << "Type: " << getType() << endl;
        cout << "Card: ****" << cardNumber.substr(cardNumber.length() - 4) << endl;
        cout << "Available Credit: $" << (creditLimit - currentBalance) << endl;
    }
};

class PayPal : public PaymentMethod {
private:
    string email;
    double balance;

public:
    PayPal(string name, string mail, double bal)
        : PaymentMethod(name), email(mail), balance(bal) {}

    bool processPayment(double amount) override {
        if (amount > balance) {
            cout << "Insufficient PayPal balance!" << endl;
            return false;
        }
        balance -= amount;
        cout << "PayPal payment of $" << amount << " successful." << endl;
        return true;
    }

    string getType() const override {
        return "PayPal";
    }

    void showDetails() const {
        showHolder();
        cout << "Type: " << getType() << endl;
        cout << "Email: " << email << endl;
        cout << "Balance: $" << balance << endl;
    }
};

// -----------------------------------------------------------------------------
// Example 3: Pure Interface (100% Abstract Class)
// -----------------------------------------------------------------------------
/*
A pure interface in C++ is a class with:
- Only pure virtual functions
- No data members (or only static constexpr)
- No concrete methods (except maybe virtual destructor)

This is the closest C++ has to interfaces in Java/C#.
*/

class IPrintable {
public:
    virtual void print() const = 0;
    virtual ~IPrintable() {}
};

class ISerializable {
public:
    virtual string serialize() const = 0;
    virtual void deserialize(const string& data) = 0;
    virtual ~ISerializable() {}
};

// A class can implement multiple interfaces
class Document : public IPrintable, public ISerializable {
private:
    string title;
    string content;

public:
    Document(string t, string c) : title(t), content(c) {}

    void print() const override {
        cout << "===== " << title << " =====\n" << content << "\n";
    }

    string serialize() const override {
        return title + "|" + content;
    }

    void deserialize(const string& data) override {
        size_t pos = data.find('|');
        if (pos != string::npos) {
            title = data.substr(0, pos);
            content = data.substr(pos + 1);
        }
    }
};

/*
================================================================================
3. ADVANCED LEVEL - Abstraction in Design, Template Abstraction,
                    Layered Architecture Concepts
================================================================================
*/

// -----------------------------------------------------------------------------
// Example 4: High-level Abstraction - Database Interface
// -----------------------------------------------------------------------------
/*
In real applications, we abstract the storage mechanism so that
business logic doesn't depend on whether we use MySQL, MongoDB, files, etc.
*/

class IDatabase {
public:
    virtual bool connect(const string& connectionString) = 0;
    virtual bool disconnect() = 0;
    virtual bool executeQuery(const string& query) = 0;
    virtual vector<string> fetchResults() = 0;
    virtual ~IDatabase() {}
};

class MySQLDatabase : public IDatabase {
private:
    bool connected;
    vector<string> results;

public:
    MySQLDatabase() : connected(false) {}

    bool connect(const string& connectionString) override {
        cout << "[MySQL] Connecting with: " << connectionString << endl;
        connected = true;
        return true;
    }

    bool disconnect() override {
        cout << "[MySQL] Disconnected." << endl;
        connected = false;
        return true;
    }

    bool executeQuery(const string& query) override {
        if (!connected) {
            cout << "[MySQL] Not connected!" << endl;
            return false;
        }
        cout << "[MySQL] Executing: " << query << endl;
        // Simulate results
        results = {"Row1", "Row2", "Row3"};
        return true;
    }

    vector<string> fetchResults() override {
        return results;
    }
};

class FileDatabase : public IDatabase {
private:
    bool connected;
    string filename;
    vector<string> results;

public:
    FileDatabase() : connected(false) {}

    bool connect(const string& connectionString) override {
        filename = connectionString;
        cout << "[FileDB] Opening file: " << filename << endl;
        connected = true;
        return true;
    }

    bool disconnect() override {
        cout << "[FileDB] Closed file: " << filename << endl;
        connected = false;
        return true;
    }

    bool executeQuery(const string& query) override {
        if (!connected) return false;
        cout << "[FileDB] Processing query on file: " << query << endl;
        results = {"FileRecord1", "FileRecord2"};
        return true;
    }

    vector<string> fetchResults() override {
        return results;
    }
};

// High-level module that depends only on abstraction
class UserService {
private:
    IDatabase* db;      // depends on abstraction, not concrete class

public:
    UserService(IDatabase* database) : db(database) {}

    void getAllUsers() {
        db->executeQuery("SELECT * FROM users");
        auto results = db->fetchResults();
        cout << "Users found: ";
        for (const auto& r : results) {
            cout << r << " ";
        }
        cout << endl;
    }
};

// -----------------------------------------------------------------------------
// Example 5: Abstraction via Templates (Generic Programming)
// -----------------------------------------------------------------------------
/*
Templates provide compile-time abstraction.
The algorithm is written once and works with any type that supports
the required operations.
*/

template <typename T>
class Stack {
private:
    vector<T> elements;

public:
    void push(const T& item) {
        elements.push_back(item);
    }

    void pop() {
        if (!elements.empty()) {
            elements.pop_back();
        }
    }

    T top() const {
        if (elements.empty()) {
            throw runtime_error("Stack is empty");
        }
        return elements.back();
    }

    bool empty() const {
        return elements.empty();
    }

    size_t size() const {
        return elements.size();
    }
};

// -----------------------------------------------------------------------------
// Example 6: Layered Abstraction - Shape Drawing System
// -----------------------------------------------------------------------------
class IRenderer {
public:
    virtual void drawCircle(double x, double y, double radius) = 0;
    virtual void drawRectangle(double x, double y, double w, double h) = 0;
    virtual ~IRenderer() {}
};

class OpenGLRenderer : public IRenderer {
public:
    void drawCircle(double x, double y, double radius) override {
        cout << "[OpenGL] Drawing circle at (" << x << "," << y 
             << ") radius " << radius << endl;
    }

    void drawRectangle(double x, double y, double w, double h) override {
        cout << "[OpenGL] Drawing rectangle at (" << x << "," << y 
             << ") size " << w << "x" << h << endl;
    }
};

class SVGRenderer : public IRenderer {
public:
    void drawCircle(double x, double y, double radius) override {
        cout << "[SVG] <circle cx=\"" << x << "\" cy=\"" << y 
             << "\" r=\"" << radius << "\" />" << endl;
    }

    void drawRectangle(double x, double y, double w, double h) override {
        cout << "[SVG] <rect x=\"" << x << "\" y=\"" << y 
             << "\" width=\"" << w << "\" height=\"" << h << "\" />" << endl;
    }
};

// High-level shapes depend only on IRenderer abstraction
class AbstractShape {
protected:
    IRenderer* renderer;

public:
    AbstractShape(IRenderer* r) : renderer(r) {}
    virtual void draw() = 0;
    virtual ~AbstractShape() {}
};

class CircleShape : public AbstractShape {
private:
    double x, y, radius;

public:
    CircleShape(IRenderer* r, double x, double y, double rad)
        : AbstractShape(r), x(x), y(y), radius(rad) {}

    void draw() override {
        renderer->drawCircle(x, y, radius);
    }
};

class RectangleShape : public AbstractShape {
private:
    double x, y, width, height;

public:
    RectangleShape(IRenderer* r, double x, double y, double w, double h)
        : AbstractShape(r), x(x), y(y), width(w), height(h) {}

    void draw() override {
        renderer->drawRectangle(x, y, width, height);
    }
};

/*
================================================================================
4. BEST PRACTICES
================================================================================

1. Program to an interface, not an implementation.
2. Depend on abstractions (abstract classes / interfaces).
3. Keep interfaces small and focused (Interface Segregation Principle).
4. Prefer pure interfaces when you only need a contract.
5. Use abstract classes when you want to share some common code.
6. Hide complex algorithms behind simple method names.
7. Use the Dependency Inversion Principle (high-level modules should not
   depend on low-level modules; both should depend on abstractions).

================================================================================
5. DEMONSTRATION
================================================================================
*/

int main() {
    cout << "========== 1. REAL-WORLD ABSTRACTION (CAR) ==========\n";
    Car myCar;
    myCar.start();
    myCar.accelerate();
    myCar.accelerate();
    myCar.brake();
    myCar.displayDashboard();
    myCar.stop();

    cout << "\n========== 2. ABSTRACT CLASS - PAYMENT SYSTEM ==========\n";
    CreditCard cc("Alice", "1234567890123456", 5000);
    PayPal pp("Bob", "bob@email.com", 1500);

    PaymentMethod* methods[] = {&cc, &pp};

    for (auto method : methods) {
        method->showHolder();
        cout << "Type: " << method->getType() << endl;
        method->processPayment(200);
        cout << endl;
    }

    cout << "========== 3. PURE INTERFACES ==========\n";
    Document doc("My Report", "This is the content of the report.");
    doc.print();

    string data = doc.serialize();
    cout << "Serialized: " << data << endl;

    Document doc2("", "");
    doc2.deserialize(data);
    doc2.print();

    cout << "\n========== 4. DATABASE ABSTRACTION ==========\n";
    MySQLDatabase mysql;
    mysql.connect("server=localhost;db=mydb;user=root");

    UserService service1(&mysql);
    service1.getAllUsers();
    mysql.disconnect();

    cout << endl;

    FileDatabase fileDb;
    fileDb.connect("users.txt");
    UserService service2(&fileDb);
    service2.getAllUsers();
    fileDb.disconnect();

    cout << "\n========== 5. TEMPLATE ABSTRACTION ==========\n";
    Stack<int> intStack;
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    cout << "Top: " << intStack.top() << ", Size: " << intStack.size() << endl;

    Stack<string> strStack;
    strStack.push("Hello");
    strStack.push("World");
    cout << "Top: " << strStack.top() << endl;

    cout << "\n========== 6. LAYERED RENDERING ABSTRACTION ==========\n";
    OpenGLRenderer opengl;
    SVGRenderer svg;

    CircleShape circle1(&opengl, 10, 20, 5);
    RectangleShape rect1(&opengl, 0, 0, 100, 50);

    CircleShape circle2(&svg, 15, 25, 8);
    RectangleShape rect2(&svg, 5, 5, 80, 40);

    cout << "--- Using OpenGL ---\n";
    circle1.draw();
    rect1.draw();

    cout << "\n--- Using SVG ---\n";
    circle2.draw();
    rect2.draw();

    cout << "\n========== PROGRAM END ==========\n";
    return 0;
}

/*
================================================================================
SUMMARY - KEY TAKEAWAYS
================================================================================

Abstraction = Focus on WHAT, hide the HOW

How C++ supports Abstraction:
1. Abstract classes (pure virtual functions)
2. Pure interfaces (all pure virtual)
3. Access specifiers (private/protected)
4. Header / Implementation separation
5. Templates (compile-time abstraction)

Levels of Abstraction:
┌─────────────────────┬──────────────────────────────────────┐
│ Level               │ Example                              │
├─────────────────────┼──────────────────────────────────────┤
│ Low                 │ Assembly / machine instructions      │
│ Medium              │ Classes with private helpers         │
│ High                │ Abstract interfaces + services       │
│ Very High           │ Frameworks, domain-specific languages│
└─────────────────────┴──────────────────────────────────────┘

Golden Rule:
"Depend upon abstractions. Do not depend upon concretions."
— Robert C. Martin (Dependency Inversion Principle)

================================================================================
*/
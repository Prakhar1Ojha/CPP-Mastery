/*
================================================================================
                    ENCAPSULATION IN C++ - COMPLETE GUIDE
              From Beginner to Advanced Level
================================================================================

Encapsulation is the bundling of data (attributes) and methods (functions)
that operate on that data into a single unit (class), and restricting
direct access to some of the object's components.

It is one of the four fundamental principles of OOP:
1. Encapsulation
2. Abstraction
3. Inheritance
4. Polymorphism

Key Benefits:
- Data Hiding / Data Protection
- Controlled access through getters and setters
- Improved maintainability and flexibility
- Reduced complexity and increased security
- Ability to change internal implementation without affecting external code

Access Specifiers:
┌───────────┬──────────────────────┬─────────────────────┐
│ Specifier │ Accessible from      │ Accessible from     │
│           │ same class           │ derived class       │
├───────────┼──────────────────────┼─────────────────────┤
│ public    │ Yes                  │ Yes                 │
│ protected │ Yes                  │ Yes                 │
│ private   │ Yes                  │ No                  │
└───────────┴──────────────────────┴─────────────────────┘

================================================================================
1. BEGINNER LEVEL - Basic Encapsulation with Getters & Setters
================================================================================
*/

#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

// -----------------------------------------------------------------------------
// Example 1: Bad Design - No Encapsulation (Everything public)
// -----------------------------------------------------------------------------
class BadBankAccount {
public:
    string owner;
    double balance;     // Anyone can directly modify this!

    void deposit(double amount) {
        balance += amount;
    }
};

// Problem: Anyone can do → account.balance = -1000000;  (invalid state)

// -----------------------------------------------------------------------------
// Example 2: Good Design - Proper Encapsulation
// -----------------------------------------------------------------------------
class BankAccount {
private:
    // Data is hidden (private)
    string accountNumber;
    string ownerName;
    double balance;
    static int totalAccounts;   // shared among all objects

public:
    // Constructor
    BankAccount(string accNo, string owner, double initialBalance = 0.0) {
        accountNumber = accNo;
        ownerName = owner;
        if (initialBalance < 0) {
            balance = 0;
            cout << "Warning: Initial balance cannot be negative. Set to 0." << endl;
        } else {
            balance = initialBalance;
        }
        totalAccounts++;
        cout << "Account created for " << ownerName << endl;
    }

    // Destructor
    ~BankAccount() {
        totalAccounts--;
    }

    // ========== GETTERS (Accessors) ==========
    string getAccountNumber() const {
        return accountNumber;
    }

    string getOwnerName() const {
        return ownerName;
    }

    double getBalance() const {
        return balance;
    }

    static int getTotalAccounts() {
        return totalAccounts;
    }

    // ========== SETTERS (Mutators) with Validation ==========
    void setOwnerName(const string& name) {
        if (name.empty()) {
            cout << "Error: Owner name cannot be empty." << endl;
            return;
        }
        ownerName = name;
    }

    // Note: We deliberately do NOT provide a public setBalance()
    // Balance should only change through controlled methods.

    // ========== Controlled Operations ==========
    bool deposit(double amount) {
        if (amount <= 0) {
            cout << "Error: Deposit amount must be positive." << endl;
            return false;
        }
        balance += amount;
        cout << "Deposited $" << amount << ". New balance: $" << balance << endl;
        return true;
    }

    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "Error: Withdrawal amount must be positive." << endl;
            return false;
        }
        if (amount > balance) {
            cout << "Error: Insufficient funds. Available: $" << balance << endl;
            return false;
        }
        balance -= amount;
        cout << "Withdrew $" << amount << ". New balance: $" << balance << endl;
        return true;
    }

    void display() const {
        cout << "\n--- Account Info ---\n"
             << "Account No : " << accountNumber << "\n"
             << "Owner      : " << ownerName << "\n"
             << "Balance    : $" << balance << "\n";
    }
};

// Static member definition
int BankAccount::totalAccounts = 0;

/*
================================================================================
2. INTERMEDIATE LEVEL - const Correctness, Mutable, Friend (preview),
                        Nested Classes, Access Control Nuances
================================================================================
*/

// -----------------------------------------------------------------------------
// Example 3: const Correctness in Encapsulation
// -----------------------------------------------------------------------------
class Temperature {
private:
    double celsius;
    mutable int accessCount;    // can be modified even in const methods

public:
    Temperature(double c = 0.0) : celsius(c), accessCount(0) {}

    // const getter - promises not to modify the object
    double getCelsius() const {
        accessCount++;          // allowed because accessCount is mutable
        return celsius;
    }

    double getFahrenheit() const {
        accessCount++;
        return (celsius * 9.0 / 5.0) + 32.0;
    }

    int getAccessCount() const {
        return accessCount;
    }

    // Non-const setter
    void setCelsius(double c) {
        if (c < -273.15) {
            throw invalid_argument("Temperature below absolute zero!");
        }
        celsius = c;
    }

    void setFahrenheit(double f) {
        setCelsius((f - 32.0) * 5.0 / 9.0);
    }
};

// -----------------------------------------------------------------------------
// Example 4: Encapsulation with Validation & Invariants
// -----------------------------------------------------------------------------
/*
An invariant is a condition that must always be true for the object
to be in a valid state.
Example: Age should never be negative, balance should not go below minimum, etc.
*/

class Student {
private:
    string name;
    int age;
    float gpa;              // 0.0 to 4.0
    string studentId;

    // Private helper to maintain invariant
    bool isValidGPA(float g) const {
        return g >= 0.0f && g <= 4.0f;
    }

    bool isValidAge(int a) const {
        return a >= 5 && a <= 100;
    }

public:
    Student(string n, int a, float g, string id) {
        setName(n);
        setAge(a);
        setGPA(g);
        studentId = id;     // assume ID is validated elsewhere
    }

    // Getters
    string getName() const { return name; }
    int getAge() const { return age; }
    float getGPA() const { return gpa; }
    string getStudentId() const { return studentId; }

    // Setters with strong validation
    void setName(const string& n) {
        if (n.empty() || n.length() > 50) {
            throw invalid_argument("Name must be 1-50 characters.");
        }
        name = n;
    }

    void setAge(int a) {
        if (!isValidAge(a)) {
            throw invalid_argument("Age must be between 5 and 100.");
        }
        age = a;
    }

    void setGPA(float g) {
        if (!isValidGPA(g)) {
            throw invalid_argument("GPA must be between 0.0 and 4.0.");
        }
        gpa = g;
    }

    // Business logic methods
    string getGradeStatus() const {
        if (gpa >= 3.5) return "Excellent";
        if (gpa >= 3.0) return "Good";
        if (gpa >= 2.0) return "Average";
        return "Needs Improvement";
    }

    void display() const {
        cout << "Student: " << name << " (ID: " << studentId << ")\n"
             << "Age: " << age << ", GPA: " << gpa
             << " [" << getGradeStatus() << "]\n";
    }
};

// -----------------------------------------------------------------------------
// Example 5: Nested Classes (Inner Class) for tighter encapsulation
// -----------------------------------------------------------------------------
class University {
private:
    string name;

    // Nested class - only meaningful in context of University
    class Department {
    private:
        string deptName;
        int facultyCount;

    public:
        Department(string n, int count) : deptName(n), facultyCount(count) {}

        void display() const {
            cout << "  Department: " << deptName 
                 << " | Faculty: " << facultyCount << endl;
        }

        string getName() const { return deptName; }
    };

    Department* departments[10];
    int deptCount;

public:
    University(string n) : name(n), deptCount(0) {
        for (int i = 0; i < 10; i++) departments[i] = nullptr;
    }

    ~University() {
        for (int i = 0; i < deptCount; i++) {
            delete departments[i];
        }
    }

    void addDepartment(string deptName, int faculty) {
        if (deptCount >= 10) {
            cout << "Cannot add more departments." << endl;
            return;
        }
        departments[deptCount++] = new Department(deptName, faculty);
    }

    void display() const {
        cout << "\nUniversity: " << name << endl;
        cout << "Departments (" << deptCount << "):\n";
        for (int i = 0; i < deptCount; i++) {
            departments[i]->display();
        }
    }
};

/*
================================================================================
3. ADVANCED LEVEL - PIMPL Idiom, Read-only Interfaces,
                    Encapsulation with Smart Design
================================================================================
*/

// -----------------------------------------------------------------------------
// Example 6: PIMPL (Pointer to Implementation) Idiom
// -----------------------------------------------------------------------------
/*
PIMPL hides the complete implementation details from the header file.
Benefits:
- Binary compatibility (ABI stability)
- Reduced compilation dependencies
- Stronger encapsulation
- Faster compile times

Typically used in professional libraries.
*/

// Forward declaration
class WidgetImpl;

class Widget {
private:
    WidgetImpl* pImpl;      // opaque pointer to implementation

public:
    Widget();
    ~Widget();

    // Copy operations need special handling with PIMPL
    Widget(const Widget& other);
    Widget& operator=(const Widget& other);

    void doSomething();
    void setValue(int v);
    int getValue() const;
};

// Implementation would normally be in a .cpp file
class WidgetImpl {
public:
    int value;
    string internalData;
    // ... many private details not exposed in header

    WidgetImpl() : value(0), internalData("secret") {}
};

Widget::Widget() : pImpl(new WidgetImpl()) {}

Widget::~Widget() {
    delete pImpl;
}

Widget::Widget(const Widget& other) : pImpl(new WidgetImpl(*other.pImpl)) {}

Widget& Widget::operator=(const Widget& other) {
    if (this != &other) {
        *pImpl = *other.pImpl;
    }
    return *this;
}

void Widget::doSomething() {
    cout << "Widget doing something with value = " << pImpl->value << endl;
}

void Widget::setValue(int v) {
    pImpl->value = v;
}

int Widget::getValue() const {
    return pImpl->value;
}

// -----------------------------------------------------------------------------
// Example 7: Immutable Object Pattern (Strong Encapsulation)
// -----------------------------------------------------------------------------
/*
Once created, the object cannot be modified.
All members are private and there are no setters.
This is the strongest form of encapsulation for state.
*/

class ImmutablePoint {
private:
    const double x;
    const double y;

public:
    ImmutablePoint(double xVal, double yVal) : x(xVal), y(yVal) {}

    double getX() const { return x; }
    double getY() const { return y; }

    // Instead of modifying, return a new object
    ImmutablePoint translate(double dx, double dy) const {
        return ImmutablePoint(x + dx, y + dy);
    }

    ImmutablePoint scale(double factor) const {
        return ImmutablePoint(x * factor, y * factor);
    }

    void display() const {
        cout << "Point(" << x << ", " << y << ")" << endl;
    }
};

/*
================================================================================
4. BEST PRACTICES FOR ENCAPSULATION
================================================================================

1. Make data members private by default.
2. Provide public getters/setters only when necessary.
3. Prefer returning by value or const reference from getters.
4. Validate data in setters and constructors.
5. Maintain class invariants at all times.
6. Use const methods whenever a method does not modify state.
7. Prefer immutable objects when possible.
8. Hide complex implementation details (PIMPL when needed).
9. Don't expose internal containers directly (return copies or views).
10. Use friend sparingly — it breaks encapsulation.

================================================================================
5. DEMONSTRATION
================================================================================
*/

int main() {
    cout << "========== 1. BASIC ENCAPSULATION ==========\n";
    BankAccount acc("ACC1001", "Alice Johnson", 1000.0);
    acc.display();

    acc.deposit(500);
    acc.withdraw(200);
    acc.withdraw(2000);     // should fail

    // acc.balance = 999999; // ERROR: balance is private
    cout << "Current balance via getter: $" << acc.getBalance() << endl;
    cout << "Total accounts: " << BankAccount::getTotalAccounts() << endl;

    cout << "\n========== 2. CONST CORRECTNESS & MUTABLE ==========\n";
    Temperature temp(25.0);
    cout << "Celsius: " << temp.getCelsius() << endl;
    cout << "Fahrenheit: " << temp.getFahrenheit() << endl;
    cout << "Access count: " << temp.getAccessCount() << endl;

    const Temperature frozen(-10.0);
    // frozen.setCelsius(0);  // ERROR: cannot call non-const on const object
    cout << "Frozen temp: " << frozen.getCelsius() << " C" << endl;

    cout << "\n========== 3. VALIDATION & INVARIANTS ==========\n";
    try {
        Student s1("Bob Smith", 20, 3.7f, "S12345");
        s1.display();

        // s1.setGPA(5.0);  // would throw
        s1.setGPA(3.9f);
        s1.display();
    }
    catch (const invalid_argument& e) {
        cout << "Exception: " << e.what() << endl;
    }

    cout << "\n========== 4. NESTED CLASS ==========\n";
    University uni("Tech University");
    uni.addDepartment("Computer Science", 25);
    uni.addDepartment("Electrical Engineering", 18);
    uni.addDepartment("Mathematics", 12);
    uni.display();

    cout << "\n========== 5. PIMPL IDIOM ==========\n";
    Widget w;
    w.setValue(42);
    w.doSomething();
    cout << "Value: " << w.getValue() << endl;

    cout << "\n========== 6. IMMUTABLE OBJECT ==========\n";
    ImmutablePoint p1(3.0, 4.0);
    p1.display();

    ImmutablePoint p2 = p1.translate(1.0, 2.0);
    p2.display();

    ImmutablePoint p3 = p1.scale(2.0);
    p3.display();

    // p1.x = 10;  // ERROR: x is private and const

    cout << "\n========== PROGRAM END ==========\n";
    return 0;
}

/*
================================================================================
SUMMARY
================================================================================

Encapsulation = Data Hiding + Controlled Access

Levels of Encapsulation Strength:
1. Public data          → Weakest (no encapsulation)
2. Private data + getters/setters → Basic
3. Private data + validated methods only → Strong
4. Immutable objects    → Strongest for state
5. PIMPL                → Maximum implementation hiding

Remember:
- Encapsulation is about protecting the integrity of the object.
- It allows you to change the internal representation freely.
- Good encapsulation leads to more robust and maintainable code.

================================================================================
*/
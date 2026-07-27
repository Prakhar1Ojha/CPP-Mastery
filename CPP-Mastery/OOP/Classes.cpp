/*
----------------------------------------
Topic : Classes & Objects
Difficulty : Easy
Time Complexity : O(1) per method call
Space Complexity : O(1) per object (plus member data)
Author : Prakhar Ojha
----------------------------------------
Concept:
A class bundles data (members) with the functions that operate
on it (methods). private members enforce encapsulation — outside
code can't touch them directly, only through public methods.
This is the foundation OOP concepts (inheritance, polymorphism)
build on.

Example:
Input : create Student("Prakhar", 21)
Output : Name: Prakhar, Age: 21
----------------------------------------
*/

#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int age;

public:
    // Constructor
    Student(string n, int a) {
        name = n;
        age = a;
    }

    void display() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }

    void setAge(int a) {
        if (a > 0) age = a; // basic validation, encapsulation in action
    }
};

int main() {
    Student s("Prakhar", 21);
    s.display();

    s.setAge(22);
    s.display();

    return 0;
}

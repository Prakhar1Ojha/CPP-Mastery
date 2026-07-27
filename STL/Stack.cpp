/*
================================================================================
                    std::stack IN C++ - COMPLETE GUIDE
              From Beginner to Advanced Level
================================================================================

std::stack is a container adapter that provides LIFO (Last-In-First-Out)
functionality.

Header: #include <stack>

By default, stack uses deque as its underlying container.
You can also use vector or list.

Key Characteristics:
- Only the top element is accessible
- push → add to top
- pop  → remove from top
- No iterators, no random access
- Simple and efficient for LIFO needs

When to use stack:
✓ Expression evaluation / parsing
✓ Undo functionality
✓ Backtracking algorithms
✓ DFS (Depth-First Search) implementation
✓ Function call simulation
✓ Matching parentheses / balanced symbols
✓ Next Greater Element problems

================================================================================
1. BEGINNER LEVEL - Basic Stack Operations
================================================================================
*/

#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main() {
    cout << "========== 1. BASIC STACK OPERATIONS ==========\n";

    stack<int> st;

    // push / emplace
    st.push(10);
    st.push(20);
    st.push(30);
    st.emplace(40);

    cout << "Size: " << st.size() << endl;
    cout << "Empty? " << (st.empty() ? "Yes" : "No") << endl;
    cout << "Top: " << st.top() << endl;

    // Processing (LIFO order)
    cout << "\nPopping all elements (LIFO):\n";
    while (!st.empty()) {
        cout << "  Top: " << st.top() << endl;
        st.pop();   // pop does NOT return the value
    }

    cout << "\n========== 2. STACK WITH STRINGS ==========\n";
    stack<string> history;
    history.push("google.com");
    history.push("github.com");
    history.push("stackoverflow.com");
    history.push("cppreference.com");

    cout << "Browser back simulation:\n";
    while (!history.empty()) {
        cout << "  Current page: " << history.top() << endl;
        history.pop();
        if (!history.empty())
            cout << "  ← Going back...\n";
    }

    /*
    ================================================================================
    2. INTERMEDIATE LEVEL - Practical Problems & Different Underlying Containers
    ================================================================================
    */

    cout << "\n========== 3. BALANCED PARENTHESES CHECKER ==========\n";
    auto isBalanced = [](const string& expr) -> bool {
        stack<char> s;
        for (char c : expr) {
            if (c == '(' || c == '{' || c == '[') {
                s.push(c);
            }
            else if (c == ')' || c == '}' || c == ']') {
                if (s.empty()) return false;
                char top = s.top();
                s.pop();
                if ((c == ')' && top != '(') ||
                    (c == '}' && top != '{') ||
                    (c == ']' && top != '[')) {
                    return false;
                }
            }
        }
        return s.empty();
    };

    vector<string> expressions = {
        "()",
        "()[]{}",
        "(]",
        "([)]",
        "{[]}",
        "(((",
        "(()())"
    };

    for (const string& e : expressions) {
        cout << "  \"" << e << "\" → " 
             << (isBalanced(e) ? "Balanced" : "Not Balanced") << endl;
    }

    cout << "\n========== 4. INFIX TO POSTFIX CONVERSION ==========\n";
    /*
    Classic stack application: Convert infix expression to postfix
    Example: A + B * C → A B C * +
    */
    auto precedence = [](char op) -> int {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        if (op == '^') return 3;
        return 0;
    };

    auto infixToPostfix = [&](const string& infix) -> string {
        stack<char> ops;
        string postfix;

        for (char c : infix) {
            if (isalnum(c)) {
                postfix += c;
            }
            else if (c == '(') {
                ops.push(c);
            }
            else if (c == ')') {
                while (!ops.empty() && ops.top() != '(') {
                    postfix += ops.top();
                    ops.pop();
                }
                if (!ops.empty()) ops.pop();  // remove '('
            }
            else {  // operator
                while (!ops.empty() && ops.top() != '(' &&
                       precedence(ops.top()) >= precedence(c)) {
                    postfix += ops.top();
                    ops.pop();
                }
                ops.push(c);
            }
        }
        while (!ops.empty()) {
            postfix += ops.top();
            ops.pop();
        }
        return postfix;
    };

    vector<string> infixExprs = {
        "A+B*C",
        "(A+B)*C",
        "A+B*C-D/E",
        "A*(B+C)/D"
    };

    for (const string& e : infixExprs) {
        cout << "  " << e << " → " << infixToPostfix(e) << endl;
    }

    cout << "\n========== 5. EVALUATE POSTFIX EXPRESSION ==========\n";
    auto evaluatePostfix = [](const string& postfix) -> int {
        stack<int> s;
        for (char c : postfix) {
            if (isdigit(c)) {
                s.push(c - '0');
            }
            else {
                int b = s.top(); s.pop();
                int a = s.top(); s.pop();
                switch (c) {
                    case '+': s.push(a + b); break;
                    case '-': s.push(a - b); break;
                    case '*': s.push(a * b); break;
                    case '/': s.push(a / b); break;
                }
            }
        }
        return s.top();
    };

    cout << "  23*45*+ → " << evaluatePostfix("23*45*+") << endl;  // 2*3 + 4*5 = 26
    cout << "  234*+  → " << evaluatePostfix("234*+") << endl;    // 2+3*4 = 14

    cout << "\n========== 6. STACK WITH DIFFERENT UNDERLYING CONTAINERS ==========\n";
    // Default: deque
    stack<int> defaultStack;

    // Using vector
    stack<int, vector<int>> vectorStack;
    vectorStack.push(1);
    vectorStack.push(2);
    cout << "vector-based stack top: " << vectorStack.top() << endl;

    // Using deque explicitly
    stack<int, deque<int>> dequeStack;
    dequeStack.push(10);
    cout << "deque-based stack top: " << dequeStack.top() << endl;

    /*
    ================================================================================
    3. ADVANCED LEVEL - Next Greater Element, Monotonic Stack, Two Stacks
    ================================================================================
    */

    cout << "\n========== 7. NEXT GREATER ELEMENT (Monotonic Stack) ==========\n";
    /*
    For each element, find the next greater element to its right.
    Classic monotonic stack problem.
    */
    vector<int> arr = {4, 5, 2, 10, 8};
    vector<int> nge(arr.size(), -1);
    stack<int> mono;   // stores indices

    for (int i = 0; i < (int)arr.size(); i++) {
        while (!mono.empty() && arr[mono.top()] < arr[i]) {
            nge[mono.top()] = arr[i];
            mono.pop();
        }
        mono.push(i);
    }

    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\nNext Greater: ";
    for (int x : nge) cout << x << " ";
    cout << endl;

    cout << "\n========== 8. IMPLEMENT QUEUE USING TWO STACKS ==========\n";
    class QueueUsingStacks {
        stack<int> s1, s2;  // s1 for push, s2 for pop

    public:
        void push(int x) {
            s1.push(x);
        }

        int pop() {
            if (s2.empty()) {
                while (!s1.empty()) {
                    s2.push(s1.top());
                    s1.pop();
                }
            }
            if (s2.empty()) throw runtime_error("Queue is empty");
            int val = s2.top();
            s2.pop();
            return val;
        }

        int front() {
            if (s2.empty()) {
                while (!s1.empty()) {
                    s2.push(s1.top());
                    s1.pop();
                }
            }
            if (s2.empty()) throw runtime_error("Queue is empty");
            return s2.top();
        }

        bool empty() const {
            return s1.empty() && s2.empty();
        }
    };

    QueueUsingStacks q;
    q.push(1);
    q.push(2);
    q.push(3);
    cout << "Front: " << q.front() << endl;
    cout << "Pop: " << q.pop() << endl;
    cout << "Pop: " << q.pop() << endl;
    q.push(4);
    cout << "Front: " << q.front() << endl;
    cout << "Pop: " << q.pop() << endl;
    cout << "Pop: " << q.pop() << endl;

    cout << "\n========== 9. BEST PRACTICES ==========\n";
    cout << R"(
1. stack is perfect for LIFO problems — don't reinvent it
2. Remember: pop() does not return value → use top() then pop()
3. No iterators — if you need to traverse, use the underlying container
4. Default underlying container (deque) is usually the best choice
5. For pure performance with only push/pop → vector as underlying can be faster
6. Monotonic stack is a powerful pattern for "next greater/smaller" problems
7. Two stacks can simulate a queue (and vice versa)
8. Always check empty() before calling top() or pop()

Common Interview Problems solvable with Stack:
- Valid Parentheses
- Min Stack (design a stack with O(1) min)
- Next Greater Element
- Largest Rectangle in Histogram
- Decode String
- Asteroid Collision
- Simplify Path (Unix path)
)" << endl;

    cout << "========== PROGRAM END ==========\n";
    return 0;
}

/*
================================================================================
COMPLEXITY SUMMARY
================================================================================

std::stack (adapter):
  push / emplace   : O(1)
  pop              : O(1)
  top              : O(1)
  size / empty     : O(1)

Underlying container choice:
  deque  → good all-rounder (default)
  vector → slightly faster, but may reallocate
  list   → no advantage for stack, more memory overhead

Note: stack does not provide iterators. If you need full access,
consider using the underlying container (vector/deque) directly.

================================================================================
*/
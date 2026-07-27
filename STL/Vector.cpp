/*
================================================================================
                    std::vector IN C++ - COMPLETE GUIDE
              From Beginner to Advanced Level
================================================================================

std::vector is a dynamic array that can grow and shrink at runtime.
It is the most commonly used container in the C++ Standard Template Library (STL).

Header: #include <vector>
Namespace: std

Key Characteristics:
- Contiguous memory storage (like arrays)
- Random access in O(1)
- Insertion/deletion at end is amortized O(1)
- Insertion/deletion in middle is O(n)
- Automatically manages memory

When to use vector:
✓ Need dynamic size
✓ Frequent access by index
✓ Mostly adding/removing at the end
✗ Frequent insertion/deletion at front or middle (prefer deque or list)

================================================================================
1. BEGINNER LEVEL - Creation, Access, Basic Operations
================================================================================
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>   // for sort, reverse, etc.
#include <numeric>     // for accumulate, iota
using namespace std;

void printVector(const vector<int>& v, const string& label = "") {
    if (!label.empty()) cout << label;
    cout << "[ ";
    for (int x : v) cout << x << " ";
    cout << "]" << endl;
}

int main() {
    cout << "========== 1. CREATING VECTORS ==========\n";

    // Empty vector
    vector<int> v1;
    cout << "Empty vector size: " << v1.size() << endl;

    // Vector with size (default initialized to 0)
    vector<int> v2(5);
    printVector(v2, "Size 5 (zeros): ");

    // Vector with size and initial value
    vector<int> v3(5, 100);
    printVector(v3, "Size 5 filled with 100: ");

    // Vector from initializer list (C++11)
    vector<int> v4 = {10, 20, 30, 40, 50};
    printVector(v4, "Initializer list: ");

    // Copy constructor
    vector<int> v5(v4);
    printVector(v5, "Copied from v4: ");

    // From another range
    vector<int> v6(v4.begin() + 1, v4.end() - 1);
    printVector(v6, "From range [1, end-1): ");

    cout << "\n========== 2. ACCESSING ELEMENTS ==========\n";
    vector<int> nums = {10, 20, 30, 40, 50};

    // operator[] - NO bounds checking (fast)
    cout << "nums[2] = " << nums[2] << endl;

    // at() - WITH bounds checking (throws out_of_range)
    cout << "nums.at(2) = " << nums.at(2) << endl;
    try {
        cout << nums.at(10) << endl;
    } catch (const out_of_range& e) {
        cout << "Exception: " << e.what() << endl;
    }

    // front() and back()
    cout << "front() = " << nums.front() << ", back() = " << nums.back() << endl;

    // data() - pointer to underlying array
    int* ptr = nums.data();
    cout << "data()[0] = " << ptr[0] << endl;

    cout << "\n========== 3. ADDING & REMOVING ELEMENTS ==========\n";
    vector<int> v;

    // push_back - add at end
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    printVector(v, "After push_back: ");

    // emplace_back - constructs in-place (more efficient for complex types)
    v.emplace_back(40);
    printVector(v, "After emplace_back: ");

    // insert - insert at specific position
    v.insert(v.begin() + 1, 15);           // insert single value
    printVector(v, "After insert 15 at index 1: ");

    v.insert(v.begin() + 2, 3, 99);        // insert 3 copies of 99
    printVector(v, "After insert 3x99: ");

    // pop_back - remove last element
    v.pop_back();
    printVector(v, "After pop_back: ");

    // erase - remove element(s)
    v.erase(v.begin() + 1);                // erase single
    printVector(v, "After erase index 1: ");

    v.erase(v.begin() + 1, v.begin() + 4); // erase range
    printVector(v, "After erase range: ");

    // clear - remove all
    v.clear();
    cout << "After clear, size = " << v.size() << ", empty? " 
         << (v.empty() ? "Yes" : "No") << endl;

    /*
    ================================================================================
    2. INTERMEDIATE LEVEL - Capacity, Iterators, Algorithms, 2D Vectors
    ================================================================================
    */

    cout << "\n========== 4. SIZE vs CAPACITY ==========\n";
    vector<int> capDemo;
    cout << "Initial: size=" << capDemo.size() 
         << ", capacity=" << capDemo.capacity() << endl;

    for (int i = 0; i < 10; i++) {
        capDemo.push_back(i);
        cout << "After push " << i << ": size=" << capDemo.size()
             << ", capacity=" << capDemo.capacity() << endl;
    }

    // reserve - pre-allocate capacity (avoids reallocations)
    vector<int> reserved;
    reserved.reserve(100);
    cout << "\nAfter reserve(100): size=" << reserved.size()
         << ", capacity=" << reserved.capacity() << endl;

    // shrink_to_fit - request to reduce capacity to size (C++11)
    reserved.push_back(1);
    reserved.shrink_to_fit();
    cout << "After shrink_to_fit: size=" << reserved.size()
         << ", capacity=" << reserved.capacity() << endl;

    // resize
    vector<int> resized = {1, 2, 3};
    resized.resize(5, 0);      // grow, fill with 0
    printVector(resized, "resize(5, 0): ");
    resized.resize(2);         // shrink
    printVector(resized, "resize(2): ");

    cout << "\n========== 5. ITERATORS ==========\n";
    vector<int> iterVec = {10, 20, 30, 40, 50};

    // Forward iteration
    cout << "Forward: ";
    for (auto it = iterVec.begin(); it != iterVec.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Reverse iteration
    cout << "Reverse: ";
    for (auto it = iterVec.rbegin(); it != iterVec.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Range-based for (C++11) - preferred
    cout << "Range-based: ";
    for (int x : iterVec) cout << x << " ";
    cout << endl;

    // Const iterators
    cout << "Const: ";
    for (auto it = iterVec.cbegin(); it != iterVec.cend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "\n========== 6. COMMON ALGORITHMS WITH VECTOR ==========\n";
    vector<int> algo = {5, 2, 8, 1, 9, 3, 7, 4, 6};

    // sort
    sort(algo.begin(), algo.end());
    printVector(algo, "Sorted ascending: ");

    sort(algo.begin(), algo.end(), greater<int>());
    printVector(algo, "Sorted descending: ");

    // reverse
    reverse(algo.begin(), algo.end());
    printVector(algo, "Reversed: ");

    // find
    auto it = find(algo.begin(), algo.end(), 7);
    if (it != algo.end()) {
        cout << "Found 7 at index: " << (it - algo.begin()) << endl;
    }

    // count
    algo.push_back(5);
    algo.push_back(5);
    cout << "Count of 5: " << count(algo.begin(), algo.end(), 5) << endl;

    // accumulate (sum)
    int sum = accumulate(algo.begin(), algo.end(), 0);
    cout << "Sum: " << sum << endl;

    // min/max element
    cout << "Min: " << *min_element(algo.begin(), algo.end()) << endl;
    cout << "Max: " << *max_element(algo.begin(), algo.end()) << endl;

    cout << "\n========== 7. 2D VECTORS (Matrix) ==========\n";
    // Method 1: vector of vectors
    vector<vector<int>> matrix(3, vector<int>(4, 0));  // 3x4 matrix of zeros

    // Fill with values
    int val = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = val++;
        }
    }

    cout << "3x4 Matrix:\n";
    for (const auto& row : matrix) {
        for (int x : row) cout << x << "\t";
        cout << endl;
    }

    // Jagged array (rows of different sizes)
    vector<vector<int>> jagged = {
        {1, 2},
        {3, 4, 5, 6},
        {7}
    };
    cout << "\nJagged array:\n";
    for (const auto& row : jagged) {
        for (int x : row) cout << x << " ";
        cout << endl;
    }

    /*
    ================================================================================
    3. ADVANCED LEVEL - Custom Types, move, emplace, Performance Tips
    ================================================================================
    */

    cout << "\n========== 8. VECTOR OF CUSTOM TYPES ==========\n";
    struct Person {
        string name;
        int age;

        Person(string n, int a) : name(n), age(a) {
            cout << "  Constructed: " << name << endl;
        }

        // Move constructor
        Person(Person&& other) noexcept : name(move(other.name)), age(other.age) {
            cout << "  Move constructed: " << name << endl;
        }

        // Copy constructor
        Person(const Person& other) : name(other.name), age(other.age) {
            cout << "  Copy constructed: " << name << endl;
        }
    };

    vector<Person> people;
    people.reserve(3);   // avoid reallocation (important!)

    cout << "Using push_back (may copy):\n";
    people.push_back(Person("Alice", 25));   // temporary → move

    cout << "\nUsing emplace_back (constructs in-place):\n";
    people.emplace_back("Bob", 30);          // no temporary

    people.emplace_back("Charlie", 35);

    cout << "\nPeople in vector:\n";
    for (const auto& p : people) {
        cout << "  " << p.name << ", " << p.age << endl;
    }

    cout << "\n========== 9. IMPORTANT METHODS SUMMARY ==========\n";
    vector<int> demo = {1, 2, 3, 4, 5};

    cout << "size()      = " << demo.size() << endl;
    cout << "capacity()  = " << demo.capacity() << endl;
    cout << "max_size()  = " << demo.max_size() << endl;
    cout << "empty()     = " << demo.empty() << endl;

    // assign
    demo.assign(3, 7);   // replace with 3 sevens
    printVector(demo, "assign(3, 7): ");

    // swap
    vector<int> other = {100, 200};
    demo.swap(other);
    printVector(demo, "After swap: ");
    printVector(other, "other after swap: ");

    cout << "\n========== 10. PERFORMANCE TIPS ==========\n";
    cout << R"(
1. Prefer push_back / emplace_back over insert at front/middle
2. Use reserve() when you know approximate size → avoids reallocations
3. Prefer emplace_back over push_back for complex objects
4. Use shrink_to_fit() only when you really need to free memory
5. Pass vectors by const reference to functions (avoid copies)
6. For frequent front insertion → use deque or list instead
7. vector<bool> is specialized (bit-packed) → has quirks, avoid if possible
8. Clear + shrink_to_fit to fully release memory:
      v.clear();
      v.shrink_to_fit();
)" << endl;

    cout << "========== PROGRAM END ==========\n";
    return 0;
}

/*
================================================================================
COMPLEXITY CHEAT SHEET
================================================================================

Operation              | Time Complexity      | Notes
-----------------------|----------------------|---------------------------
Access [i] / at(i)     | O(1)                 | Random access
front() / back()       | O(1)                 |
push_back()            | Amortized O(1)       | May reallocate
pop_back()             | O(1)                 |
insert() middle        | O(n)                 | Shifts elements
erase() middle         | O(n)                 | Shifts elements
find (linear)          | O(n)                 |
sort                   | O(n log n)           |
size() / empty()       | O(1)                 |
reserve()              | O(n) if grows        | Reallocation

Memory: Contiguous → Cache friendly → Usually fastest container for iteration

================================================================================
*/

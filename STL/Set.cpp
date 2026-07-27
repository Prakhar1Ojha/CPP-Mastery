/*
================================================================================
                    std::set, std::multiset, unordered_set 
                         COMPLETE GUIDE
              From Beginner to Advanced Level
================================================================================

set             → Ordered unique elements (Red-Black Tree)
multiset        → Ordered, allows duplicates
unordered_set   → Hash-based unique elements (C++11)
unordered_multiset → Hash-based, allows duplicates

Header:
  #include <set>
  #include <unordered_set>

Key Differences:
┌──────────────────┬──────────────┬────────────────────┐
│ Feature          │ set          │ unordered_set      │
├──────────────────┼──────────────┼────────────────────┤
│ Order            │ Sorted       │ No order           │
│ Uniqueness       │ Yes          │ Yes                │
│ Underlying       │ RB-Tree      │ Hash Table         │
│ Insert/Find/Erase│ O(log n)     │ Avg O(1)           │
│ Custom order     │ Comparator   │ Hash + Equality    │
└──────────────────┴──────────────┴────────────────────┘

Use set when: You need unique sorted elements
Use unordered_set when: You need fast unique lookup, order doesn't matter

================================================================================
1. BEGINNER LEVEL - std::set Basics
================================================================================
*/

#include <iostream>
#include <set>
#include <unordered_set>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
void printSet(const T& s, const string& label = "") {
    if (!label.empty()) cout << label;
    cout << "{ ";
    for (const auto& x : s) cout << x << " ";
    cout << "}" << endl;
}

int main() {
    cout << "========== 1. CREATING AND INSERTING ==========\n";

    set<int> s;

    // insert returns pair<iterator, bool>
    auto result = s.insert(30);
    cout << "Inserted 30? " << (result.second ? "Yes" : "No") << endl;

    s.insert(10);
    s.insert(20);
    s.insert(50);
    s.insert(40);
    s.insert(20);   // duplicate - ignored

    printSet(s, "Set (sorted unique): ");

    // Initializer list
    set<string> names = {"Zoe", "Alice", "Bob", "Alice", "Charlie"};
    printSet(names, "Names set: ");

    // insert range
    vector<int> vec = {5, 15, 25, 10};
    s.insert(vec.begin(), vec.end());
    printSet(s, "After inserting vector: ");

    // emplace
    s.emplace(35);
    printSet(s, "After emplace 35: ");

    cout << "\n========== 2. ACCESSING & SEARCHING ==========\n";
    // Sets do NOT support operator[] or at()
    // Access only via iterators or find/count

    auto it = s.find(20);
    if (it != s.end()) {
        cout << "Found: " << *it << endl;
    }

    cout << "Count of 20: " << s.count(20) << endl;   // 0 or 1
    cout << "Count of 99: " << s.count(99) << endl;

    // lower_bound / upper_bound
    auto lb = s.lower_bound(20);   // first >= 20
    auto ub = s.upper_bound(20);   // first > 20
    cout << "lower_bound(20): " << *lb << endl;
    cout << "upper_bound(20): " << *ub << endl;

    // equal_range
    auto range = s.equal_range(20);
    cout << "equal_range(20): [" << *range.first << ", " << *range.second << ")" << endl;

    cout << "\n========== 3. DELETING ELEMENTS ==========\n";
    s.erase(20);                    // erase by value
    printSet(s, "After erase 20: ");

    s.erase(s.find(30));            // erase by iterator
    printSet(s, "After erase 30: ");

    // erase range
    s.erase(s.lower_bound(10), s.upper_bound(25));
    printSet(s, "After erase range [10,25]: ");

    s.clear();
    cout << "After clear, size = " << s.size() << endl;

    /*
    ================================================================================
    2. INTERMEDIATE LEVEL - Multiset, Custom Comparator, Set Operations
    ================================================================================
    */

    cout << "\n========== 4. std::multiset (Duplicates Allowed) ==========\n";
    multiset<int> ms = {5, 2, 8, 2, 5, 1, 5, 3};
    printSet(ms, "Multiset: ");

    cout << "Count of 5: " << ms.count(5) << endl;

    // equal_range for all occurrences
    auto eq = ms.equal_range(5);
    cout << "All 5s: ";
    for (auto it = eq.first; it != eq.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // erase all occurrences of a value
    ms.erase(5);
    printSet(ms, "After erase all 5s: ");

    // To erase only one occurrence:
    multiset<int> ms2 = {1, 2, 2, 2, 3};
    auto it2 = ms2.find(2);
    if (it2 != ms2.end()) ms2.erase(it2);   // erases only one
    printSet(ms2, "After erasing one 2: ");

    cout << "\n========== 5. CUSTOM COMPARATOR ==========\n";
    // Descending order
    set<int, greater<int>> desc = {5, 1, 8, 3, 2};
    printSet(desc, "Descending set: ");

    // Custom: sort strings by length
    auto lenCmp = [](const string& a, const string& b) {
        if (a.length() != b.length())
            return a.length() < b.length();
        return a < b;   // same length → alphabetical
    };
    set<string, decltype(lenCmp)> byLen(lenCmp);
    byLen.insert({"apple", "fig", "banana", "kiwi", "pear", "a"});
    printSet(byLen, "Sorted by length: ");

    cout << "\n========== 6. SET OPERATIONS (Algorithms) ==========\n";
    set<int> A = {1, 2, 3, 4, 5, 6};
    set<int> B = {4, 5, 6, 7, 8, 9};

    // Union
    set<int> unionSet;
    set_union(A.begin(), A.end(), B.begin(), B.end(),
              inserter(unionSet, unionSet.begin()));
    printSet(unionSet, "A ∪ B: ");

    // Intersection
    set<int> interSet;
    set_intersection(A.begin(), A.end(), B.begin(), B.end(),
                     inserter(interSet, interSet.begin()));
    printSet(interSet, "A ∩ B: ");

    // Difference (A - B)
    set<int> diffSet;
    set_difference(A.begin(), A.end(), B.begin(), B.end(),
                   inserter(diffSet, diffSet.begin()));
    printSet(diffSet, "A - B: ");

    // Symmetric difference (A △ B)
    set<int> symDiff;
    set_symmetric_difference(A.begin(), A.end(), B.begin(), B.end(),
                             inserter(symDiff, symDiff.begin()));
    printSet(symDiff, "A △ B: ");

    // includes - is B subset of A?
    set<int> C = {2, 4, 6};
    cout << "Is C subset of A? " 
         << (includes(A.begin(), A.end(), C.begin(), C.end()) ? "Yes" : "No") << endl;

    /*
    ================================================================================
    3. ADVANCED LEVEL - unordered_set, Custom Hash, Practical Uses
    ================================================================================
    */

    cout << "\n========== 7. std::unordered_set ==========\n";
    unordered_set<string> uset = {"apple", "banana", "cherry", "apple"};
    printSet(uset, "Unordered set: ");

    uset.insert("date");
    uset.emplace("elderberry");

    if (uset.find("banana") != uset.end()) {
        cout << "banana exists" << endl;
    }

    cout << "Bucket count: " << uset.bucket_count() << endl;
    cout << "Load factor: " << uset.load_factor() << endl;

    // Practical: remove duplicates from vector
    vector<int> numbers = {1, 2, 3, 2, 4, 1, 5, 3, 6};
    unordered_set<int> unique(numbers.begin(), numbers.end());
    numbers.assign(unique.begin(), unique.end());
    cout << "Unique numbers: ";
    for (int x : numbers) cout << x << " ";
    cout << endl;

    cout << "\n========== 8. CUSTOM TYPE WITH unordered_set ==========\n";
    struct Point {
        int x, y;
        bool operator==(const Point& o) const {
            return x == o.x && y == o.y;
        }
    };

    struct PointHash {
        size_t operator()(const Point& p) const {
            return hash<int>()(p.x) * 31 + hash<int>()(p.y);
        }
    };

    unordered_set<Point, PointHash> points;
    points.insert({0, 0});
    points.insert({1, 2});
    points.insert({0, 0});   // duplicate ignored
    points.insert({3, 4});

    cout << "Points in unordered_set:\n";
    for (const auto& p : points) {
        cout << "  (" << p.x << ", " << p.y << ")\n";
    }

    cout << "\n========== 9. PRACTICAL USE CASES ==========\n";

    // 1. Fast membership testing
    unordered_set<int> allowed = {1, 3, 5, 7, 9};
    int query = 5;
    cout << query << " is allowed? " 
         << (allowed.count(query) ? "Yes" : "No") << endl;

    // 2. Finding duplicates in array
    vector<int> arr = {1, 2, 3, 4, 2, 5, 6, 3};
    unordered_set<int> seen;
    cout << "Duplicates: ";
    for (int x : arr) {
        if (seen.count(x)) cout << x << " ";
        else seen.insert(x);
    }
    cout << endl;

    // 3. Ordered unique elements from stream
    set<int> orderedUnique = {9, 1, 5, 3, 1, 7, 5};
    printSet(orderedUnique, "Ordered unique: ");

    cout << "\n========== 10. BEST PRACTICES ==========\n";
    cout << R"(
1. Use set when you need sorted unique elements
2. Use unordered_set for fastest unique membership testing
3. Use multiset when you need sorted elements with duplicates
4. Elements in set are const — you cannot modify them in-place
   (erase + insert if you need to "change" a value)
5. Prefer emplace over insert for complex types
6. For custom types in set → provide operator< or comparator
7. For custom types in unordered_set → provide hash + equality
8. set iterators are bidirectional; unordered_set are forward only
9. Never modify the key/value while iterating (undefined behavior)
10. Prefer count()/find() over iterating to check existence
)" << endl;

    cout << "========== PROGRAM END ==========\n";
    return 0;
}

/*
================================================================================
COMPLEXITY SUMMARY
================================================================================

std::set / multiset:
  Insert / Erase / Find   : O(log n)
  Iterate                 : O(n)
  lower_bound / upper_bound : O(log n)

std::unordered_set / unordered_multiset:
  Insert / Erase / Find   : Average O(1), Worst O(n)
  Iterate                 : O(n)

Memory: set has less overhead per element than unordered_set (no buckets)

Common Patterns:
- Remove duplicates → insert into set/unordered_set then copy back
- Frequency counting → map or unordered_map (not set)
- Sorted unique collection → set
- Fast "have I seen this?" → unordered_set

================================================================================
*/
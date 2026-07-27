/*
================================================================================
                    std::map & std::unordered_map IN C++ 
                         COMPLETE GUIDE
              From Beginner to Advanced Level
================================================================================

map             → Ordered associative container (Red-Black Tree)
unordered_map   → Hash table based (C++11)

Header:
  #include <map>
  #include <unordered_map>

Key Differences:
┌─────────────────────┬──────────────────────┬────────────────────────┐
│ Feature             │ std::map             │ std::unordered_map     │
├─────────────────────┼──────────────────────┼────────────────────────┤
│ Ordering            │ Sorted by key        │ No order               │
│ Underlying          │ Red-Black Tree       │ Hash Table             │
│ Search/Insert/Delete│ O(log n)             │ Average O(1), Worst O(n)│
│ Key requirement     │ operator< or Compare │ Hash + equality        │
│ Memory              │ Less overhead        │ More (buckets)         │
│ Iterator validity   │ Stable               │ May invalidate on rehash│
└─────────────────────┴──────────────────────┴────────────────────────┘

Use map when: You need sorted order or ordered traversal
Use unordered_map when: You need maximum speed and don't care about order

================================================================================
1. BEGINNER LEVEL - std::map Basics
================================================================================
*/

#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

int main() {
    cout << "========== 1. CREATING AND INSERTING ==========\n";

    map<string, int> age;

    // Method 1: operator[]
    age["Alice"] = 25;
    age["Bob"] = 30;
    age["Charlie"] = 22;

    // Method 2: insert with pair
    age.insert(pair<string, int>("Diana", 28));
    age.insert(make_pair("Eve", 35));

    // Method 3: insert with initializer (C++11)
    age.insert({"Frank", 40});

    // Method 4: emplace (constructs in-place, more efficient)
    age.emplace("Grace", 27);

    // Method 5: insert_or_assign (C++17) - insert or update
    age.insert_or_assign("Alice", 26);   // updates existing

    cout << "Map contents (sorted by key):\n";
    for (const auto& [name, years] : age) {   // structured binding C++17
        cout << "  " << name << " : " << years << endl;
    }

    cout << "\n========== 2. ACCESSING ELEMENTS ==========\n";

    // operator[] - creates default if key doesn't exist!
    cout << "age[\"Bob\"] = " << age["Bob"] << endl;
    cout << "age[\"Unknown\"] = " << age["Unknown"] << endl;  // inserts 0!

    // at() - throws if key not found (safer)
    try {
        cout << "age.at(\"Charlie\") = " << age.at("Charlie") << endl;
        cout << age.at("NotExist") << endl;
    } catch (const out_of_range& e) {
        cout << "Exception: " << e.what() << endl;
    }

    // find() - returns iterator
    auto it = age.find("Diana");
    if (it != age.end()) {
        cout << "Found Diana: " << it->second << endl;
    } else {
        cout << "Diana not found" << endl;
    }

    // count() - 0 or 1 for map (keys are unique)
    cout << "Count of 'Eve': " << age.count("Eve") << endl;
    cout << "Count of 'Zack': " << age.count("Zack") << endl;

    // contains() - C++20
    // cout << age.contains("Bob") << endl;

    cout << "\n========== 3. REMOVING ELEMENTS ==========\n";
    print_map:
    age.erase("Unknown");           // erase by key
    age.erase(age.find("Frank"));   // erase by iterator

    // erase range
    // age.erase(age.find("Bob"), age.find("Eve"));

    cout << "After erasures:\n";
    for (const auto& p : age) {
        cout << "  " << p.first << " : " << p.second << endl;
    }

    cout << "Size: " << age.size() << ", Empty? " << age.empty() << endl;

    /*
    ================================================================================
    2. INTERMEDIATE LEVEL - Custom Comparators, Multimap, Nested Maps
    ================================================================================
    */

    cout << "\n========== 4. CUSTOM COMPARATOR (Descending) ==========\n";
    // Greater comparator → keys in descending order
    map<int, string, greater<int>> descMap = {
        {1, "One"}, {5, "Five"}, {3, "Three"}, {2, "Two"}
    };

    cout << "Descending order map:\n";
    for (const auto& [k, v] : descMap) {
        cout << "  " << k << " → " << v << endl;
    }

    // Custom comparator with lambda (C++11)
    auto cmp = [](const string& a, const string& b) {
        return a.length() < b.length();   // sort by string length
    };
    map<string, int, decltype(cmp)> lengthMap(cmp);
    lengthMap["apple"] = 1;
    lengthMap["kiwi"] = 2;
    lengthMap["banana"] = 3;
    lengthMap["fig"] = 4;

    cout << "\nSorted by key length:\n";
    for (const auto& [k, v] : lengthMap) {
        cout << "  " << k << " (" << k.length() << ") → " << v << endl;
    }

    cout << "\n========== 5. std::multimap (Duplicate Keys Allowed) ==========\n";
    multimap<string, int> scores;
    scores.insert({"Alice", 85});
    scores.insert({"Bob", 90});
    scores.insert({"Alice", 92});   // duplicate key OK
    scores.insert({"Alice", 78});
    scores.insert({"Charlie", 88});

    cout << "All scores:\n";
    for (const auto& [name, score] : scores) {
        cout << "  " << name << " : " << score << endl;
    }

    // equal_range - get all values for a key
    cout << "\nAll scores of Alice:\n";
    auto range = scores.equal_range("Alice");
    for (auto it = range.first; it != range.second; ++it) {
        cout << "  " << it->second << endl;
    }

    cout << "\n========== 6. NESTED MAPS ==========\n";
    // map of map → like a 2D dictionary
    map<string, map<string, int>> studentMarks;

    studentMarks["Alice"]["Math"] = 95;
    studentMarks["Alice"]["Science"] = 88;
    studentMarks["Alice"]["English"] = 92;

    studentMarks["Bob"]["Math"] = 78;
    studentMarks["Bob"]["Science"] = 85;
    studentMarks["Bob"]["English"] = 80;

    cout << "Student Marks:\n";
    for (const auto& [student, subjects] : studentMarks) {
        cout << student << ":\n";
        for (const auto& [subject, marks] : subjects) {
            cout << "  " << subject << " : " << marks << endl;
        }
    }

    /*
    ================================================================================
    3. ADVANCED LEVEL - unordered_map, Custom Hash, Performance
    ================================================================================
    */

    cout << "\n========== 7. std::unordered_map (Hash Map) ==========\n";
    unordered_map<string, int> wordCount;

    string text = "the quick brown fox jumps over the lazy dog the fox";
    string word;
    for (char c : text) {
        if (c == ' ') {
            if (!word.empty()) {
                wordCount[word]++;
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) wordCount[word]++;

    cout << "Word frequencies:\n";
    for (const auto& [w, count] : wordCount) {
        cout << "  " << w << " : " << count << endl;
    }

    // Bucket interface
    cout << "\nBucket count: " << wordCount.bucket_count() << endl;
    cout << "Load factor: " << wordCount.load_factor() << endl;
    cout << "Max load factor: " << wordCount.max_load_factor() << endl;

    cout << "\n========== 8. CUSTOM KEY TYPE WITH unordered_map ==========\n";
    // For custom types you must provide:
    // 1. Hash function
    // 2. Equality comparison

    struct Point {
        int x, y;
        bool operator==(const Point& other) const {
            return x == other.x && y == other.y;
        }
    };

    // Custom hash
    struct PointHash {
        size_t operator()(const Point& p) const {
            return hash<int>()(p.x) ^ (hash<int>()(p.y) << 1);
        }
    };

    unordered_map<Point, string, PointHash> pointMap;
    pointMap[{0, 0}] = "Origin";
    pointMap[{1, 2}] = "Point A";
    pointMap[{3, 4}] = "Point B";

    cout << "Point map:\n";
    for (const auto& [pt, name] : pointMap) {
        cout << "  (" << pt.x << "," << pt.y << ") → " << name << endl;
    }

    cout << "\n========== 9. USEFUL MAP OPERATIONS ==========\n";
    map<int, string> m = {{1, "one"}, {2, "two"}, {3, "three"}, {5, "five"}};

    // lower_bound / upper_bound (only for ordered map)
    auto lb = m.lower_bound(3);   // first element not less than 3
    auto ub = m.upper_bound(3);   // first element greater than 3
    cout << "lower_bound(3): " << lb->first << " → " << lb->second << endl;
    cout << "upper_bound(3): " << ub->first << " → " << ub->second << endl;

    // equal_range
    auto eq = m.equal_range(3);
    cout << "equal_range(3): from " << eq.first->first 
         << " to " << eq.second->first << endl;

    cout << "\n========== 10. PERFORMANCE & BEST PRACTICES ==========\n";
    cout << R"(
map (ordered):
  ✓ Keys are always sorted
  ✓ lower_bound / upper_bound available
  ✓ Stable iterators
  ✗ O(log n) for most operations

unordered_map:
  ✓ Average O(1) lookup/insert/delete
  ✓ Best for pure key-value lookup speed
  ✗ No ordering
  ✗ Worst case O(n) if many hash collisions
  ✗ Iterators may invalidate on rehash

Best Practices:
1. Prefer unordered_map when order doesn't matter and speed is critical
2. Prefer map when you need sorted keys or range queries
3. Use emplace / try_emplace instead of operator[] when possible
4. Use at() when you expect the key to exist
5. For custom types in unordered_map → provide good hash function
6. Reserve buckets in unordered_map if you know approximate size:
      umap.reserve(1000);
7. map/unordered_map keys are const — you cannot modify them in-place
)" << endl;

    cout << "========== PROGRAM END ==========\n";
    return 0;
}

/*
================================================================================
COMPLEXITY SUMMARY
================================================================================

std::map / std::multimap (Red-Black Tree):
  Insert / Erase / Find     : O(log n)
  Iterate all               : O(n)
  lower_bound / upper_bound : O(log n)

std::unordered_map / unordered_multimap (Hash Table):
  Insert / Erase / Find     : Average O(1), Worst O(n)
  Iterate all               : O(n)
  No ordered operations

Memory overhead: unordered_map usually uses more memory due to buckets.

================================================================================
*/
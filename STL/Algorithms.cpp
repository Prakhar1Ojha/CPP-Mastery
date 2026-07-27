/*
================================================================================
                    STL ALGORITHMS IN C++ - COMPLETE GUIDE
              From Beginner to Advanced Level
================================================================================

The <algorithm> header provides a rich set of functions that operate on
ranges of elements (usually defined by iterators).

Header: #include <algorithm>
Also useful: #include <numeric>  (accumulate, iota, partial_sum, etc.)

Most algorithms take a range [first, last) — half-open interval.

Categories of Algorithms:
1. Non-modifying sequence operations (find, count, search...)
2. Modifying sequence operations (copy, transform, replace...)
3. Partitioning operations
4. Sorting operations
5. Binary search operations (on sorted ranges)
6. Set operations (on sorted ranges)
7. Heap operations
8. Min/max operations
9. Comparison operations
10. Numeric operations (<numeric>)

================================================================================
1. BEGINNER LEVEL - Essential Everyday Algorithms
================================================================================
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <functional>
#include <iterator>
using namespace std;

template <typename T>
void print(const T& container, const string& label = "") {
    if (!label.empty()) cout << label;
    for (const auto& x : container) cout << x << " ";
    cout << endl;
}

int main() {
    cout << "========== 1. SORTING ==========\n";
    vector<int> v = {5, 2, 8, 1, 9, 3, 7, 4, 6};

    // Ascending (default)
    sort(v.begin(), v.end());
    print(v, "sort ascending: ");

    // Descending
    sort(v.begin(), v.end(), greater<int>());
    print(v, "sort descending: ");

    // Partial sort - only top k elements sorted
    vector<int> v2 = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    partial_sort(v2.begin(), v2.begin() + 3, v2.end());
    print(v2, "partial_sort (top 3): ");

    // stable_sort - preserves relative order of equal elements
    vector<pair<int, string>> people = {
        {3, "Alice"}, {1, "Bob"}, {3, "Charlie"}, {2, "Diana"}
    };
    stable_sort(people.begin(), people.end(),
                [](const auto& a, const auto& b) { return a.first < b.first; });
    cout << "stable_sort by age: ";
    for (const auto& p : people) cout << "(" << p.first << "," << p.second << ") ";
    cout << endl;

    // is_sorted
    cout << "Is sorted? " << is_sorted(v.begin(), v.end(), greater<int>()) << endl;

    cout << "\n========== 2. SEARCHING ==========\n";
    vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // find - linear search
    auto it = find(data.begin(), data.end(), 7);
    if (it != data.end())
        cout << "find(7) at index: " << (it - data.begin()) << endl;

    // find_if - search with condition
    auto it2 = find_if(data.begin(), data.end(), [](int x) { return x > 5 && x % 2 == 0; });
    cout << "First even > 5: " << *it2 << endl;

    // binary_search - requires sorted range
    cout << "binary_search(6): " << binary_search(data.begin(), data.end(), 6) << endl;

    // lower_bound / upper_bound
    auto lb = lower_bound(data.begin(), data.end(), 6);  // first >= 6
    auto ub = upper_bound(data.begin(), data.end(), 6);  // first > 6
    cout << "lower_bound(6): index " << (lb - data.begin()) << endl;
    cout << "upper_bound(6): index " << (ub - data.begin()) << endl;

    // equal_range
    auto range = equal_range(data.begin(), data.end(), 6);
    cout << "equal_range(6): [" << (range.first - data.begin()) 
         << ", " << (range.second - data.begin()) << ")" << endl;

    cout << "\n========== 3. COUNTING & CHECKING ==========\n";
    vector<int> nums = {1, 2, 3, 2, 4, 2, 5, 2};

    cout << "count(2): " << count(nums.begin(), nums.end(), 2) << endl;
    cout << "count_if (even): " 
         << count_if(nums.begin(), nums.end(), [](int x) { return x % 2 == 0; }) << endl;

    cout << "all_of (>0): " << all_of(nums.begin(), nums.end(), [](int x) { return x > 0; }) << endl;
    cout << "any_of (>4): " << any_of(nums.begin(), nums.end(), [](int x) { return x > 4; }) << endl;
    cout << "none_of (<0): " << none_of(nums.begin(), nums.end(), [](int x) { return x < 0; }) << endl;

    cout << "\n========== 4. MIN / MAX ==========\n";
    vector<int> vals = {3, 1, 4, 1, 5, 9, 2, 6};

    cout << "min_element: " << *min_element(vals.begin(), vals.end()) << endl;
    cout << "max_element: " << *max_element(vals.begin(), vals.end()) << endl;

    auto [mn, mx] = minmax_element(vals.begin(), vals.end());
    cout << "minmax_element: " << *mn << " and " << *mx << endl;

    cout << "min(3, 7): " << min(3, 7) << endl;
    cout << "max(3, 7): " << max(3, 7) << endl;
    cout << "minmax(8, 2): " << minmax(8, 2).first << " " << minmax(8, 2).second << endl;

    /*
    ================================================================================
    2. INTERMEDIATE LEVEL - Transform, Replace, Partition, Heap, Permutations
    ================================================================================
    */

    cout << "\n========== 5. TRANSFORM & FOR_EACH ==========\n";
    vector<int> a = {1, 2, 3, 4, 5};
    vector<int> b(5);

    // Square each element
    transform(a.begin(), a.end(), b.begin(), [](int x) { return x * x; });
    print(b, "Squares: ");

    // Add two ranges
    vector<int> c = {10, 20, 30, 40, 50};
    transform(a.begin(), a.end(), c.begin(), b.begin(), plus<int>());
    print(b, "a + c: ");

    // for_each - apply function to each
    cout << "for_each print: ";
    for_each(a.begin(), a.end(), [](int x) { cout << x << " "; });
    cout << endl;

    cout << "\n========== 6. REPLACE, FILL, GENERATE ==========\n";
    vector<int> r = {1, 2, 0, 4, 0, 6, 0};
    replace(r.begin(), r.end(), 0, 99);
    print(r, "replace 0 with 99: ");

    replace_if(r.begin(), r.end(), [](int x) { return x > 50; }, -1);
    print(r, "replace_if >50 with -1: ");

    fill(r.begin(), r.begin() + 3, 7);
    print(r, "fill first 3 with 7: ");

    vector<int> gen(5);
    int n = 0;
    generate(gen.begin(), gen.end(), [&n]() { return n++; });
    print(gen, "generate 0..4: ");

    // iota (from <numeric>)
    vector<int> seq(6);
    iota(seq.begin(), seq.end(), 10);  // 10, 11, 12, 13, 14, 15
    print(seq, "iota from 10: ");

    cout << "\n========== 7. PARTITION ==========\n";
    vector<int> p = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto pivot = partition(p.begin(), p.end(), [](int x) { return x % 2 == 0; });
    print(p, "partition even/odd: ");
    cout << "Partition point index: " << (pivot - p.begin()) << endl;

    // stable_partition preserves relative order
    vector<int> sp = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    stable_partition(sp.begin(), sp.end(), [](int x) { return x % 2 == 0; });
    print(sp, "stable_partition: ");

    cout << "\n========== 8. HEAP OPERATIONS ==========\n";
    vector<int> h = {3, 1, 4, 1, 5, 9, 2, 6};
    make_heap(h.begin(), h.end());
    print(h, "make_heap: ");

    h.push_back(7);
    push_heap(h.begin(), h.end());
    print(h, "push_heap(7): ");

    pop_heap(h.begin(), h.end());
    cout << "pop_heap → max was: " << h.back() << endl;
    h.pop_back();
    print(h, "after pop_heap: ");

    sort_heap(h.begin(), h.end());
    print(h, "sort_heap: ");

    cout << "\n========== 9. PERMUTATIONS ==========\n";
    vector<int> perm = {1, 2, 3};
    cout << "All permutations of {1,2,3}:\n";
    do {
        cout << "  ";
        print(perm);
    } while (next_permutation(perm.begin(), perm.end()));

    /*
    ================================================================================
    3. ADVANCED LEVEL - Numeric, Set Algorithms, Custom Operations, C++17/20
    ================================================================================
    */

    cout << "\n========== 10. NUMERIC ALGORITHMS ==========\n";
    vector<int> nums2 = {1, 2, 3, 4, 5};

    cout << "accumulate (sum): " << accumulate(nums2.begin(), nums2.end(), 0) << endl;
    cout << "accumulate (product): " 
         << accumulate(nums2.begin(), nums2.end(), 1, multiplies<int>()) << endl;

    // partial_sum
    vector<int> psum(5);
    partial_sum(nums2.begin(), nums2.end(), psum.begin());
    print(psum, "partial_sum: ");

    // adjacent_difference
    vector<int> adiff(5);
    adjacent_difference(nums2.begin(), nums2.end(), adiff.begin());
    print(adiff, "adjacent_difference: ");

    // inner_product
    vector<int> x = {1, 2, 3};
    vector<int> y = {4, 5, 6};
    cout << "inner_product: " << inner_product(x.begin(), x.end(), y.begin(), 0) << endl;

    cout << "\n========== 11. SET ALGORITHMS (on sorted ranges) ==========\n";
    vector<int> A = {1, 2, 3, 4, 5, 6};
    vector<int> B = {4, 5, 6, 7, 8, 9};
    vector<int> result;

    set_union(A.begin(), A.end(), B.begin(), B.end(), back_inserter(result));
    print(result, "set_union: ");

    result.clear();
    set_intersection(A.begin(), A.end(), B.begin(), B.end(), back_inserter(result));
    print(result, "set_intersection: ");

    result.clear();
    set_difference(A.begin(), A.end(), B.begin(), B.end(), back_inserter(result));
    print(result, "set_difference (A-B): ");

    result.clear();
    set_symmetric_difference(A.begin(), A.end(), B.begin(), B.end(), back_inserter(result));
    print(result, "set_symmetric_difference: ");

    cout << "includes (is {2,4,6} subset of A)? " 
         << includes(A.begin(), A.end(), vector<int>{2,4,6}.begin(), vector<int>{2,4,6}.end()) << endl;

    cout << "\n========== 12. REMOVE-ERASE IDIOM ==========\n";
    /*
    Important pattern: remove doesn't actually erase elements from the container.
    It moves unwanted elements to the end and returns the new logical end.
    You must call erase afterwards.
    */
    vector<int> re = {1, 2, 3, 2, 4, 2, 5};
    print(re, "Before remove 2: ");

    auto newEnd = remove(re.begin(), re.end(), 2);
    print(re, "After remove (logical): ");
    cout << "Physical size still: " << re.size() << endl;

    re.erase(newEnd, re.end());   // actually erase
    print(re, "After erase: ");

    // remove_if
    vector<int> ri = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    ri.erase(remove_if(ri.begin(), ri.end(), [](int x) { return x % 2 == 0; }), ri.end());
    print(ri, "remove_if even: ");

    cout << "\n========== 13. UNIQUE & REVERSE & ROTATE ==========\n";
    vector<int> u = {1, 1, 2, 2, 2, 3, 3, 4, 5, 5};
    auto uniqEnd = unique(u.begin(), u.end());
    u.erase(uniqEnd, u.end());
    print(u, "unique: ");

    reverse(u.begin(), u.end());
    print(u, "reverse: ");

    vector<int> rot = {1, 2, 3, 4, 5};
    rotate(rot.begin(), rot.begin() + 2, rot.end());  // left rotate by 2
    print(rot, "rotate left by 2: ");

    cout << "\n========== 14. BEST PRACTICES & TIPS ==========\n";
    cout << R"(
1. Always ensure the range is valid: [first, last)
2. Most algorithms that "remove" need the erase-remove idiom
3. Binary search algorithms require sorted ranges
4. Set algorithms require both ranges to be sorted
5. Prefer algorithms over raw loops — clearer intent, fewer bugs
6. Use lambdas (C++11) for custom predicates/comparators
7. back_inserter is useful when the result size is unknown
8. For performance-critical code, know the complexity of each algorithm
9. C++20 ranges library (std::ranges::) provides better composability
10. Parallel algorithms available with execution policies (C++17):
    sort(execution::par, v.begin(), v.end());

Most Used Algorithms Cheat Sheet:
  sort / stable_sort / partial_sort
  find / find_if / binary_search / lower_bound
  count / count_if
  min_element / max_element
  transform / for_each
  copy / fill / generate
  remove / remove_if + erase
  unique + erase
  reverse / rotate
  accumulate / partial_sum
  next_permutation
  make_heap / push_heap / pop_heap
)" << endl;

    cout << "========== PROGRAM END ==========\n";
    return 0;
}

/*
================================================================================
COMPLEXITY QUICK REFERENCE (common algorithms)
================================================================================

sort                     O(n log n)
stable_sort              O(n log n)  (may use more memory)
partial_sort             O(n log k)
find / find_if           O(n)
binary_search            O(log n)    (sorted)
lower_bound/upper_bound  O(log n)    (sorted)
count / count_if         O(n)
min/max_element          O(n)
transform                O(n)
partition                O(n)
make_heap                O(n)
push/pop_heap            O(log n)
accumulate               O(n)
set_union etc.           O(n + m)    (sorted ranges)
next_permutation         O(n)

================================================================================
*/
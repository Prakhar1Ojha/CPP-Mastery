/*
================================================================================
                    std::priority_queue IN C++ - COMPLETE GUIDE
              From Beginner to Advanced Level
================================================================================

std::priority_queue is a container adapter that provides constant time
maximum (or minimum) element retrieval.

It is essentially a Max-Heap (by default) or Min-Heap.

Header: #include <queue>

Underlying container: vector (by default)
Comparison: less<T> (max-heap) by default

Key Characteristics:
- Largest element is always on top (max-heap)
- push → O(log n)
- pop  → O(log n)
- top  → O(1)
- No iterators, no random access
- Elements are not stored in fully sorted order — only heap order

When to use priority_queue:
✓ Dijkstra's algorithm
✓ Huffman coding
✓ Finding k largest / smallest elements
✓ Scheduling based on priority
✓ Merge k sorted lists
✓ Median maintenance (two heaps)

================================================================================
1. BEGINNER LEVEL - Basic Max-Heap & Min-Heap
================================================================================
*/

#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <functional>   // for greater<>
using namespace std;

int main() {
    cout << "========== 1. MAX-HEAP (Default priority_queue) ==========\n";

    priority_queue<int> maxHeap;

    maxHeap.push(30);
    maxHeap.push(10);
    maxHeap.push(50);
    maxHeap.push(20);
    maxHeap.emplace(40);

    cout << "Size: " << maxHeap.size() << endl;
    cout << "Top (maximum): " << maxHeap.top() << endl;

    cout << "Extracting all elements (descending):\n  ";
    while (!maxHeap.empty()) {
        cout << maxHeap.top() << " ";
        maxHeap.pop();
    }
    cout << endl;

    cout << "\n========== 2. MIN-HEAP ==========\n";
    // Use greater<T> as comparator
    priority_queue<int, vector<int>, greater<int>> minHeap;

    minHeap.push(30);
    minHeap.push(10);
    minHeap.push(50);
    minHeap.push(20);
    minHeap.push(40);

    cout << "Top (minimum): " << minHeap.top() << endl;

    cout << "Extracting all elements (ascending):\n  ";
    while (!minHeap.empty()) {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }
    cout << endl;

    cout << "\n========== 3. PRIORITY QUEUE WITH PAIRS ==========\n";
    // By default, compares first element, then second
    priority_queue<pair<int, string>> pq;

    pq.push({3, "Low"});
    pq.push({10, "High"});
    pq.push({5, "Medium"});
    pq.push({10, "Also High"});

    cout << "Priority tasks (higher number = higher priority):\n";
    while (!pq.empty()) {
        cout << "  Priority " << pq.top().first 
             << " → " << pq.top().second << endl;
        pq.pop();
    }

    /*
    ================================================================================
    2. INTERMEDIATE LEVEL - Custom Types, Custom Comparators, Practical Problems
    ================================================================================
    */

    cout << "\n========== 4. CUSTOM TYPE WITH OPERATOR OVERLOADING ==========\n";
    struct Patient {
        string name;
        int severity;   // higher = more urgent

        // Max-heap based on severity
        bool operator<(const Patient& other) const {
            return severity < other.severity;   // for max-heap
        }
    };

    priority_queue<Patient> emergency;

    emergency.push({"Alice", 3});
    emergency.push({"Bob", 8});
    emergency.push({"Charlie", 5});
    emergency.push({"Diana", 9});
    emergency.push({"Eve", 2});

    cout << "Treating patients by severity:\n";
    while (!emergency.empty()) {
        Patient p = emergency.top();
        emergency.pop();
        cout << "  Treating " << p.name 
             << " (severity " << p.severity << ")" << endl;
    }

    cout << "\n========== 5. CUSTOM COMPARATOR (Lambda / Functor) ==========\n";
    struct Task {
        string name;
        int priority;
        int duration;
    };

    // Comparator: higher priority first; if equal, shorter duration first
    auto cmp = [](const Task& a, const Task& b) {
        if (a.priority != b.priority)
            return a.priority < b.priority;   // max-heap on priority
        return a.duration > b.duration;       // min-heap on duration
    };

    priority_queue<Task, vector<Task>, decltype(cmp)> taskQueue(cmp);

    taskQueue.push({"Write report", 5, 60});
    taskQueue.push({"Fix bug", 8, 30});
    taskQueue.push({"Code review", 8, 45});
    taskQueue.push({"Meeting", 3, 30});
    taskQueue.push({"Deploy", 9, 20});

    cout << "Task execution order:\n";
    while (!taskQueue.empty()) {
        Task t = taskQueue.top();
        taskQueue.pop();
        cout << "  [P" << t.priority << "] " << t.name 
             << " (" << t.duration << " min)" << endl;
    }

    cout << "\n========== 6. K LARGEST ELEMENTS ==========\n";
    vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int k = 4;

    // Method: Use min-heap of size k
    priority_queue<int, vector<int>, greater<int>> kLargest;

    for (int num : numbers) {
        kLargest.push(num);
        if ((int)kLargest.size() > k) {
            kLargest.pop();   // remove smallest
        }
    }

    cout << k << " largest elements: ";
    vector<int> result;
    while (!kLargest.empty()) {
        result.push_back(kLargest.top());
        kLargest.pop();
    }
    // result is sorted ascending; reverse for descending
    for (auto it = result.rbegin(); it != result.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    /*
    ================================================================================
    3. ADVANCED LEVEL - Two Heaps for Median, Dijkstra idea, Performance
    ================================================================================
    */

    cout << "\n========== 7. FINDING MEDIAN USING TWO HEAPS ==========\n";
    /*
    Classic technique:
    - Max-heap for the lower half
    - Min-heap for the upper half
    - Keep sizes balanced
    */
    class MedianFinder {
        priority_queue<int> lower;                              // max-heap
        priority_queue<int, vector<int>, greater<int>> upper;   // min-heap

    public:
        void addNum(int num) {
            if (lower.empty() || num <= lower.top()) {
                lower.push(num);
            } else {
                upper.push(num);
            }

            // Balance
            if (lower.size() > upper.size() + 1) {
                upper.push(lower.top());
                lower.pop();
            } else if (upper.size() > lower.size()) {
                lower.push(upper.top());
                upper.pop();
            }
        }

        double findMedian() {
            if (lower.size() == upper.size()) {
                return (lower.top() + upper.top()) / 2.0;
            }
            return lower.top();
        }
    };

    MedianFinder mf;
    vector<int> stream = {5, 15, 1, 3, 8, 7, 9};
    for (int x : stream) {
        mf.addNum(x);
        cout << "  After inserting " << x 
             << ", median = " << mf.findMedian() << endl;
    }

    cout << "\n========== 8. MERGE K SORTED LISTS (Concept) ==========\n";
    /*
    Using min-heap of pairs: {value, {listIndex, elementIndex}}
    */
    vector<vector<int>> lists = {
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9}
    };

    using Node = pair<int, pair<int, int>>;  // {value, {listIdx, elemIdx}}
    priority_queue<Node, vector<Node>, greater<Node>> minH;

    // Initialize with first element of each list
    for (int i = 0; i < (int)lists.size(); i++) {
        if (!lists[i].empty()) {
            minH.push({lists[i][0], {i, 0}});
        }
    }

    vector<int> merged;
    while (!minH.empty()) {
        auto [val, idx] = minH.top();
        minH.pop();
        merged.push_back(val);

        int listIdx = idx.first;
        int elemIdx = idx.second;

        if (elemIdx + 1 < (int)lists[listIdx].size()) {
            minH.push({lists[listIdx][elemIdx + 1], {listIdx, elemIdx + 1}});
        }
    }

    cout << "Merged k sorted lists: ";
    for (int x : merged) cout << x << " ";
    cout << endl;

    cout << "\n========== 9. BEST PRACTICES ==========\n";
    cout << R"(
1. Default priority_queue is Max-Heap (largest on top)
2. For Min-Heap use: priority_queue<T, vector<T>, greater<T>>
3. For custom types:
   - Overload operator<  OR
   - Provide a custom comparator (functor / lambda)
4. push/emplace = O(log n), top = O(1), pop = O(log n)
5. No iterators — you cannot traverse without destroying the heap
6. To make a min-heap of pairs by second element, write custom comparator
7. For "k largest" → use min-heap of size k
8. For "k smallest" → use max-heap of size k
9. Two heaps (max + min) is the standard way to maintain running median
10. priority_queue does not support decrease-key efficiently
    (for Dijkstra with decrease-key, use set or custom heap)

Common Interview Problems:
- Kth Largest Element
- Top K Frequent Elements
- Merge K Sorted Lists
- Find Median from Data Stream
- Task Scheduler
- Ugly Number II
- Network Delay Time (Dijkstra)
)" << endl;

    cout << "========== PROGRAM END ==========\n";
    return 0;
}

/*
================================================================================
COMPLEXITY SUMMARY
================================================================================

std::priority_queue:
  push / emplace   : O(log n)
  pop              : O(log n)
  top              : O(1)
  size / empty     : O(1)

Underlying: vector (contiguous) → good cache performance
Comparison: less<T> by default → Max-Heap

Note: priority_queue is not stable regarding insertion order of equal elements.
It only guarantees the heap property (parent ≥ children for max-heap).

================================================================================
*/
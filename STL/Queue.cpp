/*
================================================================================
                    std::queue & std::deque IN C++ 
                         COMPLETE GUIDE
              From Beginner to Advanced Level
================================================================================

std::queue  → FIFO (First-In-First-Out) adapter
std::deque  → Double-Ended Queue (actual container)

Header:
  #include <queue>     // for queue, priority_queue
  #include <deque>

queue is a container adapter — by default it uses deque as underlying container.

Key Characteristics of queue:
- Elements are inserted at the back (push)
- Elements are removed from the front (pop)
- Only front and back can be accessed
- No iterators, no random access

When to use queue:
✓ BFS (Breadth-First Search)
✓ Task scheduling
✓ Print spooling
✓ Any FIFO processing

deque (Double-Ended Queue):
- Insert/delete from both ends in O(1)
- Random access in O(1)
- More flexible than vector for front operations
- Not contiguous memory (chunked)

================================================================================
1. BEGINNER LEVEL - std::queue Basics
================================================================================
*/

#include <iostream>
#include <queue>
#include <deque>
#include <string>
#include <vector>
using namespace std;

int main() {
    cout << "========== 1. BASIC QUEUE OPERATIONS ==========\n";

    queue<int> q;

    // push / emplace - add to back
    q.push(10);
    q.push(20);
    q.push(30);
    q.emplace(40);   // constructs in-place

    cout << "Size: " << q.size() << endl;
    cout << "Empty? " << (q.empty() ? "Yes" : "No") << endl;

    // front() - access front element
    // back()  - access back element
    cout << "Front: " << q.front() << endl;
    cout << "Back:  " << q.back() << endl;

    // pop - remove front (does NOT return the value!)
    cout << "\nProcessing queue (FIFO):\n";
    while (!q.empty()) {
        cout << "  Processing: " << q.front() << endl;
        q.pop();
    }
    cout << "Queue is now empty: " << q.empty() << endl;

    cout << "\n========== 2. QUEUE WITH CUSTOM TYPE ==========\n";
    queue<string> tasks;
    tasks.push("Write code");
    tasks.push("Review PR");
    tasks.push("Deploy");
    tasks.push("Monitor");

    cout << "Task queue:\n";
    while (!tasks.empty()) {
        cout << "  Doing: " << tasks.front() << endl;
        tasks.pop();
    }

    /*
    ================================================================================
    2. INTERMEDIATE LEVEL - deque (the real powerhouse)
    ================================================================================
    */

    cout << "\n========== 3. std::deque - Double Ended Queue ==========\n";
    deque<int> dq;

    // Insert at both ends
    dq.push_back(10);    // back
    dq.push_back(20);
    dq.push_front(5);    // front
    dq.push_front(1);
    dq.emplace_back(30);
    dq.emplace_front(0);

    cout << "Deque: ";
    for (int x : dq) cout << x << " ";
    cout << endl;

    // Access
    cout << "front: " << dq.front() << ", back: " << dq.back() << endl;
    cout << "dq[2] = " << dq[2] << endl;         // random access
    cout << "dq.at(3) = " << dq.at(3) << endl;

    // Remove from both ends
    dq.pop_front();
    dq.pop_back();
    cout << "After pop_front & pop_back: ";
    for (int x : dq) cout << x << " ";
    cout << endl;

    // Insert / erase in middle (less efficient)
    dq.insert(dq.begin() + 2, 99);
    cout << "After insert 99 at index 2: ";
    for (int x : dq) cout << x << " ";
    cout << endl;

    dq.erase(dq.begin() + 1);
    cout << "After erase index 1: ";
    for (int x : dq) cout << x << " ";
    cout << endl;

    cout << "\n========== 4. QUEUE WITH DIFFERENT UNDERLYING CONTAINER ==========\n";
    // queue can use list or deque (default is deque)
    queue<int, deque<int>> q1;
    // queue<int, list<int>> q2;   // also possible (need #include <list>)

    q1.push(100);
    q1.push(200);
    cout << "Custom underlying queue front: " << q1.front() << endl;

    cout << "\n========== 5. PRACTICAL EXAMPLE - BFS SIMULATION ==========\n";
    /*
    Simple graph BFS using queue
    Graph:
        0 → 1 → 3
        │   │
        ↓   ↓
        2 → 4
    */
    vector<vector<int>> graph = {
        {1, 2},    // 0 connected to 1, 2
        {3, 4},    // 1 connected to 3, 4
        {4},       // 2 connected to 4
        {},        // 3
        {}         // 4
    };

    vector<bool> visited(5, false);
    queue<int> bfs;

    int start = 0;
    bfs.push(start);
    visited[start] = true;

    cout << "BFS traversal starting from " << start << ": ";
    while (!bfs.empty()) {
        int node = bfs.front();
        bfs.pop();
        cout << node << " ";

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                bfs.push(neighbor);
            }
        }
    }
    cout << endl;

    /*
    ================================================================================
    3. ADVANCED LEVEL - Circular Buffer idea, Performance, Custom Queue
    ================================================================================
    */

    cout << "\n========== 6. DEQUE vs VECTOR for FRONT OPERATIONS ==========\n";
    cout << R"(
Operation          | vector          | deque
-------------------|-----------------|------------------
push_back          | Amortized O(1)  | O(1)
push_front         | O(n)            | O(1)
pop_back           | O(1)            | O(1)
pop_front          | O(n)            | O(1)
Random access [i]  | O(1)            | O(1)
Memory             | Contiguous      | Chunked (blocks)
Cache performance  | Excellent       | Good
Iterator validity  | Unstable on grow| More stable
)" << endl;

    cout << "========== 7. SIMULATING A SLIDING WINDOW WITH DEQUE ==========\n";
    /*
    Classic problem: Maximum of all subarrays of size k
    Using deque to maintain candidates for maximum
    */
    vector<int> arr = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    deque<int> window;   // stores indices
    vector<int> result;

    for (int i = 0; i < (int)arr.size(); i++) {
        // Remove elements outside current window
        while (!window.empty() && window.front() <= i - k) {
            window.pop_front();
        }

        // Remove smaller elements (they can never be max)
        while (!window.empty() && arr[window.back()] <= arr[i]) {
            window.pop_back();
        }

        window.push_back(i);

        // Window is fully formed
        if (i >= k - 1) {
            result.push_back(arr[window.front()]);
        }
    }

    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\nMax of each window of size " << k << ": ";
    for (int x : result) cout << x << " ";
    cout << endl;

    cout << "\n========== 8. BEST PRACTICES ==========\n";
    cout << R"(
queue:
1. Use for pure FIFO requirements
2. Remember: pop() does not return the value — use front() then pop()
3. No iterators — you cannot traverse without destroying the queue
4. Default underlying container is deque (good choice)

deque:
1. Prefer over vector when you need frequent push_front / pop_front
2. Prefer over list when you also need random access
3. Good middle ground between vector and list
4. Not the best for pure middle insertions (list is better)
5. Memory is allocated in chunks → slightly more overhead than vector

Common Patterns:
- BFS → queue
- Sliding window maximum/minimum → deque
- Undo/Redo or browser history → two stacks or deque
- Task scheduling → queue
)" << endl;

    cout << "========== PROGRAM END ==========\n";
    return 0;
}

/*
================================================================================
COMPLEXITY SUMMARY
================================================================================

std::queue (adapter):
  push / emplace   : O(1)
  pop              : O(1)
  front / back     : O(1)
  size / empty     : O(1)

std::deque:
  push_front/back  : O(1)
  pop_front/back   : O(1)
  operator[]       : O(1)
  insert/erase middle : O(n)

Note: queue does not support iteration. If you need to iterate,
use the underlying container (deque) directly or copy to another container.

================================================================================
*/
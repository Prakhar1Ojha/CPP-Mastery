/*
----------------------------------------
Topic : STL Vector
Difficulty : Easy
Time Complexity : push_back O(1) amortized, insert/erase O(n)
Space Complexity : O(n)
Author : Prakhar Ojha
----------------------------------------
Concept:
vector is a dynamic array: contiguous memory, automatic resizing
(doubles capacity when full, which is why push_back is amortized
O(1) rather than always O(1)). Prefer it over raw arrays whenever
size isn't fixed at compile time.

Why use vector?
- Dynamic size, resizes automatically
- Cache-friendly (contiguous memory) unlike list/deque
- Random access via [] is O(1)

Complexities:
push_back()  -> O(1) amortized
pop_back()   -> O(1)
insert(mid)  -> O(n) — shifts elements
erase(mid)   -> O(n) — shifts elements
operator[]   -> O(1)

Example:
Input : push 1,2,3, insert 10 at index 1
Output : 1 10 2 3
----------------------------------------
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    v.insert(v.begin() + 1, 10);

    for (int x : v) cout << x << " ";
    cout << endl;

    cout << "size: " << v.size() << ", capacity: " << v.capacity() << endl;

    v.pop_back();
    cout << "after pop_back, size: " << v.size() << endl;

    return 0;
}

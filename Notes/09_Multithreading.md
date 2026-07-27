# Multithreading

Modern C++ (C++11+) has first-class threading support via `<thread>`, `<mutex>`, `<atomic>`, and `<future>` — no need for platform-specific APIs (pthreads, WinAPI threads) for most use cases.

---

## 1. Creating Threads (Beginner)

```cpp
#include <thread>
using namespace std;

void printHello() { cout << "Hello from thread\n"; }

int main() {
    thread t(printHello);
    t.join(); // wait for t to finish before continuing
    return 0;
}
```
`join()` blocks the calling thread until `t` finishes. `detach()` lets `t` run independently in the background — but then you lose the ability to `join()` it later, and the program must ensure the thread finishes before `main()` exits or behavior is undefined.

Passing arguments:
```cpp
void greet(string name) { cout << "Hi " << name << "\n"; }
thread t(greet, "Prakhar");
t.join();
```

---

## 2. The Core Problem: Race Conditions (Beginner–Intermediate)

When two threads read/write shared data without coordination, the result depends on unpredictable timing — a **race condition**.

```cpp
int counter = 0;
void increment() {
    for (int i = 0; i < 100000; i++) counter++; // NOT atomic — read, add, write = 3 steps
}

thread t1(increment), t2(increment);
t1.join(); t2.join();
cout << counter; // expected 200000, but often LESS — increments get lost
```
`counter++` isn't one CPU instruction — it's read, add 1, write back. If two threads interleave those steps, one thread's increment can be overwritten by the other's stale read. This is the single most important concept in the whole topic to be able to explain clearly.

---

## 3. Mutex — Mutual Exclusion (Intermediate)

A mutex ensures only one thread can execute a critical section at a time.

```cpp
#include <mutex>
mutex mtx;
int counter = 0;

void increment() {
    for (int i = 0; i < 100000; i++) {
        mtx.lock();
        counter++;
        mtx.unlock();
    }
}
```

**Prefer `lock_guard`** over manual `lock()`/`unlock()` — it's RAII (ties back to Memory Management notes): the mutex is released automatically when `lock_guard` goes out of scope, even if an exception is thrown mid-section.

```cpp
void increment() {
    for (int i = 0; i < 100000; i++) {
        lock_guard<mutex> lock(mtx); // locks on construction, unlocks on destruction
        counter++;
    }
}
```

`unique_lock` is a more flexible alternative to `lock_guard` — supports deferred locking and manual unlock/relock, used with condition variables.

---

## 4. `atomic` — Lock-Free Alternative (Intermediate)

For simple operations (increment, flag toggling), `atomic<T>` avoids mutex overhead entirely by using hardware-level atomic instructions.

```cpp
#include <atomic>
atomic<int> counter(0);
void increment() {
    for (int i = 0; i < 100000; i++) counter++; // now genuinely atomic
}
```
Much faster than a mutex for simple counters, but only works for operations the hardware/library directly supports — for anything more complex than a single variable update, you're back to a mutex.

---

## 5. Deadlock (Intermediate–Advanced)

Occurs when two+ threads each hold a lock the other needs, and neither can proceed.

```cpp
mutex m1, m2;
void threadA() { lock_guard<mutex> l1(m1); lock_guard<mutex> l2(m2); /* ... */ }
void threadB() { lock_guard<mutex> l2(m2); lock_guard<mutex> l1(m1); /* ... */ } // opposite order!
```
If A locks `m1` and B locks `m2` at the same time, A then waits forever for `m2` (held by B) and B waits forever for `m1` (held by A). 

**Prevention**: always acquire multiple locks in a consistent, global order across all threads — or use `std::lock(m1, m2)` which locks multiple mutexes together, deadlock-free.

---

## 6. Condition Variables (Advanced)

Used when a thread needs to wait for a specific condition to become true (not just a lock to free up) — classic producer-consumer pattern.

```cpp
#include <condition_variable>
mutex mtx;
condition_variable cv;
queue<int> buffer;
bool ready = false;

void producer() {
    unique_lock<mutex> lock(mtx);
    buffer.push(42);
    ready = true;
    cv.notify_one(); // wake up a waiting thread
}

void consumer() {
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, [] { return ready; }); // sleeps until predicate is true, releasing the lock while waiting
    cout << buffer.front();
}
```
`cv.wait()` atomically releases the mutex while sleeping (so the producer can acquire it) and reacquires it before returning — this atomicity is exactly why you can't just do a manual `while(!ready) {}` spin loop safely without wasting CPU.

---

## 7. `async` / `future` — Higher-Level Concurrency (Advanced)

For "run this and get a result later" without manually managing threads:

```cpp
#include <future>
int computeSquare(int x) { return x * x; }

future<int> result = async(launch::async, computeSquare, 5);
cout << result.get(); // blocks until computeSquare finishes, then returns 25
```
`async` handles thread creation and result-passing for you — a cleaner abstraction than raw `thread` + shared variable + mutex when you just need "compute this in parallel and get the answer back."

---

## 8. Common Interview Questions

- Explain a race condition with a concrete example (the `counter++` one above is the canonical answer).
- Mutex vs atomic — when would you use each?
- What is a deadlock, and how do you prevent one?
- Why prefer `lock_guard` over manual `lock()`/`unlock()`? (RAII — exception safety)
- What's the difference between concurrency and parallelism? (Concurrency: multiple tasks make progress, possibly interleaved on one core. Parallelism: tasks literally execute simultaneously on multiple cores.)

# File Handling

C++ handles file I/O through the `<fstream>` library, built on the same stream abstraction as `cin`/`cout`.

---

## 1. The Three Stream Classes (Beginner)

| Class | Purpose |
|---|---|
| `ifstream` | Input file stream — reading from a file |
| `ofstream` | Output file stream — writing to a file |
| `fstream`  | Both read and write |

```cpp
#include <fstream>
using namespace std;

ofstream outFile("data.txt");
if (outFile.is_open()) {
    outFile << "Hello, file!\n";
    outFile.close();
}
```
**Always check `is_open()`** — a missing directory, permissions issue, or bad path fails silently otherwise (the stream just enters a "failed" state rather than throwing by default).

---

## 2. Reading From a File (Beginner)

```cpp
ifstream inFile("data.txt");
string line;
while (getline(inFile, line)) {
    cout << line << "\n";
}
inFile.close();
```

Reading token by token (like `cin >>`) instead of line by line:
```cpp
ifstream inFile("numbers.txt");
int x;
while (inFile >> x) {
    cout << x << " ";
}
```
`while (inFile >> x)` works because the stream extraction operator returns the stream itself, and a stream converts to `false` in a boolean context once it hits EOF or a read failure — a clean, idiomatic loop-until-exhausted pattern.

---

## 3. File Modes (Intermediate)

```cpp
ofstream f1("log.txt", ios::app);     // append instead of overwrite
ofstream f2("data.bin", ios::binary);  // binary mode, no text translation
fstream f3("data.txt", ios::in | ios::out); // read+write, combined with |
```

| Mode flag | Meaning |
|---|---|
| `ios::in` | Open for reading |
| `ios::out` | Open for writing (truncates by default) |
| `ios::app` | Append — writes go to the end, existing content preserved |
| `ios::trunc` | Truncate — clears existing content (default with `ios::out`) |
| `ios::binary` | Binary mode — no newline translation |
| `ios::ate` | Open and immediately seek to the end |

---

## 4. Binary File I/O (Intermediate–Advanced)

For raw data (not human-readable text), use `read`/`write` with pointers cast to `char*`:

```cpp
struct Record { int id; double value; };

Record r{1, 99.5};
ofstream out("records.bin", ios::binary);
out.write(reinterpret_cast<char*>(&r), sizeof(Record));
out.close();

Record loaded;
ifstream in("records.bin", ios::binary);
in.read(reinterpret_cast<char*>(&loaded), sizeof(Record));
```
Binary I/O is faster and more compact than text (no parsing/formatting overhead), but the file is no longer portable across platforms with different struct padding/endianness without extra care — a real interview trade-off to be able to articulate.

---

## 5. Error Handling (Intermediate)

```cpp
ifstream f("missing.txt");
if (!f) {
    cerr << "Failed to open file\n";
    return 1;
}
```
Stream state flags: `good()`, `eof()`, `fail()`, `bad()`. `fail()` covers recoverable errors (e.g. wrong-typed extraction); `bad()` means a serious, likely unrecoverable I/O error.

---

## 6. File Pointers (`seekg`/`seekp`) (Advanced)

```cpp
ifstream f("data.txt");
f.seekg(0, ios::end);   // move read pointer to end
streampos size = f.tellg(); // get current position = file size
f.seekg(0, ios::beg);    // back to start
```
`seekg` moves the **get** (read) pointer, `seekp` moves the **put** (write) pointer — necessary when random-accessing specific offsets in a large file rather than reading sequentially (e.g. implementing a simple key-value store on disk).

---

## 7. RAII and Files (ties back to Memory Management)

Streams follow RAII: `ofstream`'s destructor calls `close()` automatically if you forget to. Still, explicit `.close()` is good practice — it lets you check for flush/write errors at a well-defined point rather than relying on a destructor that can't report failure back to you.

---

## 8. Common Interview/Practical Notes

- Text mode vs binary mode differs mainly around newline translation (`\n` ↔ `\r\n` on Windows) — always open in `ios::binary` for non-text data to avoid silent corruption.
- Buffering: streams are buffered by default; `flush()` or `endl` (which flushes) forces a write to disk immediately — useful for logs you need visible right away, but `endl` in a tight loop is a common performance mistake (prefer `"\n"` and let the buffer flush naturally).

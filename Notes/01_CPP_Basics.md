# C++ Basics

## Why C++?

C++ gives you close-to-hardware control (manual memory management, pointers) while still supporting high-level abstractions (OOP, templates, STL). That combination is why it's still the default language for competitive programming and systems-level interviews.

## Compilation Model

C++ is compiled, not interpreted. Source (`.cpp`) → preprocessor → compiler → object files (`.o`) → linker → executable. Understanding this matters for debugging linker errors (`undefined reference`) vs compiler errors (syntax/type errors).

## Variables & Data Types

| Type | Typical Size | Notes |
|------|--------------|-------|
| `int` | 4 bytes | Platform-dependent, but 4 bytes on virtually all modern systems |
| `float` | 4 bytes | ~7 decimal digits precision |
| `double` | 8 bytes | ~15 decimal digits precision, default for floating point |
| `char` | 1 byte | Stores a single character or small integer |
| `bool` | 1 byte | `true` / `false` |

## `auto` and Type Deduction

`auto` lets the compiler infer the type from the initializer. Useful for iterators and long template types, but overusing it can hurt readability — prefer explicit types when the type isn't obvious from context.

## Input/Output

`cin`/`cout` are simpler to use than C's `scanf`/`printf` but slower by default. Adding `ios_base::sync_with_stdio(false); cin.tie(NULL);` at the start of `main()` disables syncing with C's stdio and speeds up I/O significantly — important in competitive programming with large inputs.

## Type Casting

- **Implicit**: compiler converts automatically (`int` → `double` in an expression).
- **Explicit**: `static_cast<T>(value)` — preferred over C-style casts `(T)value` because it's checked at compile time and clearly signals intent.

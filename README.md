# Cpp Data Structures

A collection of **header-only** C++ data structure implementations. No build
step, no linking against a compiled library - just copy the header(s) you
need into your project and `#include` them.

## Features

- Header-only - copy, paste, and go
- Templated (`template <typename T>`) - works with any type that supports
  default construction and assignment
- Zero external dependencies beyond the C++ standard library
- Optional debug logging via a `DEBUG` / `LOG(x)` macro toggle


## Header Files
1. `linkedlist.h`
2. `stack.h`
3. `sort.h`
4. `utils.h`

## Usage

Since everything is header-only, integration is a single step:

1. Copy the header file(s) you need into your project (e.g. `stack.h`).
2. `#include` it wherever you need it.
3. Compile as normal - no separate `.cpp` sources or linking required.

```cpp
#include "stack.h"

int main()
{
    Stack<int> stack(5);
    stack.push(10);
    stack.push(20);
    stack.traverse(); // 20 10
}
```

By default `DEBUG` is enabled (`1`) if not defined beforehand.

## Examples

Standalone usage examples for each data structure are provided as separate
`.cpp` files (e.g. `examples/stack.cpp`)
demonstrating construction, common operations, and edge cases like overflow
and underflow.

> **Note:** The code examples in this repository were generated with the
> assistance of **Claude Sonnet 5 (medium effort)**.

## License

MIT License. See the `LICENSE` file for details.

Copyright (c) 2026 Nimul Islam Mahin and contributors.
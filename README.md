# memory_pointer

A small C++ practice repository that implements custom pointer/data-structure utilities.

## Libraries

- `unique_pointer/uniquepointer.hpp` – basic move-only smart pointer.
- `shared_pointer/shared_pointer.hpp` – basic reference-counted smart pointer.
- `myvector/myvector.hpp` – custom dynamic array implementation.
- `mymatrix/mymatrix.hpp` – custom 2D matrix container.
- `mystack/mystack.hpp` – custom stack (LIFO) container (new).

## Tests

The repository contains simple executable tests:

- `unique_pointer/test_uniquepointer.cpp`
- `shared_pointer/test_shared.cpp`
- `mystack/test_mystack.cpp`

## Build and run

A root `Makefile` is provided.

```bash
make test
```

This compiles the test binaries in `bin/` and executes them.

To remove build artifacts:

```bash
make clean
```

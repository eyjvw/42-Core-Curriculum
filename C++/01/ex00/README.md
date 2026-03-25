# ex00 — Basic Class & Memory

Description

Introductory exercise demonstrating basic class creation, constructors/destructors,
and the difference between stack and heap allocation.

What you practice

- Defining a simple C++ class with constructor and destructor.
- Allocating objects on the stack vs `new` (heap) and observing lifetime.
- Simple member functions and output.

Files

- `includes/` — class headers
- `src/` — implementation files
- `Makefile` (uses `mk/` fragments) to build the binary.

Build & Run

```bash
make
./Zombie
```

Notes

- Inspect the constructors/destructors to understand order of operations and memory ownership.

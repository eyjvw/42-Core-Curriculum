# ex05 — Harl (Logger) Basics

Description

Implement a small logger `Harl` that exposes level-based handlers (DEBUG, INFO, WARNING, ERROR).
This exercise focuses on calling member functions based on a level string.

What you practice

- Declaring member functions and invoking them from another member.
- Simple string-based dispatch and control flow.
- Formatting console output.

Files

- `includes/Harl.hpp`, `src/Harl.cpp`
- `Makefile` to build the exercise

Build & Run

```bash
make
./Harl
```

Notes

- The dispatch can be implemented with function pointer arrays, maps, or switch logic.

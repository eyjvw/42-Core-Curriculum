# C++ — Module Week 02

*This project has been created as part of the 42 curriculum by sbonneau.*

This folder contains the C++ exercises for Week 02 (`ex00` → `ex03`).

## Description

These exercises focus on building a fixed-point number class progressively,
then using it in a geometry-oriented exercise.

## Exercises

- `ex00` — canonical form basics for `Fixed` class.
- `ex01` — conversions, arithmetic operators and stream output.
- `ex02` — full operator overload set (comparison, arithmetic, increment/decrement, min/max).
- `ex03` — `Point` and `bsp` function using fixed-point coordinates.

## Build

Requirements: Linux with a C++ compiler (`g++`/`c++`).

To build an exercise, change into its directory and run:

```bash
make
```

Makefile rules are standardized using shared `mk/` fragments (`variables.mk`, `colors.mk`, `rules.mk`).

## What you learn

- Orthodox Canonical Form in C++98
- Operator overloading and const-correctness
- Fixed-point arithmetic implementation details
- Reusing a consistent project structure across exercises

See each exercise folder for exercise-specific notes.

## Resources

- C++ reference (cppreference.com)
- 42 coding standards

## AI Usage

AI assistance was used to standardize Makefiles and README style across the repository.

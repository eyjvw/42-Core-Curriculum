# C++ — Module Week 03

*This project has been created as part of the 42 curriculum by sbonneau.*

This folder contains the C++ exercises for Week 03 (`ex00` → `ex03`).

## Description

This module introduces inheritance and polymorphism foundations through the
`ClapTrap` family (`ScavTrap`, `FragTrap`, `DiamondTrap`).

## Exercises

- `ex00` — base class `ClapTrap`.
- `ex01` — first inheritance step with `ScavTrap`.
- `ex02` — extended derived behavior with `FragTrap`.
- `ex03` — multiple inheritance and identity behavior with `DiamondTrap`.

## Build

Requirements: Linux with a C++ compiler (`g++`/`c++`).

To build an exercise, change into its directory and run:

```bash
make
```

Makefile rules are standardized using shared `mk/` fragments (`variables.mk`, `colors.mk`, `rules.mk`).

## What you learn

- Class inheritance in C++98
- Constructor/destructor chaining
- Method overriding and behavior specialization
- Multiple inheritance basics and ambiguity handling

See each exercise folder for exercise-specific notes.

## Resources

- C++ reference (cppreference.com)
- 42 coding standards

## AI Usage

AI assistance was used to standardize Makefiles and README style across the repository.

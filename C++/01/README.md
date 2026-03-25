# C++ — Module Week 01

This folder contains the C++ exercises for Week 01 (ex00 → ex06).

Description

These exercises continue the introduction to C++ with focus on object semantics,
references vs pointers, class design, and small practical utilities.

Exercises

- `ex00` — simple class & memory: basic class construction and stack vs heap usage.
- `ex01` — horde-style allocation: practice constructors/destructors and arrays of objects.
- `ex02` — Pointer vs Reference.
- `ex03` — `HumanA` / `HumanB` / `Weapon`: references vs pointers, ownership and interaction.
- `ex04` — Infile and Outfile.
- `ex05` — `Harl` logger (level-based handlers): member functions and dispatch.
- `ex06` — advanced `Harl`: level dispatch with controlled fall-through behavior.

Build

Requirements: Linux with a C++ compiler (`g++`/`c++`).

To build an exercise, change into its directory and run:

```bash
make
```

Makefile rules are standardized using shared `mk/` fragments (`variables.mk`, `colors.mk`, `rules.mk`).

What you learn

- Class construction/destruction and basic RAII
- Stack vs heap allocation and managing dynamic arrays
- References and pointer semantics in method arguments
- Small-scale project layout and Makefile usage

See each exercise folder for a short README describing the exercise-specific goals.

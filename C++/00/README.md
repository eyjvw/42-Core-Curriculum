# C++ — Module Week 00

This folder contains the introductory C++ exercises for the module: `ex00`, `ex01`, and `ex02`.

Description

These exercises introduce basic C++ programming concepts and a small, repeatable project workflow:

- Command-line arguments handling and console I/O.
- Simple classes and object management.
- Basic input validation and formatted output.
- Using a consistent Makefile layout (shared `mk/` fragments for variables, colors and rules).

Exercises

- `ex00` — `megaphone`: work with `argc`/`argv`, transform and print strings.
- `ex01` — `phonebook`: implement `Contact` and `PhoneBook` classes, CLI commands `ADD`/`SEARCH`/`EXIT` and formatted table output.
- `ex02` — consolidation exercises: apply the basics and reinforce input handling and small class design.

Build

Requirements:

- Linux with a C++ compiler (`g++`/`c++`).

To build any exercise, change into the exercise folder and run:

```bash
make
```

Makefile rules

- `make` / `make all`: build the binary
- `make clean`: remove object files
- `make fclean`: remove binary and artifacts
- `make re`: full rebuild

Project structure

- `exNN/`: exercise source, `mk/` fragments and Makefile
- `mk/`: shared Makefile fragments (`variables.mk`, `colors.mk`, `rules.mk`)

Core flow (per exercise)

1. Edit sources in `src/` or exercise root.
2. Run `make` to compile into the exercise binary.
3. Execute the binary and test CLI behavior.

Resources

- C++ reference (cppreference.com)
- 42 coding standards and Norminette

AI Usage

AI assistance was used to standardize Makefiles and README style across the repository.

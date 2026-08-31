# C++ — Modules 00 → 09

*This project has been created as part of the 42 curriculum by sbonneau.*

## Description

The C++ piscine of the 42 common core: ten modules (`00` → `09`) written in **C++98**,
progressing from basic classes and I/O to inheritance, polymorphism, templates and the STL.

Every module folder holds its own README and a set of exercises (`exNN/`), each with its own
README, sources and Makefile built on the shared `mk/` fragments.

## Modules

| Module | Topic | Exercises |
|--------|-------|-----------|
| [00](./00/README.md) | Namespaces, classes, I/O, `megaphone`, `PhoneBook` | ex00 → ex02 |
| [01](./01/README.md) | Memory allocation, references vs pointers, `Harl` | ex00 → ex06 |
| [02](./02/README.md) | Orthodox Canonical Form, fixed-point arithmetic, `bsp` | ex00 → ex03 |
| [03](./03/README.md) | Inheritance, the `ClapTrap` family, diamond problem | ex00 → ex03 |
| [04](./04/README.md) | Polymorphism, abstract classes, interfaces, deep copy | ex00 → ex03 |
| [05](./05/README.md) | Exceptions, `Bureaucrat`, `AForm`, `Intern` | ex00 → ex03 |
| [06](./06/README.md) | Casts, scalar conversion, serialization, RTTI | ex00 → ex02 |
| [07](./07/README.md) | Templates, generic functions, templated `Array` | ex00 → ex02 |
| [08](./08/README.md) | STL containers, algorithms, `MutantStack` | ex00 → ex02 |
| [09](./09/README.md) | STL in practice: `BitcoinExchange`, `RPN`, `PmergeMe` | ex00 → ex02 |

## Build

Requirements: Linux with a C++ compiler (`g++`/`c++`).

Each exercise builds on its own:

```bash
cd 05/ex00
make
./Bureaucrat
```

## Makefile rules

- `make` / `make all`: build the binary
- `make clean`: remove object files
- `make fclean`: remove binary and artifacts
- `make re`: full rebuild

All Makefiles are standardized with the shared `mk/` fragments
(`variables.mk`, `colors.mk`, `rules.mk`) and compile with
`-Wall -Wextra -Werror -std=c++98`.

## Resources

- C++ reference (cppreference.com)
- 42 coding standards

## AI Usage

AI assistance was used to standardize Makefiles and README style across the repository.

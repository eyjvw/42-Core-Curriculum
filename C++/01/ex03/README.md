# ex03 — Human & Weapon (References vs Pointers)

Description

This exercise implements `HumanA`, `HumanB`, and `Weapon` classes to illustrate the
difference between references and pointers as class members.

What you practice

- Class composition: storing objects vs references to objects.
- How references and pointers affect object lifetime and ownership.
- Member function interaction between classes.

Files

- `includes/Weapon.hpp`, `HumanA.hpp`, `HumanB.hpp`
- `src/` — implementations
- `Makefile` for building the exercise

Build & Run

```bash
make
./Violence
```

Notes

- `HumanA` typically holds a reference to a `Weapon`, requiring the weapon to outlive the human.
- `HumanB` usually holds a pointer allowing weapon reassignment at runtime.

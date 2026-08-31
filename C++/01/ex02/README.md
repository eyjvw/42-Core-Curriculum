# ex02 — Pointer vs Reference (HI THIS IS BRAIN)

*This project has been created as part of the 42 curriculum by sbonneau.*

## Description

Small exercise that demonstrates the difference between a pointer and a reference
by printing the memory address and the value of a single `std::string` using:

- the original object
- a pointer to the object
- a reference to the object

## What you practice

- Understanding memory addresses and how pointers store them.
- Dereferencing a pointer to access the pointed value (`*ptr`).
- Using references as aliases to existing objects and how they differ from pointers.
- Observing that pointers and references can be used to access the same object but
	with different syntax and semantics.

## Files

- `src/main.cpp` — prints addresses and values for object/pointer/reference
- `Makefile` — build rules (uses `mk/` fragments)

## Build & Run

```bash
make
./HiThisBrain
```

## Notes

- The program outputs the memory address of the string and shows the same value
	when accessed directly, via pointer, and via reference.
- This is a simple, focused exercise to reinforce pointer vs reference concepts.

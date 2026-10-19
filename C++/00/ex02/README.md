# ex02 — The Job Of Your Dreams (Account)

*This project has been created as part of the 42 curriculum by sbonneau.*

## Description

Recreate the lost `Account.cpp` from the provided `Account.hpp`, `tests.cpp` and log file:
the program output must match `19920104_091532.log` (timestamps aside).

## What you practice

- More practice with C++ types and simple algorithms.
- Input safety and defensive programming.
- Organizing code into multiple source files and using the provided Makefile layout.

## Files

- `includes/Account.hpp`, `src/tests.cpp`: provided by the subject.
- `src/Account.cpp`: the recreated implementation.
- `Makefile` (includes `mk/`) to build the exercise binary.

## Build & Run

```bash
make
./JobOfYourDream
```

## Notes

- Compare with the reference log: `diff <(./JobOfYourDream | cut -c19-) <(cut -c19- 19920104_091532.log)`.

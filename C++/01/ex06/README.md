# ex06 — Harl (Advanced Dispatch)

*This project has been created as part of the 42 curriculum by sbonneau.*

## Description

Advanced variant of the `Harl` logger exercise. This version typically requires
handling levels with controlled fall-through (e.g., DEBUG triggers subsequent levels).

## What you practice

- Implementing level dispatch with intentional fall-through behavior.
- Using `switch` or ordered dispatch safely, and documenting intentional fall-throughs.
- Handling compiler warnings for fall-through (`/* fall through */`) and ensuring clean builds.

## Files

- `includes/Harl.hpp`, `src/Harl.cpp`
- `Makefile` to build the exercise

## Build & Run

```bash
make
./Harl
```

## Notes

- Be explicit about intentional fall-through to satisfy `-Wimplicit-fallthrough` when using `-Werror`.

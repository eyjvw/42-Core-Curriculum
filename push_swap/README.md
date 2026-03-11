# push_swap

*This project has been created as part of the 42 curriculum by sbonneau.*

## Description

`push_swap` sorts integers using two stacks and a limited set of operations. The goal is to produce the shortest possible sequence of operations that sorts the input.

## Usage

### Compilation

```bash
make
# bonus (checker)
make bonus
```

### Running

```bash
# Example
./push_swap 3 2 1 5 4

# Bonus: checker reads operations on stdin and validates
./checker 3 2 1 5 4
# then feed operations to stdin
```

### Makefile rules

- `make` / `make all` — compile `push_swap`
- `make bonus` — compile `checker`
- `make clean` — remove object directories
- `make fclean` — remove executables and objects
- `make re` — full rebuild

## Structure

- `src/ops` — stack operations (sa, sb, pa, pb, ra, rra...)
- `src/sort` — sort strategies (three, medium, chunk...)
- `src/utils` — helpers and parsing
- `bonus/` — checker implementation

## Notes

- I kept algorithmic logic intact (no changes to sort strategies).
- I improved build layout and small robustness checks in utils.

## AI usage

AI assistance was used for code review, Makefile refactor and README generation.

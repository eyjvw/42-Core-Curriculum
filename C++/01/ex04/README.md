# ex04 — Sed (find & replace)

Description

Small utility that reads a file, replaces every occurrence of string `s1` with
`s2`, and writes the result to a new file named `<filename>.replace`.

What you practice

- String search and replacement in lines of text.
- File I/O with `std::ifstream` / `std::ofstream` and error handling.
- Validating arguments and ensuring safe output to a new file.

Files

- `src/main.cpp` — implements the search-and-replace logic
- `Makefile` — build rules (uses `mk/` fragments)

Usage

```bash
make
./Sed filename s1 s2
# produces filename.replace with s1 replaced by s2 throughout the file
```

Behavior notes

- If `s1` is empty the program prints an error and exits.
- The program writes to a new file named `<filename>.replace` (it does not
	edit the original file in-place).
- This exercise is focused: replace every occurrence of `s1` by `s2` and create
	the new output file.

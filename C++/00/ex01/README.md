# ex01 — PhoneBook

*This project has been created as part of the 42 curriculum by sbonneau.*

## Description

Implement a small phonebook application using two classes: `Contact` and `PhoneBook`.

## What you practice

- Class design and simple encapsulation in C++.
- Reading user input with `std::getline` and validating it (empty or whitespace-only inputs are rejected).
- Formatted table output with fixed column widths and truncation of long fields.

## Files

- `src/Contact.cpp`, `includes/Contact.hpp`: contact representation and display helpers.
- `src/PhoneBook.cpp`, `includes/PhoneBook.hpp`: command loop for `ADD`, `SEARCH`, `EXIT` and storage of up to 8 contacts.
- `Makefile` (includes `mk/`) to build the `phonebook` binary.

## Build & Run

```bash
make
./phonebook
```

## Notes

- Inputs containing only spaces or tabs are trimmed and treated as empty — the program prompts again.
- `SEARCH` prints a formatted list and allows selecting an index to show full contact details.

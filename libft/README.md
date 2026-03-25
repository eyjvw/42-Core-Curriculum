# libft

*This project has been created as part of the 42 curriculum by sbonneau.*

## Description

**libft** is a custom C library that reimplements a selection of standard C library functions, along with additional utility functions not available in the standard library. It serves as a foundation for all future 42 projects, replacing the use of the standard `libc`.

The library is split into three categories:

### Libc Functions
Standard functions reimplemented from scratch:
- `ft_isalnum` `ft_isalpha` `ft_isascii` `ft_isdigit` `ft_isprint`
- `ft_tolower` `ft_toupper`
- `ft_strlen` `ft_strchr` `ft_strrchr` `ft_strncmp` `ft_strnstr`
- `ft_strlcpy` `ft_strlcat` `ft_strdup`
- `ft_memset` `ft_bzero` `ft_memcpy` `ft_memmove` `ft_memchr` `ft_memcmp`
- `ft_atoi` `ft_calloc`

### Additional Functions
Utility functions not in `libc`:
- `ft_substr` `ft_strjoin` `ft_strtrim` `ft_split`
- `ft_itoa` `ft_strmapi` `ft_striteri`
- `ft_putchar_fd` `ft_putstr_fd` `ft_putendl_fd` `ft_putnbr_fd`

### Bonus — Linked List
A generic singly-linked list implementation using `t_list`:
- `ft_lstnew` `ft_lstadd_front` `ft_lstadd_back` `ft_lstlast`
- `ft_lstsize` `ft_lstdelone` `ft_lstclear` `ft_lstiter` `ft_lstmap`

## Instructions

### Build

```bash
# Compile the base library
make

# Compile with bonus (linked list functions)
make bonus
```

Both produce `libft.a`.

### Usage

1. Include the header in your C file:
```c
#include "libft.h"
```

2. Compile your program with the library:
```bash
gcc -Wall -Wextra -Werror your_file.c libft.a -o your_program
```

### Makefile Rules

| Rule | Effect |
|------|--------|
| `make` / `make all` | Compile the base library |
| `make bonus` | Compile the library including linked list functions |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and `libft.a` |
| `make re` | Full recompile from scratch |

## Data Structure: t_list

The bonus part introduces a generic linked list node:

```c
typedef struct s_list
{
    void          *content;
    struct s_list *next;
}   t_list;
```

`content` is a `void *`, meaning the list can hold any data type. All list functions operate on this structure.

## Resources

- [man 3 string](https://man7.org/linux/man-pages/man3/string.3.html) - Standard string functions reference
- [man 3 stdlib](https://man7.org/linux/man-pages/man3/stdlib.h.3head.html) - Standard library functions reference
- [42 Norminette](https://github.com/42School/norminette) - Official 42 coding standards
- [Linked Lists in C](https://en.wikipedia.org/wiki/Linked_list) - Linked list concepts

## AI Usage

AI assistance (GitHub Copilot) was used for the following tasks:

1. **Norm Compliance**: Identifying and fixing norminette errors (variable alignment, line counts, function count per file)
2. **Bug Identification**: Detecting edge cases in memory functions and string operations
3. **Documentation**: Generating the README structure

Core implementation logic and algorithm design were done manually. AI was used as a coding assistant to ensure norm compliance and code organization.

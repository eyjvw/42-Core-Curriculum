# get_next_line

*This project has been created as part of the 42 curriculum by sbonneau.*

## Description

**get_next_line** is a function that reads one line at a time from a file descriptor, returning it on each successive call. It handles files, stdin, and multiple file descriptors simultaneously (bonus).

The function signature:
```c
char *get_next_line(int fd);
```

Each call returns the next line including the `\n` character (if present), or `NULL` on EOF or error. The returned string must be freed by the caller.

## Files

| File | Description |
|------|-------------|
| `get_next_line.c` | Main function + read/line-extraction logic |
| `get_next_line_utils.c` | String utility functions |
| `get_next_line.h` | Header with prototypes and `BUFFER_SIZE` |
| `get_next_line_bonus.c` | Bonus: supports multiple file descriptors |
| `get_next_line_utils_bonus.c` | Bonus: same utils for the bonus version |
| `get_next_line_bonus.h` | Bonus header with `FD_MAX` (1024) |

## How It Works

### Architecture: 3 internal functions

```
ft_read()   — reads from fd in BUFFER_SIZE chunks, accumulates into a static buffer until '\n' or EOF
ft_line()   — extracts the first line from the buffer, updates the remainder for the next call
ft_copy()   — safe strjoin that frees s1 automatically (used to grow the buffer)
```

### Static Buffer

A `static char *buffer` persists between calls, holding any data read beyond the last returned line. On the next call, `ft_read` checks this remainder before calling `read()` again.

### Bonus: Multiple FDs

The bonus version uses `static char *buffer[FD_MAX]` — one buffer slot per file descriptor — allowing simultaneous reads from up to 1024 different FDs without losing context.

## Usage

### Build

```bash
# Standard version
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl

# Bonus version
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c -o gnl_bonus
```

The `BUFFER_SIZE` can be overridden at compile time. Default is `400` if not specified.

### Example

```c
#include "get_next_line.h"

int fd = open("file.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
```

## Resources

- [man 2 read](https://man7.org/linux/man-pages/man2/read.2.html) - read() syscall documentation
- [Static variables in C](https://en.cppreference.com/w/c/language/storage_duration) - Understanding static storage duration
- [42 Norminette](https://github.com/42School/norminette) - Official 42 coding standards
- [File descriptors](https://en.wikipedia.org/wiki/File_descriptor) - File descriptor concepts

## AI Usage

AI assistance (GitHub Copilot) was used for the following tasks:

1. **Code Review**: Identifying edge cases and correctness issues (null checks, type mismatches)
2. **Norm Compliance**: Keeping functions within the 25-line and 5-function limits
3. **Documentation**: Generating the README structure

Core algorithm design and implementation were done manually.

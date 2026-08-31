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

### Architecture: 2 internal functions + the entry point

```
ft_fill()     - grows the stash with BUFFER_SIZE reads, and only while the
                stash does not already contain a '\n'
ft_extract()  - cuts the leading line out of the stash and replaces the stash
                with the remainder
get_next_line() - validates the fd, fills, extracts, and clears the stash on
                  EOF or error
```

### The stash

A `static char *stash` persists between calls and holds everything read past
the last returned line. This is what makes repeated calls cheap: the data
already read is never re-read, and never re-parsed from the start of the file.

### Reading as little as possible

`ft_fill()` tests the stash for a newline **before every `read()`**, so a call
that can already be answered from the stash performs no syscall at all. This is
what the subject asks for ("if you encounter a new line, you have to return the
current line"), and it is also what makes the function usable on pipes,
sockets and terminals: reading ahead on a stream that has no more data yet
would simply block.

### Cost

Growing the stash re-copies it, so a line of length `L` read with a buffer of
size `B` costs `O(L^2 / B)` in the worst case. For the sizes this project deals
with, that is well below the cost of the syscalls themselves, and it keeps the
allocation logic simple enough to stay obviously leak-free. `BUFFER_SIZE` is
handled identically at `1`, at `10000000`, and when the flag is absent.

### Bonus: multiple FDs

The bonus keeps one stash per file descriptor in a single static array,
`static char *stash[FD_MAX]` — one static variable, as the subject requires —
so reads can be interleaved across up to 1024 descriptors without any of them
losing its position. The fd is range-checked *before* it is used as an index.

## Instructions

### Build

```bash
# Standard version
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl

# Bonus version
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c -o gnl_bonus
```

The `BUFFER_SIZE` can be overridden at compile time. Default is `400` if not specified.

### Usage

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

AI assistance was used for the following tasks:

1. **Code review**: building a test harness (pipes, sanitizers, buffer sizes
   from 1 to 10000000) and using it to find an invalid-fd double free, an
   out-of-bounds stash index in the bonus, and a read-ahead that blocked on
   pipes.
2. **Norm compliance**: keeping functions within the 25-line and 5-function
   limits.
3. **Documentation**.

The algorithm and the implementation are the author's; AI was used to review
and stress-test them, not to generate them.

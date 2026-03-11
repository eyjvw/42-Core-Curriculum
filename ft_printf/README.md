# ft_printf

*This project has been created as part of the 42 curriculum by sbonneau.*

## Description

**ft_printf** is a custom implementation of the C standard library function `printf()`. This project aims to recreate the behavior of `printf` with support for multiple format specifiers and bonus flags, providing a deep understanding of variadic functions, string formatting, and low-level output operations.

The implementation handles the following conversions:
- `%c` - Character
- `%s` - String
- `%p` - Pointer address
- `%d` / `%i` - Signed decimal integer
- `%u` - Unsigned decimal integer
- `%x` - Hexadecimal (lowercase)
- `%X` - Hexadecimal (uppercase)
- `%%` - Literal percent sign

### Bonus Features

The project includes support for the following formatting flags:
- `-` : Left-align the output within the given field width
- `0` : Pad with zeros instead of spaces
- `.` : Precision specification
- `#` : Alternate form (adds 0x/0X prefix for hexadecimal)
- ` ` (space) : Add a space before positive numbers
- `+` : Always display sign for signed conversions
- *width* : Minimum field width

## Instructions

### Compilation

To compile the library:

```bash
make
```

This will create the static library `libftprintf.a` containing all the necessary object files.

### Usage

1. Include the header in your C file:
```c
#include "ft_printf.h"
```

2. Compile your program with the library:
```bash
gcc -Wall -Wextra -Werror your_file.c libftprintf.a -o your_program
```

3. Use `ft_printf()` just like the standard `printf()`:
```c
ft_printf("Hello %s! Number: %d\n", "World", 42);
ft_printf("Hex: %#x, Pointer: %p\n", 255, ptr);
ft_printf("%10.5d\n", 42);  // Width and precision
```

### Makefile Rules

- `make` or `make all` - Compile the library
- `make clean` - Remove object files
- `make fclean` - Remove object files and the library
- `make re` - Recompile everything from scratch

## Resources

### Documentation & References

- [printf man page](https://man7.org/linux/man-pages/man3/printf.3.html) - Official documentation for printf formatting
- [Variadic Functions in C](https://en.cppreference.com/w/c/variadic) - Understanding `va_list`, `va_start`, `va_arg`, `va_end`
- [42 Norminette](https://github.com/42School/norminette) - Official 42 coding standards
- [Printf Format Specifiers](https://cplusplus.com/reference/cstdio/printf/) - Detailed format specification reference

### AI Usage

AI assistance (GitHub Copilot) was used for the following tasks:

1. **Code Refactoring**: Helping split large functions into smaller, norm-compliant functions (max 25 lines, max 5 functions per file)
2. **Norm Compliance**: Identifying and fixing norminette errors (variable alignment, function arguments, line counts)
3. **Bug Identification**: Detecting edge cases and logic errors in precision and flag handling
4. **Documentation**: Generating comments and README structure

The core algorithm design, implementation logic, and debugging were done manually. AI was primarily used as a coding assistant to ensure compliance with 42 standards and improve code organization.

## Algorithm & Data Structure Explanation

### Core Architecture

The implementation is organized into multiple files to respect the 42 norm (max 5 functions per file):

```
ft_printf.c          - Main entry point and format string parsing
ft_bonus.c           - Flag parsing logic
ft_conversions.c     - Signed integer conversions
ft_conversions2.c    - Unsigned integer conversions
ft_conversions3.c    - Hexadecimal conversions
ft_utils.c           - Basic output functions (char, string, numbers)
ft_utils2.c          - Hexadecimal and pointer utilities
ft_utils3.c          - Formatting with flags (width, alignment)
ft_printf_utils.c    - Helper functions for padding and conversions
```

### Data Structure: t_flags

```c
typedef struct s_flags
{
    int minus;      // Left-align flag (-)
    int zero;       // Zero-padding flag (0)
    int hash;       // Alternate form flag (#)
    int plus;       // Force sign flag (+)
    int space;      // Space before positive numbers
    int width;      // Minimum field width
    int precision;  // Precision specification
} t_flags;
```

This structure centralizes all formatting information, making it easy to pass formatting context between functions without exceeding the 4-parameter limit imposed by the norm.

### Algorithm: Two-Phase Processing

#### Phase 1: Flag Parsing (`ft_parse_flags`)

1. Initialize all flags to default values (0 or -1 for precision)
2. Parse flag characters (`-`, `0`, `+`, ` `, `#`)
3. Parse width (numeric value)
4. Parse precision (`.` followed by numeric value)
5. Return the populated `t_flags` structure

**Justification**: Parsing flags separately from conversion logic keeps functions focused and maintainable. The precision default of `-1` distinguishes "no precision specified" from precision `0`.

#### Phase 2: Conversion and Formatting

For each format specifier:

1. **Simple conversions** (`%c`, `%s`, `%p`) are handled directly with flag support
2. **Numeric conversions** (`%d`, `%i`, `%u`, `%x`, `%X`) follow this process:
   - Convert number to string with appropriate base (10 or 16)
   - Apply precision (zero-padding for numbers)
   - Add prefixes/signs (`+`, ` `, `0x`, `0X`)
   - Apply width padding (left or right aligned)

**Key Design Decisions**:

1. **String-based conversion**: Numbers are converted to strings before formatting. This simplifies width/padding logic and avoids complex recursive counting.

2. **Separation of concerns**: Each conversion type has its own function, making the code modular and testable.

3. **Zero-padding vs Precision**: When precision is specified for numeric types, the zero flag is ignored (as per printf specification). This is enforced with:
   ```c
   if (flags.precision >= 0)
       flags.zero = 0;
   ```

4. **Memory management**: Dynamic allocation (`malloc`) is used for conversion buffers with a fixed `BUFFER_SIZE` (50 bytes), sufficient for all standard conversions. Each allocated string is freed after use to prevent leaks.

5. **Precision edge case**: When precision is `0` and value is `0`, nothing is printed for numeric types (standard printf behavior):
   ```c
   if (!(flags.precision == 0 && n == 0))
       // write digits
   ```

### Performance Considerations

- **Single-pass parsing**: The format string is parsed once from left to right
- **Minimal system calls**: Output is buffered when possible (write multiple characters at once)
- **No recursion for conversions**: Iterative approach with power-of-base calculation prevents stack overflow

### Norm Compliance Strategy

To meet the strict 42 norm requirements:
- Functions split across multiple files when exceeding 5 functions per file
- Helper functions extract logic to keep functions under 25 lines
- Parameter count limited to 4 by using structures (`t_flags`)
- No ternary operators (replaced with if/else)
- Variables aligned with tabs
